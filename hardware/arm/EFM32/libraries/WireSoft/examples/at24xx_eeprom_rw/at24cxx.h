/*
  EEPROM.h - EEPROM library
  Copyright (c) 2006 David A. Mellis.  All right reserved.

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

  modify by huawewi huaweiwx@sina.com 2017.2.18
*/

#ifndef _AT24CXX_h
#define _AT24CXX_h

#if __has_include("configs/i2cEepromConfig.h")
#  include "configs/i2cEepromConfig.h"
#endif

#if USE_WARESOFT >0
# include "WireSoft.h"
# define WARE TwoWireSoft
#else
#include "Wire.h"
# define WARE TwoWire
#endif

#define AT24C01		0x7f
#define AT24C02		0xff
#define AT24C04		0x1ff
#define AT24C08		0x3ff
#define AT24C16		0x7ff
#define AT24C32		0xfff
#define AT24C64	  0x1fff
#define AT24C128	0x3fff
#define AT24C256	0x7fff
#define AT24C512	0xffff

class EXTEEPROM : public WARE {
  public:
    EXTEEPROM(__ConstPin sda = SDA, __ConstPin scl = SCL, uint8_t delay = SOFT_STANDARD):WARE(sda,scl,delay){}
	
    void begin(uint8_t devAdr = 0x50, uint16_t devType = AT24C02);
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

    ~EXTEEPROM();
    uint8_t 	_devAdr;
    uint16_t    _devType;
};

//extern EEPROMClass EXTEEPROM;

#endif

