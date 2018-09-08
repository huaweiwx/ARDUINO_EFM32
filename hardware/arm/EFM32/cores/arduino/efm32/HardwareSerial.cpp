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

#include "arduino.h"

#if defined(USART0)&& (USE_USART0 >0)
USART_Buf_TypeDef* USART0_buf = 0;
#endif
#if defined(USART1)&& (USE_USART1 >0)
USART_Buf_TypeDef* USART1_buf = 0;
#endif
#if defined(USART2)&& (USE_USART2 >0)
USART_Buf_TypeDef* USART2_buf = 0;
#endif
#if defined(USART3)&& (USE_USART3 >0)
USART_Buf_TypeDef* USART3_buf = 0;
#endif
#if defined(USART4)&& (USE_USART4 >0)
USART_Buf_TypeDef* USART4_buf = 0;
#endif
#if defined(USART5)&& (USE_USART5 >0)
USART_Buf_TypeDef* USART5_buf = 0;
#endif
#if  defined(UART0) && (USE_UART0 >0)
USART_Buf_TypeDef* UART0_buf = 0;
#endif
#if  defined(UART1) && (USE_UART1 >0)
USART_Buf_TypeDef* UART1_buf = 0;
#endif
#if defined(LEUART0)&& (USE_LEUART0 >0)
USART_Buf_TypeDef* LEUART0_buf = 0;
#endif
#if defined(LEUART1)&& (USE_LEUART1 >0)
USART_Buf_TypeDef* LEUART1_buf = 0;
#endif

HardwareSerial::HardwareSerial(USART_TypeDef *instance) {
  this->instance = instance;
}

void HardwareSerial::setRouteLoc(uint8_t route) {
      routeLoc = route;
      USART_ROUTE_LOCATION_LOCx = route<<8;
}

void HardwareSerial::begin(uint32_t baud, uint8_t config)
{
  uint8_t type = 0;
  if (buf == NULL) {
    buf = (USART_Buf_TypeDef*)malloc(sizeof(USART_Buf_TypeDef));
    buf->instance = this->instance;
  }

#if  defined(USART0)&& (USE_USART0 >0)
  if (this->instance == USART0) {
    USART0_buf = buf;
    USART_Reset(USART0);
    /* To avoid false start, configure output as high */
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART0_TX_PORT(this->routeLoc),
                    AF_USART0_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART0_RX_PORT(this->routeLoc),
                    AF_USART0_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for USART0 */
    CMU_ClockEnable(cmuClock_USART0, true);
  }
#endif

#if   defined(USART1)&& (USE_USART1 >0)
  if (this->instance == USART1) {
    USART1_buf = buf;
    USART_Reset(USART1);
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART1_TX_PORT(this->routeLoc),
                    AF_USART1_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART1_RX_PORT(this->routeLoc),
                    AF_USART1_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for USART1 */
    CMU_ClockEnable(cmuClock_USART1, true);
  }
#endif

#if   defined(USART2)&& (USE_USART2 >0)
  if (this->instance == USART2) {
    USART2_buf = buf;
    USART_Reset(USART2);
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART2_TX_PORT(this->routeLoc),
                    AF_USART2_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART2_RX_PORT(this->routeLoc),
                    AF_USART2_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for USART1 */
    CMU_ClockEnable(cmuClock_USART2, true);
  }
#endif

#if   defined(USART3)&& (USE_USART3 >0)
  if (this->instance == USART3) {
    USART3_buf = buf;
    USART_Reset(USART3);
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART3_TX_PORT(this->routeLoc),
                    AF_USART3_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART3_RX_PORT(this->routeLoc),
                    AF_USART3_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for USART1 */
    CMU_ClockEnable(cmuClock_USART3, true);
  }
#endif

#if   defined(USART4)&& (USE_USART4 >0)
  if (this->instance == USART4) {
    USART4_buf = buf;
    USART_Reset(USART4);
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART4_TX_PORT(this->routeLoc),
                    AF_USART4_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART4_RX_PORT(this->routeLoc),
                    AF_USART4_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for USART1 */
    CMU_ClockEnable(cmuClock_USART4, true);
  }
#endif

#if   defined(USART5)&& (USE_USART5 >0)
  if (this->instance == USART5) {
    USART5_buf = buf;
    USART_Reset(USART5);
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART5_TX_PORT(this->routeLoc),
                    AF_USART5_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_USART5_RX_PORT(this->routeLoc),
                    AF_USART5_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for USART1 */
    CMU_ClockEnable(cmuClock_USART5, true);
  }
#endif
#if   defined(UART0)&& (USE_UART0 >0)
  if (this->instance == UART0) {
    type = 1;
    UART0_buf = buf;
    UART_Reset(UART0);
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_UART0_TX_PORT(this->routeLoc),
                    AF_UART0_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_UART0_RX_PORT(this->routeLoc),
                    AF_USART5_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for USART1 */
    CMU_ClockEnable(cmuClock_UART0, true);
  }
#endif
#if   defined(UART1)&& (USE_UART1 >0)
  if (this->instance == UART1) {
    type = 1;
    UART0_buf = buf;
    UART_Reset(UART1);
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_UART1_TX_PORT(this->routeLoc),
                    AF_UART1_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_UART1_RX_PORT(this->routeLoc),
                    AF_UART1_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for USART1 */
    CMU_ClockEnable(cmuClock_UART1, true);
  }
#endif
#if defined(LEUART0)&& (USE_LEUART0 >0)
  if (this->instance == (USART_TypeDef *)LEUART0) {
    type = 2;
    LEUART0_buf = buf;
    LEUART_Reset(LEUART0);
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_LEUART0_TX_PORT(this->routeLoc),
                    AF_LEUART0_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_LEUART0_RX_PORT(this->routeLoc),
                    AF_LEUART0_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for LEUART0 */
  /* Enable CORE LE clock in order to access LE modules */
    CMU_ClockEnable(cmuClock_HFLE, true); // Necessary for accessing LE modules
	
//    CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO); // Set a reference clock
    CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFRCO); // Set a reference clock

    CMU_ClockEnable(cmuClock_LEUART0, true);
    CMU_ClockDivSet(cmuClock_LEUART0, cmuClkDiv_1); // Don't prescale LEUART clock

    LEUART_Init_TypeDef init = LEUART_INIT_DEFAULT;
    init.enable = leuartDisable;
    LEUART_Init(LEUART0, &init);
    LEUART0->IEN = LEUART_IEN_RXDATAV;
    LEUART0->ROUTE = USART_ROUTE_LOCATION_LOCx | LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN;
  }
