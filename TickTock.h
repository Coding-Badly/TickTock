/*==============================================================================

  TickTock.h - Manage time by ticks / tocks rather than micros / millis.

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
#ifndef TickTock_h
#define TickTock_h

unsigned long ticks( void );
unsigned long tocks( void );

void tc_ticktock_constant( void ) __attribute__((error("The parameter must be a compile-time constant.")));

// fix? rmv? const unsigned long us2ticksF( unsigned long microseconds );

__attribute__((always_inline, unused, const)) static inline 
const unsigned long us2ticks( unsigned long microseconds )
{
  static const unsigned long long Prescaler = 64ull;
  static const unsigned long long Divisor = Prescaler * 1000000ull;

  if ( __builtin_constant_p( microseconds ) )
  {
    return( (unsigned long) ((((unsigned long long)microseconds * F_CPU) + (Divisor / 2)) / Divisor) );
  }
  else
  {
    tc_ticktock_constant();
    // fix? rmv? return( us2ticksF( microseconds ) );
  }
}

__attribute__((always_inline, unused, const)) static inline 
const unsigned long ms2ticks( unsigned long milliseconds )
{
  return( us2ticks( milliseconds * 1000ul ) );
}

// fix? rmv? const unsigned long us2tocksF( unsigned long microseconds );

__attribute__((always_inline, unused, const)) static inline 
const unsigned long us2tocks( unsigned long microseconds )
{
  static const unsigned long long Prescaler = 64ull;
  static const unsigned long long Divisor = Prescaler * 1000000ull * 256ull;

  if ( __builtin_constant_p( microseconds ) )
  {
    return( (unsigned long) ((((unsigned long long)microseconds * F_CPU) + (Divisor / 2)) / Divisor) );
  }
  else
  {
    tc_ticktock_constant();
    // fix? rmv? return( us2tocksF( microseconds ) );
  }
}

__attribute__((always_inline, unused, const)) static inline 
const unsigned long ms2tocks( unsigned long milliseconds )
{
  return( us2tocks( milliseconds * 1000ul ) );
}

#endif
