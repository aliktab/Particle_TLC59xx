#pragma once

/*
  Copyright (C) 2014 Alik <aliktab@gmail.com> All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

// this will load the definition for common Particle variable types
#include <Particle.h>


#define TLC59711_BLINK_OFF      0
#define TLC59711_BLINK_2HZ      1
#define TLC59711_BLINK_1HZ      2
#define TLC59711_BLINK_HALFHZ   3

#define TLC59711_CHANNELS_QTY   12

#define TLC59711_MAX_PWM_VAL    0xffff


class TLC59711
{
public:

  enum BlinkMode
  {
    blm_off   = 0,
    blm_2hz   = 1,
    blm_1hz   = 2,
    blm_half  = 3
  };


  // Constructor: bymber of cascaded TLC59711
  TLC59711(uint8_t _qty);

  bool begin();

  void set_BC(uint8_t _r, uint8_t _g, uint8_t _b);

  void set_PWM(uint8_t _pos, uint16_t _pwm);

  void set_LED(uint8_t _led, uint16_t _r, uint16_t _g, uint16_t _b);

  void show_data();

  void clear();

protected:

  uint8_t     m_chips_qty;

  uint8_t     m_BCr;
  uint8_t     m_BCg;
  uint8_t     m_BCb;

  uint16_t *  m_buffer;
};