#endif
#if   defined(LEUART1)&& (USE_LEUART1 >0)
  if (this->instance == (USART_TypeDef *)LEUART1) {
    type = 2;
    LEUART1_buf = buf;
    LEUART_Reset(LEUART1);
    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_LEUART1_TX_PORT(this->routeLoc),
                    AF_LEUART1_TX_PIN(this->routeLoc),
                    gpioModePushPull, 1);

    GPIO_PinModeSet((GPIO_Port_TypeDef)AF_LEUART1_RX_PORT(this->routeLoc),
                    AF_LEUART1_RX_PIN(this->routeLoc),
                    gpioModeInputPull, 0);

    /* Enable clock for LEUART1 */
    CMU_ClockEnable(cmuClock_LEUART1, true);
    LEUART_Init_TypeDef init = LEUART_INIT_DEFAULT;
    LEUART_InitAsync(LEUART1, &init);
    LEUART1->IEN = LEUART_IEN_RXDATAV;
    LEUART1->ROUTE = USART_ROUTE_LOCATION_LOCx | LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN;
  }
#endif
  if (this->instance == (USART_TypeDef *)LEUART0) {
    this->instance->IFC = _LEUART_IFC_MASK;
  } else {
    USART_InitAsync_TypeDef initasync = USART_INITASYNC_DEFAULT;
    initasync.baudrate = baud;
    initasync.databits = usartDatabits8;

    if (config < 0x0f) {
      initasync.parity = usartNoParity;   /* No parity. */
    } else if (config < 0x2f) {
      initasync.parity = usartEvenParity; /* Even parity. */
    } else if (config < 0x3f) {
      initasync.parity =  usartOddParity; /* Odd parity. */
    }

    if ((config & 0x0f) == 0x0E) {
      initasync.stopbits = usartStopbits2; /* 1 stopbits. */
    } else {
      initasync.stopbits = usartStopbits1; /* 2 stopbits. */
    }

    initasync.oversampling = usartOVS16;
#if defined( USART_INPUT_RXPRS ) && defined( USART_CTRL_MVDIS )
    initasync.mvdis = 0;
    initasync.prsRxEnable = 0;
    initasync.prsRxCh = usartPrsRxCh0;
#endif
    USART_InitAsync(this->instance, &initasync);
    this->instance->IFC = _USART_IFC_MASK;
  }
