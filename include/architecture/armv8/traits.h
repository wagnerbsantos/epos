// EPOS ARMv8 Architecture Metainfo
#ifndef __armv8_traits_h
#define __armv8_traits_h

#include <system/config.h>

__BEGIN_SYS

template<> struct Traits<CPU>: public Traits<void>
{
    enum {LITTLE, BIG};
    static const unsigned int ENDIANESS         = LITTLE;
    static const unsigned int WORD_SIZE         = 32;
    static const unsigned int CLOCK             = Traits<Build>::MODEL == Traits<Build>::Raspberry_Pi3 ? 600000000 : 0;
    static const bool unaligned_memory_access   = false;
};

template<> struct Traits<MMU>: public Traits<void>
{
    static const bool colorful = false;
    static const unsigned int COLORS = 1;
};

template<> struct Traits<TSC>: public Traits<void>
{
    static const bool enabled = true;
};

template<> struct Traits<PMU>: public Traits<void>
{
    static const bool enabled = true;
};

__END_SYS

#endif
