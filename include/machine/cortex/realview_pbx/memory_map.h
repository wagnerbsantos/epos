// EPOS Realview PBX (ARM Cortex-A9) Memory Map

#ifndef __model_memory_map_h
#define __model_memory_map_h

#include <system/memory_map.h>
#include <machine/cortex/memory_map.h>

__BEGIN_SYS

struct Memory_Map: public Cortex_Memory_Map
{
    // Physical Memory
    enum {
        I2C_BASE                    = 0x10002000, // Versatile I2C
        AAC_BASE                    = 0x10004000, // PrimeCell PL041 Advanced Audio CODEC
        MMCI_BASE                   = 0x10005000, // PrimeCell PL181 MultiMedia Card Interface
        KBD0_BASE                   = 0x10006000, // PrimeCell PL050 PS2 Keyboard/Mouse Interface
        KBD1_BASE                   = 0x10007000, // PrimeCell PL050 PS2 Keyboard/Mouse Interface
        UART0_BASE                  = 0x10009000, // PrimeCell PL011 UART
        UART1_BASE                  = 0x1000a000, // PrimeCell PL011 UART
        UART2_BASE                  = 0x1000b000, // PrimeCell PL011 UART
        UART3_BASE                  = 0x1000c000, // PrimeCell PL011 UART
        TIMER0_BASE                 = 0x10011000, // ARM Dual-Timer Module SP804
        TIMER1_BASE                 = 0x10012000, // ARM Dual-Timer Module SP804
        GPIO0_BASE                  = 0x10013000, // PrimeCell PL061 GPIO
        GPIO1_BASE                  = 0x10014000, // PrimeCell PL061 GPIO
        GPIO2_BASE                  = 0x10015000, // PrimeCell PL061 GPIO
        RTC_BASE                    = 0x10017000, // PrimeCell PL031 RTC
        LCD_BASE                    = 0x10020000, // PrimeCell PL110 Color LCD Controller
        DMA_BASE                    = 0x10030000, // PrimeCell PL080 DMA Controller

        PPS_BASE                    = 0x1f000000, // A9 Private Peripheral Space
        SCU_BASE                    = 0x1f000000, // MP Snoop Control Unit
        GIC_CPU_BASE                = 0x1f000100,
        GLOBAL_TIMER_BASE           = 0x1f000200,
        PRIVATE_TIMER_BASE          = 0x1f000600,
        GIC_DIST_BASE               = 0x1f001000
    };

    // Logical Address Space
};

__END_SYS

#endif
