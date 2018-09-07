/* Arduino DigitalIO Library
 * Copyright (C) 2013 by William Greiman
 *
 * This file is part of the Arduino DigitalIO Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino DigitalIO Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file 
 * @brief  Software SPI.
 *
 * @defgroup softSPI Software SPI
 * @details  Software SPI Template Class.
 * @{
 */

#ifndef __SOFTSPI_h__
#define __SOFTSPI_h__
#include "utils/digitalPin.h"
//------------------------------------------------------------------------------
/** Nop for timing. */
#define nop asm volatile ("nop\n\t")
//------------------------------------------------------------------------------
/** Pin Mode for MISO is input.*/
#define MISO_MODE INPUT
/** Pullups disabled for MISO are disabled. */
#define MISO_LEVEL false
/** Pin Mode for MOSI is output.*/
#define MOSI_MODE  OUTPUT
/** Pin Mode for SCK is output. */
#define SCK_MODE  OUTPUT
//------------------------------------------------------------------------------
/**
 * @class SoftSPI
 * @brief Fast software SPI.
 */
template<const int MosiPin, const int MisoPin, const int SckPin, const int Mode = 0>
class SoftSPI {
 public:
  //----------------------------------------------------------------------------
  /** Initialize SoftSPI pins. */
  void begin() {
    fastPinConfig(MisoPin, MISO_MODE, MISO_LEVEL);
    fastPinConfig(MosiPin, MOSI_MODE, !MODE_CPHA(Mode));
    fastPinConfig(SckPin, SCK_MODE, MODE_CPOL(Mode));
  }
  void setBitOrder(uint8_t bitOrder) {
	this->msbfist = bitOrder;	  
  }
  
  void setClockDivider(uint8_t clockDevider) {
	  UNUSED(clockDevider);
  }

  void beginTransaction(SPISettings settings){
	 setBitOrder(settings.bitOrder);
  }
  void endTransaction() {}
  
  //----------------------------------------------------------------------------
  /** Soft SPI receive byte.
   * @return Data byte received.
   */
  inline __attribute__((always_inline))
  uint8_t receive() {
    uint8_t data = 0;
    receiveBit(7, &data);
    receiveBit(6, &data);
    receiveBit(5, &data);
    receiveBit(4, &data);
    receiveBit(3, &data);
    receiveBit(2, &data);
    receiveBit(1, &data);
    receiveBit(0, &data);
    return data;
  }
  //----------------------------------------------------------------------------
  /** Soft SPI send byte.
   * @param[in] data Data byte to send.
   */
  inline __attribute__((always_inline))
  void send(uint8_t data) {
    sendBit(7, data);
    sendBit(6, data);
    sendBit(5, data);
    sendBit(4, data);
    sendBit(3, data);
    sendBit(2, data);
    sendBit(1, data);
    sendBit(0, data);
  }
  //----------------------------------------------------------------------------
  /** Soft SPI transfer byte.
   * @param[in] txData Data byte to send.
   * @return Data byte received.
   */
  inline __attribute__((always_inline))
  uint8_t transfer(uint8_t txData) {
    uint8_t rxData = 0;
    transferBit(7, &rxData, txData);
    transferBit(6, &rxData, txData);
    transferBit(5, &rxData, txData);
    transferBit(4, &rxData, txData);
    transferBit(3, &rxData, txData);
    transferBit(2, &rxData, txData);
    transferBit(1, &rxData, txData);
    transferBit(0, &rxData, txData);
    return rxData;
  }

  void transfer(uint8_t *buf, size_t count){  /*reseive*/
	  uint8_t *ptr = buf;
	  for(size_t i = 0;i<count;i++,ptr++){
		  *ptr = receive();
      }		  
  }
  
   uint16_t transfer16(uint16_t data) {
	 if(msbfist == MSBFIRST) {
	   uint16_t ret =  transfer(data>>8);
	   return (ret<<8) + transfer(data &0xff);
	 }else{
	   uint16_t ret =  transfer(data &0xff);
	   return (ret + (transfer(data>>8) <<8));
	 }
   }
   
 private:
  //----------------------------------------------------------------------------
  uint8_t msbfist = 1;
  constexpr bool MODE_CPHA(const int mode) {return ((mode & 1) != 0);}
  constexpr bool MODE_CPOL(const int mode) {return ((mode & 2) != 0);}
  
  inline __attribute__((always_inline))
  void receiveBit(uint8_t bit, uint8_t* data) {
    if (MODE_CPHA(Mode)) {
      fastDigitalWrite(SckPin, !MODE_CPOL(Mode));
    }
    nop;
    nop;
    fastDigitalWrite(SckPin,
      MODE_CPHA(Mode) ? MODE_CPOL(Mode) : !MODE_CPOL(Mode));
    if (fastDigitalRead(MisoPin)) *data |= 1 << bit;
    if (!MODE_CPHA(Mode)) {
      fastDigitalWrite(SckPin, MODE_CPOL(Mode));
    }
  }
  //----------------------------------------------------------------------------
  inline __attribute__((always_inline))
  void sendBit(uint8_t bit, uint8_t data) {
    if (MODE_CPHA(Mode)) {
      fastDigitalWrite(SckPin, !MODE_CPOL(Mode));
    }
    fastDigitalWrite(MosiPin, data & (1 << bit));
    fastDigitalWrite(SckPin,
      MODE_CPHA(Mode) ? MODE_CPOL(Mode) : !MODE_CPOL(Mode));
    if (!MODE_CPHA(Mode)) {
      fastDigitalWrite(SckPin, MODE_CPOL(Mode));
    }
  }
  //----------------------------------------------------------------------------
  inline __attribute__((always_inline))
  void transferBit(uint8_t bit, uint8_t* rxData, uint8_t txData) {
    if (MODE_CPHA(Mode)) {
      fastDigitalWrite(SckPin, !MODE_CPOL(Mode));
    }
    fastDigitalWrite(MosiPin, txData & (1 << bit));
    fastDigitalWrite(SckPin,
      MODE_CPHA(Mode) ? MODE_CPOL(Mode) : !MODE_CPOL(Mode));
    if (fastDigitalRead(MisoPin)) *rxData |= 1 << bit;
    if (!MODE_CPHA(Mode)) {
      fastDigitalWrite(SckPin, MODE_CPOL(Mode));
    }
  }
  //----------------------------------------------------------------------------
};

#endif  // SoftSPI_h
/** @} */
