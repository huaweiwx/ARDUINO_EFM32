/*
  Copyright (c) 2018 huaweiwx@sina.com 2018.7.1

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _HARDWARESERIAL_H_
#define _HARDWARESERIAL_H_

#include "Stream.h"
#include "print.h"

#if !(defined(SERIAL_TX_BUFFER_SIZE) && defined(SERIAL_RX_BUFFER_SIZE))
 #define SERIAL_TX_BUFFER_SIZE 32
 #define SERIAL_RX_BUFFER_SIZE 256
#endif
 
#define SERIAL_8N1 0x06
#define SERIAL_8N2 0x0E

#define SERIAL_8E1 0x26
#define SERIAL_8E2 0x2E

#define SERIAL_8O1 0x36
#define SERIAL_8O2 0x3E

typedef struct {
    USART_TypeDef *instance;

    uint8_t txBuffer[SERIAL_TX_BUFFER_SIZE];
#if (SERIAL_TX_BUFFER_SIZE >256)
    volatile uint16_t txStart=0;
    volatile uint16_t txEnd  =0;
#else
    volatile uint8_t txStart=0;
    volatile uint8_t txEnd  =0;
#endif

    uint8_t rxBuffer[SERIAL_RX_BUFFER_SIZE];
#if (SERIAL_TX_BUFFER_SIZE >256)
    volatile uint16_t rxStart=0;
    volatile uint16_t rxEnd  =0;
#else	
    volatile uint8_t rxStart=0;
    volatile uint8_t rxEnd  =0;
#endif
}USART_Buf_TypeDef;

class HardwareSerial : public Stream {
 public:
    HardwareSerial(USART_TypeDef *instance);
    /* Pin accessors */	
    void setRouteLoc(uint8_t route = 0);

    void begin(const uint32_t baud,uint8_t config = SERIAL_8N1);
    void end();
    virtual int available(void);
    int availableForWrite(void);
    virtual int peek(void);
    virtual int read(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    using Print::write;
	operator bool() { return true; }

  private:
	USART_Buf_TypeDef *buf = NULL;
    USART_TypeDef *instance = NULL;
	uint32_t routeLoc = 0;
    uint32_t USART_ROUTE_LOCATION_LOCx = USART_ROUTE_LOCATION_LOC0;

  protected:
};

#if defined(USART0) && (USE_USART0 >0)
 	extern HardwareSerial Serial1;
#endif
#if defined(USART1) && (USE_USART1 >0)
 	extern HardwareSerial Serial2;
#endif
#if defined(USART2) && (USE_USART2 >0)
 	extern HardwareSerial Serial3;
#endif
#if defined(USART3) && (USE_USART3 >0)
 	extern HardwareSerial Serial4;
#endif
#if defined(USART4) && (USE_USART4 >0)
 	extern HardwareSerial Serial5;
#endif
#if defined(USART5) && (USE_USART5 >0)
 	extern HardwareSerial Serial6;
#endif

#if defined(UART0) && (USE_UART0 >0)
 	extern HardwareSerial Serial7;
#endif
#if defined(UART1) && (USE_UART1 >0)
 	extern HardwareSerial Serial8;
#endif

#if defined(LEUART0) && (USE_LEUART0 >0)
    extern HardwareSerial LESerial0;
#endif
#if defined(LEUART1) && (USE_LEUART1 >0)
    extern HardwareSerial LESerial1;
#endif

#ifdef MENU_SERIAL
   #define Serial MENU_SERIAL
#endif	
#endif