#if defined(USART0)&& (USE_USART0 >0)
  if (this->instance == USART0) {
    NVIC_ClearPendingIRQ(USART0_RX_IRQn);
    NVIC_EnableIRQ(USART0_RX_IRQn);
    NVIC_ClearPendingIRQ(USART0_TX_IRQn);
    NVIC_EnableIRQ(USART0_TX_IRQn);
  }
#endif
#if defined(USART1)&& (USE_USART1 >0)
  if (this->instance == USART1) {
    NVIC_ClearPendingIRQ(USART1_RX_IRQn);
    NVIC_EnableIRQ(USART1_RX_IRQn);
    NVIC_ClearPendingIRQ(USART1_TX_IRQn);
    NVIC_EnableIRQ(USART1_TX_IRQn);
  }
#endif
#if defined(USART2)&& (USE_USART2 >0)
  if (this->instance == USART2) {
    NVIC_ClearPendingIRQ(USART2_RX_IRQn);
    NVIC_EnableIRQ(USART2_RX_IRQn);
    NVIC_ClearPendingIRQ(USART2_TX_IRQn);
    NVIC_EnableIRQ(USART2_TX_IRQn);
  }
#endif
#if defined(USART3)&& (USE_USART3 >0)
  if (this->instance == USART3) {
    NVIC_ClearPendingIRQ(USART3_RX_IRQn);
    NVIC_EnableIRQ(USART3_RX_IRQn);
    NVIC_ClearPendingIRQ(USART3_TX_IRQn);
    NVIC_EnableIRQ(USART3_TX_IRQn);
  }
#endif
#if defined(USART4)&& (USE_USART4 >0)
  if (this->instance == USART4) {
    NVIC_ClearPendingIRQ(USART4_RX_IRQn);
    NVIC_EnableIRQ(USART4_RX_IRQn);
    NVIC_ClearPendingIRQ(USART4_TX_IRQn);
    NVIC_EnableIRQ(USART4_TX_IRQn);
  }
#endif
#if defined(USART5)&& (USE_USART5 >0)
  if (this->instance == USART5) {
    NVIC_ClearPendingIRQ(USART5_RX_IRQn);
    NVIC_EnableIRQ(USART5_RX_IRQn);
    NVIC_ClearPendingIRQ(USART5_TX_IRQn);
    NVIC_EnableIRQ(USART5_TX_IRQn);
  }
#endif
#if defined(UART0)&& (USE_UART0 >0)
  if (this->instance == UART0) {
    NVIC_ClearPendingIRQ(UART0_RX_IRQn);
    NVIC_EnableIRQ(UART0_RX_IRQn);
    NVIC_ClearPendingIRQ(UART0_TX_IRQn);
    NVIC_EnableIRQ(UART0_TX_IRQn);
  }
#endif
#if defined(UART1)&& (USE_UART1 >0)
  if (this->instance == UART1) {
    NVIC_ClearPendingIRQ(UART1_RX_IRQn);
    NVIC_EnableIRQ(UART1_RX_IRQn);
    NVIC_ClearPendingIRQ(UART1_TX_IRQn);
    NVIC_EnableIRQ(UART1_TX_IRQn);
  }
#endif
#if defined(LEUART0)&& (USE_LEUART0 >0)
  if (this->instance == (USART_TypeDef *)LEUART0) {
    NVIC_ClearPendingIRQ(LEUART0_IRQn);
    NVIC_EnableIRQ(LEUART0_IRQn);
    LEUART0->IEN = LEUART_IEN_RXDATAV;
    LEUART_Enable(LEUART0, leuartEnable);

  }
#endif
#if defined(LEUART1)&& (USE_LEUART1 >0)
  if (this->instance == (USART_TypeDef *)LEUART1) {
    NVIC_ClearPendingIRQ(LEUART1_IRQn);
    NVIC_EnableIRQ(LEUART1_IRQn);
  }
#endif
  if (this->instance == (USART_TypeDef *)LEUART0) {
  } else {
    this->instance->IEN = USART_IEN_RXDATAV;
    this->instance->ROUTE |=  USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_LOCATION_LOCx;
  }
}

void HardwareSerial::end(void) {

}

int HardwareSerial::available(void)
{
  if (buf->rxEnd >= buf->rxStart) return (buf->rxEnd - buf->rxStart); /*0~ SERIAL_RX_BUFFER_SIZE-1*/
  return SERIAL_RX_BUFFER_SIZE + buf->rxEnd - buf->rxStart;
}

int HardwareSerial::availableForWrite(void)
{
  if (buf->txEnd >= buf->txStart) return SERIAL_TX_BUFFER_SIZE - 1 - (buf->txEnd - buf->txStart); /*SERIAL_TX_BUFFER_SIZE-1 ~ 0*/
  return buf->txStart - buf->txEnd - 1;
}

