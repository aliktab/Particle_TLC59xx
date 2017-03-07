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

#include "TLC59xx.h"
TLC59711 led_array(1);

void setup()
{
  led_array.begin();
  led_array.set_BC(0x30, 0x7f, 0x03);
  led_array.clear();

  for (int i = 0; i < 12; i++)
    led_array.set_PWM(i, TLC59711_MAX_PWM_VAL);

  led_array.show_data();
}

void loop()
{
}
