// EPOS Machine Mediator

#ifndef __machine_h
#define __machine_h

#include <machine/ic.h>
#include <machine/timer.h>
#include <machine/rtc.h>
#include <machine/display.h>
#include <machine/common.h>

#ifdef __PCI_H
#include <machine/pci.h>
#endif
#ifdef __UART_H
#include <machine/uart.h>
#endif
#ifdef __RS485_H
#include <machine/rs485.h>
#endif
#ifdef __SPI_H
#include <machine/spi.h>
#endif
#ifdef __USB_H
#include <machine/usb.h>
#endif
#ifdef __GPIO_H
#include <machine/gpio.h>
#endif
#ifdef __ADC_H
#include <machine/adc.h>
#endif
#ifdef __KEYBOARD_H
#include <machine/keyboard.h>
#endif
#ifdef __AES_H
#include <machine/aes.h>
#endif
#ifdef __CO2_H
#include <machine/co2.h>
#endif

#endif
