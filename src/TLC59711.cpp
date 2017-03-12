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

#include "TLC59711.h"

#define TLC59711_MAGIC_CMD    0x25


TLC59711::TLC59711(uint8_t _qty, SPIClass & _spi) :
  m_spi(_spi)
{
  m_chips_qty  = _qty;
  m_buffer = (uint16_t *)calloc(2 * TLC59711_CHANNELS_QTY, m_chips_qty);

  m_BCr = m_BCg = m_BCb = 0;
}

bool TLC59711::begin()
{
  if (!m_buffer) return false;

  m_spi.begin(SPI_MODE_MASTER);

  m_spi.setBitOrder(MSBFIRST);
  m_spi.setClockDivider(SPI_CLOCK_DIV64);
  m_spi.setDataMode(SPI_MODE0);

  return true;
}

void TLC59711::set_BC(uint8_t _r, uint8_t _g, uint8_t _b)
{
  m_BCr = _r <= 0x7f ? _r : 0x7f;
  m_BCg = _g <= 0x7f ? _g : 0x7f;
  m_BCb = _b <= 0x7f ? _b : 0x7f;
}

void TLC59711::set_PWM(uint8_t _pos, uint16_t _pwm)
{
  if (_pos < TLC59711_CHANNELS_QTY * m_chips_qty)
    m_buffer[_pos] = _pwm;
}


void TLC59711::set_LED(uint8_t _led, uint16_t _r, uint16_t _g, uint16_t _b)
{
  set_PWM(_led * 3 + 0, _r);
  set_PWM(_led * 3 + 1, _g);
  set_PWM(_led * 3 + 2, _b);
}

void TLC59711::show_data()
{
  uint32_t command;

  // Magic word for write
  command = TLC59711_MAGIC_CMD;

  command <<= 5;
  // OUTTMG = 1, EXTGCK = 0, TMGRST = 1, DSPRPT = 1, BLANK = 0 -> 0x16
  command |= 0x16;

  command <<= 7;
  command |= m_BCb;

  command <<= 7;
  command |= m_BCg;

  command <<= 7;
  command |= m_BCr;

  noInterrupts();

  for (int i = 0; i < m_chips_qty; i++)
  {
    m_spi.transfer(command >> 24);
    m_spi.transfer(command >> 16);
    m_spi.transfer(command >>  8);
    m_spi.transfer(command      );

    // TLC59711_CHANNELS_QTY channels per TLC59711
    for (int8_t j = 11; j >= 0 ; j--)
    {
      // 16 bits per channel, send MSB first
      m_spi.transfer(m_buffer[i * TLC59711_CHANNELS_QTY + j] >> 8);
      m_spi.transfer(m_buffer[i * TLC59711_CHANNELS_QTY + j]     );
    }
  }

  delayMicroseconds(2);

  interrupts();
}

void TLC59711::clear()
{
  for (int i = 0; i < TLC59711_CHANNELS_QTY * m_chips_qty; i++)
    m_buffer[i] = 0;
}




