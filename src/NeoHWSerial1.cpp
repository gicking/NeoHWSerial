/*
  NeoHWSerial1.cpp - Hardware serial library with attachInterrupt
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
  Modified 2 November 2015 by SlashDev
  Modified 31 October 2020 by Georg Icking-Konert
*/

// only compile for AVR architecture
#if defined(ARDUINO_ARCH_AVR)

#include "Arduino.h"
#include "NeoHWSerial.h"
#include "NeoHWSerial_private.h"

// Each NeoHWSerial is defined in its own file, sine the linker pulls
// in the entire file when any element inside is used. --gc-sections can
// additionally cause unused symbols to be dropped, but ISRs have the
// "used" attribute so are never dropped and they keep the
// NeoHWSerial instance in as well. Putting each instance in its own
// file prevents the linker from pulling in any unused instances in the
// first place.

#if defined(HAVE_HWSERIAL1)

  #if defined(UART1_RX_vect)
    ISR(UART1_RX_vect)
  #elif defined(USART1_RX_vect)
    ISR(USART1_RX_vect)
  #else
    #error "Don't know what the Data Register Empty vector is called for Serial1"
  #endif
  {
    NeoSerial1._rx_complete_irq();
  }

  #if defined(UART1_UDRE_vect)
    ISR(UART1_UDRE_vect)
  #elif defined(USART1_UDRE_vect)
    ISR(USART1_UDRE_vect)
  #else
    #error "Don't know what the Data Register Empty vector is called for Serial1"
  #endif
  {
    NeoSerial1._tx_udr_empty_irq();
  }

  NeoHWSerial NeoSerial1(&UBRR1H, &UBRR1L, &UCSR1A, &UCSR1B, &UCSR1C, &UDR1);

  // Function that can be weakly referenced by serialEventRun to prevent
  // pulling in this file if it's not otherwise used.
  bool NeoSerial1_available()
  {
    return NeoSerial1.available();
  }

#endif // HAVE_HWSERIAL1

#endif // ARDUINO_ARCH_AVR
