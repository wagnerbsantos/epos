// EPOS ARM Cortex Timer Mediator Declarations

#ifndef __cortex_timer_h
#define __cortex_timer_h

#include <architecture/cpu.h>
#include <machine/ic.h>
#include <machine/timer.h>
#include __HEADER_MMOD(timer)
#include <utility/convert.h>

__BEGIN_SYS

// Tick timer used by the system
class Timer: private System_Timer_Engine
{
    friend Machine;
    friend IC;
    friend class Init_System;

protected:
    static const unsigned int CHANNELS = 2;
    static const unsigned int FREQUENCY = Traits<Timer>::FREQUENCY;

    typedef System_Timer_Engine Engine;
    typedef IC_Common::Interrupt_Id Interrupt_Id;

public:
    using Timer_Common::Hertz;
    using Timer_Common::Tick;
    using Timer_Common::Handler;

    // Channels
    enum {
        SCHEDULER,
        ALARM
    };

protected:
    Timer(unsigned int channel, const Hertz & frequency, const Handler & handler, bool retrigger = true)
    : _channel(channel), _initial(FREQUENCY / frequency), _retrigger(retrigger), _handler(handler) {
        db<Timer>(TRC) << "Timer(f=" << frequency << ",h=" << reinterpret_cast<void*>(handler) << ",ch=" << channel << ") => {count=" << _initial << "}" << endl;

        if(_initial && (channel < CHANNELS) && !_channels[channel])
            _channels[channel] = this;
        else
            db<Timer>(WRN) << "Timer not installed!"<< endl;

        for(unsigned int i = 0; i < Traits<Machine>::CPUS; i++)
            _current[i] = _initial;
    }

public:
    ~Timer() {
        db<Timer>(TRC) << "~Timer(f=" << frequency() << ",h=" << reinterpret_cast<void*>(_handler) << ",ch=" << _channel << ") => {count=" << _initial << "}" << endl;

        _channels[_channel] = 0;
    }

    Hertz frequency() const { return (FREQUENCY / _initial); }
    void frequency(const Hertz & f) { _initial = FREQUENCY / f; reset(); }

    Tick read() { return _current[CPU::id()]; }

    int reset() {
        db<Timer>(TRC) << "Timer::reset() => {f=" << frequency()
                       << ",h=" << reinterpret_cast<void*>(_handler)
                       << ",count=" << _current[CPU::id()] << "}" << endl;

        int percentage = _current[CPU::id()] * 100 / _initial;
        _current[CPU::id()] = _initial;

        return percentage;
    }

    using Engine::enable;
    using Engine::disable;

    void handler(const Handler & handler) { _handler = handler; }

private:
    static void int_handler(const Interrupt_Id & i);
    static void eoi(const Interrupt_Id & int_id) { Engine::eoi(int_id); }

    static void init();

private:
    unsigned int _channel;
    Tick _initial;
    bool _retrigger;
    volatile Tick _current[Traits<Machine>::CPUS];
    Handler _handler;

    static Timer * _channels[CHANNELS];
};

// Timer used by Thread::Scheduler
class Scheduler_Timer: public Timer
{
private:
    typedef RTC::Microsecond Microsecond;

public:
    Scheduler_Timer(const Microsecond & quantum, const Handler & handler): Timer(SCHEDULER, 1000000 / quantum, handler) {}
};

// Timer used by Alarm
class Alarm_Timer: public Timer
{
public:
    static const unsigned int FREQUENCY = Timer::FREQUENCY;

public:
    Alarm_Timer(const Handler & handler): Timer(ALARM, FREQUENCY, handler) {}
};


// User timer
class User_Timer: private User_Timer_Engine
{
    friend class PWM;

private:
    typedef User_Timer_Engine Engine;
    typedef Engine::Count Count;
    typedef IC_Common::Interrupt_Id Interrupt_Id;

    static const unsigned int UNITS = Traits<Timer>::UNITS - Traits<TSC>::enabled; // TSC uses the last timer. To use the it, you must disable the TSC.

public:
    using Timer_Common::Microsecond;
    using Timer_Common::Handler;

public:
    User_Timer(unsigned int channel, const Microsecond & time, const Handler & handler, bool periodic = false)
    : Engine(channel, time, handler ? true : false, periodic), _channel(channel), _handler(handler) {
        assert(channel < UNITS);
        if(_handler) {
            IC::Interrupt_Id id = _channel == 0 ? IC::INT_USER_TIMER0 : _channel == 1 ? IC::INT_USER_TIMER1 :
                                  _channel == 2 ? IC::INT_USER_TIMER2 : IC::INT_USER_TIMER3;
            IC::int_vector(id, _handler);
            IC::enable(id);
        }
    }
    ~User_Timer() {
        if(_handler) {
            IC::Interrupt_Id id = _channel == 0 ? IC::INT_USER_TIMER0 : _channel == 1 ? IC::INT_USER_TIMER1 :
                                  _channel == 2 ? IC::INT_USER_TIMER2 : IC::INT_USER_TIMER3;
            IC::disable(id);
        }
    }

    using Engine::read;

    using Engine::enable;
    using Engine::disable;

    void power(const Power_Mode & mode);

    static void eoi(const Interrupt_Id & int_id) { Engine::eoi(int_id); }

private:
    unsigned int _channel;
    Handler _handler;
};

__END_SYS

#endif