int HardwareSerial::peek(void)
{
  if (available()) {
    return buf->rxBuffer[buf->rxStart % SERIAL_RX_BUFFER_SIZE];
  } else {
    return -1;
  }
}

void HardwareSerial::flush(void) {
  while (buf->txEnd != buf-> txStart);
}

int HardwareSerial::read(void) {
  if (available()) {
    uint8_t rtn =  buf->rxBuffer[buf->rxStart++];
    buf->rxStart %= SERIAL_RX_BUFFER_SIZE;
    return rtn;
  } else {
    return -1;
  }
}

size_t HardwareSerial::write(unsigned char ch) {
  while (availableForWrite() == 0);   /*wait*/
  buf->txBuffer[buf->txEnd++] = ch;
  buf->txEnd %= SERIAL_TX_BUFFER_SIZE;
  if (this->instance == (USART_TypeDef *)LEUART0) {
    LEUART_IntEnable((LEUART_TypeDef *)buf->instance, LEUART_IEN_TXC);
    LEUART_IntSet((LEUART_TypeDef *)buf->instance, LEUART_IFS_TXC);
  } else {
    USART_IntEnable(buf->instance, USART_IEN_TXC);
    USART_IntSet(buf->instance, USART_IFS_TXC);
  }
  return 1;
}
#if defined(UART0)||defined(UART1)
void UART_TXCallback(USART_Buf_TypeDef *interruptUART) {
  if (interruptUART->txStart != interruptUART->txEnd) {
    UART_Tx((UART_TypeDef *)interruptUART->instance, interruptUART->txBuffer[interruptUART->txStart++]);
    interruptUART->txStart %= SERIAL_TX_BUFFER_SIZE;
  }
}
void UART_RXCallback(USART_Buf_TypeDef *interruptUART) {
  if (((interruptUART->rxEnd + 1) % SERIAL_RX_BUFFER_SIZE) == interruptUART->txStart) return; /*over*/
  interruptUART->rxBuffer[interruptUART->rxEnd++] = USART_Rx((UART_TypeDef *)interruptUART->instance);
  interruptUART->rxEnd %= SERIAL_RX_BUFFER_SIZE;
}
#endif

void USART_TXCallback(USART_Buf_TypeDef *interruptUART) {
  if (interruptUART->txStart != interruptUART->txEnd) {
    USART_Tx(interruptUART->instance, interruptUART->txBuffer[interruptUART->txStart++]);
    interruptUART->txStart %= SERIAL_TX_BUFFER_SIZE;
  }
}

void USART_RXCallback(USART_Buf_TypeDef *interruptUART) {
  if (((interruptUART->rxEnd + 1) % SERIAL_RX_BUFFER_SIZE) == interruptUART->txStart) return; /*over*/
  interruptUART->rxBuffer[interruptUART->rxEnd++] = USART_Rx(interruptUART->instance);
  interruptUART->rxEnd %= SERIAL_RX_BUFFER_SIZE;
}

void LEUART_TXCallback(USART_Buf_TypeDef *interruptUART) {
  if (interruptUART->txStart != interruptUART->txEnd) {
    LEUART_Tx((LEUART_TypeDef *)interruptUART->instance, interruptUART->txBuffer[interruptUART->txStart++]);
    interruptUART->txStart %= SERIAL_TX_BUFFER_SIZE;
  }
}

void LEUART_RXCallback(USART_Buf_TypeDef *interruptUART) {
  if (((interruptUART->rxEnd + 1) % SERIAL_RX_BUFFER_SIZE) == interruptUART->txStart) return; /*over*/
  interruptUART->rxBuffer[interruptUART->rxEnd++] = LEUART_Rx((LEUART_TypeDef *)interruptUART->instance);
  interruptUART->rxEnd %= SERIAL_RX_BUFFER_SIZE;
}

#if defined(USART0) && (USE_USART0 >0)
extern "C"
void USART0_RX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART0);
  USART_IntClear(USART0, flags);
  if (flags & USART_IF_RXDATAV) USART_RXCallback(USART0_buf);
}

extern "C"
void USART0_TX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART0);
  USART_IntClear(USART0, flags);
  if (flags & USART_IF_TXC) USART_TXCallback(USART0_buf);
}
HardwareSerial Serial1(USART0);
#endif

