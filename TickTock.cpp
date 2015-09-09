/*==============================================================================

  TickTock.cpp - Manage time by ticks / tocks rather than micros / millis.

  Copyright 2015 Rowdy Dog Software.

  This file is part of Arduino-Tiny.

  Arduino-Tiny is free software: you can redistribute it and/or modify it 
  under the terms of the GNU Lesser General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or (at your
  option) any later version.

  Arduino-Tiny is distributed in the hope that it will be useful, but 
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License 
  along with Arduino-Tiny.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/

#include <TickTock.h>

#include <util/atomic.h>

extern volatile unsigned long timer0_overflow_count;

unsigned long ticks( void )
{
	unsigned long ovf;
	uint8_t cnt;

  ATOMIC_BLOCK( ATOMIC_RESTORESTATE )
  {
  	ovf = timer0_overflow_count;

    #if defined(TCNT0)
	    cnt = TCNT0;
    #elif defined(TCNT0L)
	    cnt = TCNT0L;
    #else
	    #error TIMER 0 not defined
    #endif

    #ifdef TIFR0
	    if ((TIFR0 & _BV(TOV0)) && (cnt < 255))
		    ovf++;
    #else
	    if ((TIFR & _BV(TOV0)) && (cnt < 255))
		    ovf++;
    #endif
  }
  return( (ovf << 8) | cnt );
}

unsigned long tocks( void )
{
  unsigned long ovf;

  ATOMIC_BLOCK( ATOMIC_RESTORESTATE )
  {
    ovf = timer0_overflow_count;
  }

  return( ovf );
}
