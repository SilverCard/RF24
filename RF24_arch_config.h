
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.

 */
#ifndef __ARCH_CONFIG_H__
#define __ARCH_CONFIG_H__

#define RF24_LINUX

#include <stddef.h>
#include "Spi.h"
#include "gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <chrono>
#include <thread>

#define _BV(x) (1<<(x))

#define rf24_max(a,b) (a>b?a:b)
#define rf24_min(a,b) (a<b?a:b)
  
//#undef SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#define IF_SERIAL_DEBUG(x) ({x;})
#else
#define IF_SERIAL_DEBUG(x)
#endif

// Avoid spurious warnings
#if 1
#if ! defined( NATIVE ) && defined( ARDUINO )
#undef PROGMEM
#define PROGMEM __attribute__(( section(".progmem.data") ))
#undef PSTR
#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
#endif
#endif

typedef uint16_t prog_uint16_t;
#define PSTR(x) (x)
#define printf_P printf
#define strlen_P strlen
#define PROGMEM
#define pgm_read_word(p) (*(p)) 
#define PRIPSTR "%s"
#define pgm_read_byte(p) (*(p))

// Function, constant map as a result of migrating from Arduino
#define LOW GPIO::OUTPUT_LOW
#define HIGH GPIO::OUTPUT_HIGH
#define INPUT GPIO::DIRECTION_IN
#define OUTPUT GPIO::DIRECTION_OUT
#define digitalWrite(pin, value) GPIO::write(pin, value)
#define pinMode(pin, direction) GPIO::open(pin, direction)
#define delay(milisec) std::this_thread::sleep_for(std::chrono::milliseconds(milisec))
#define delayMicroseconds(usec) std::this_thread::sleep_for(std::chrono::microseconds(usec))

#endif // __ARCH_CONFIG_H__
// vim:ai:cin:sts=2 sw=2 ft=cpp