#if defined(USART1) && (USE_USART1 >0)
extern "C"
void USART1_RX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART1);
  USART_IntClear(USART1, flags);
  if (flags & USART_IF_RXDATAV) USART_RXCallback(USART1_buf);
}
extern "C"
void USART1_TX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART1);
  USART_IntClear(USART1, flags);
  if (flags & USART_IF_TXC) USART_TXCallback(USART1_buf);
}
HardwareSerial Serial2(USART1);
#endif

#if defined(USART2) && (USE_USART2 >0)
extern "C"
void USART2_RX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART2);
  USART_IntClear(USART2, flags);
  if (flags & USART_IF_RXDATAV) USART_RXCallback(USART2_buf);
}
extern "C"
void USART2_TX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART2);
  USART_IntClear(USART2, flags);
  if (flags & USART_IF_TXC) USART_TXCallback(USART2_buf);
}
HardwareSerial Serial3(USART2);
#endif

#if defined(USART3) && (USE_USART3 >0)
extern "C"
void USART3_RX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART3);
  USART_IntClear(USART3, flags);
  if (flags & USART_IF_RXDATAV) USART_RXCallback(USART3_buf);
}
extern "C"
void USART3_TX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART3);
  USART_IntClear(USART3, flags);
  if (flags & USART_IF_TXC) USART_TXCallback(USART3_buf);
}
HardwareSerial Serial4(USART3);
#endif

#if defined(USART4) && (USE_USART4 >0)
extern "C"
void USART4_RX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART4);
  USART_IntClear(USART4, flags);
  if (flags & USART_IF_RXDATAV) USART_RXCallback(USART4_buf);
}
extern "C"
void USART4_TX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART4);
  USART_IntClear(USART4, flags);
  if (flags & USART_IF_TXC) USART_TXCallback(USART4_buf);
}
HardwareSerial Serial5(USART4);
#endif

#if defined(USART5) && (USE_USART5 >0)
extern "C"
void USART5_RX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART5);
  USART_IntClear(USART5, flags);
  if (flags & USART_IF_RXDATAV) USART_RXCallback(USART5_buf);
}
extern "C"
void USART5_TX_IRQHandler(void)
{
  uint32_t flags = USART_IntGet(USART5);
  USART_IntClear(USART5, flags);
  if (flags & USART_IF_TXC) USART_TXCallback(USART5_buf);
}
HardwareSerial Serial6(USART5);
#endif

#if defined(UART0) && (USE_UART0 >0)
extern "C"
void UART0_RX_IRQHandler(void)
{
  uint32_t flags = UART_IntGet(UART0);
  UART_IntClear(UART0, flags);
  if (flags & UART_IF_RXDATAV) UART_RXCallback(UART0_buf);
}
extern "C"
void UART0_TX_IRQHandler(void)
{
  uint32_t flags = UART_IntGet(UART0);
  UART_IntClear(UART0, flags);
  if (flags & UART_IF_TXC) UART_TXCallback(UART0_buf);
}
HardwareSerial Serial7((USART_TypeDef *)UART0);
#endif

#if defined(UART1) && (USE_UART1 >0)
extern "C"
void UART1_RX_IRQHandler(void)
{
  uint32_t flags = UART_IntGet(UART1);
  UART_IntClear(UART1, flags);
  if (flags & UART_IF_RXDATAV) UART_RXCallback(UART1_buf);
}
extern "C"
void UART1_TX_IRQHandler(void)
{
  uint32_t flags = UART_IntGet(UART1);
  UART_IntClear(UART1, flags);
  if (flags & UART_IF_TXC) UART_TXCallback(UART1_buf);
}
HardwareSerial Serial8((USART_TypeDef *)UART1);
#endif

#if defined(LEUART0) && (USE_LEUART0 >0)
extern "C"
void LEUART0_IRQHandler(void)
{
  uint32_t flags = LEUART_IntGet(LEUART0);
  LEUART_IntClear(LEUART0, flags);
  if (flags & LEUART_IF_RXDATAV) LEUART_RXCallback(LEUART0_buf);
  if (flags & LEUART_IF_TXC)     LEUART_TXCallback(LEUART0_buf);
}
HardwareSerial LESerial0((USART_TypeDef *)LEUART0);
#endif

#if defined(LEUART1) && (USE_LEUART1 >0)
extern "C"
void LEUART1_IRQHandler(void)
{
  uint32_t flags = LEUART_IntGet(LEUART1);
  LEUART_IntClear(LEUART1, flags);
  if (flags & LEUART_IF_RXDATAV) LEUART_RXCallback(LEUART1_buf);
  if (flags & LEUART_IF_TXC)     LEUART_TXCallback(LEUART1_buf);
}

HardwareSerial LESerial1((USART_TypeDef *)LEUART1);
#endif
