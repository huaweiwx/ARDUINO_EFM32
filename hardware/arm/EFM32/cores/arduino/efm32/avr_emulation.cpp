/*
  EMF32ARDUINO avr_emulation.cpp
  
  Copyright (c) 2018 huaweiwx@sina.com 2018.9.1

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Arduino.h"

#if  _GPIO_PORT_A_PIN_MASK >0
DDRemulation DDRA(gpioPortA,_GPIO_PORT_A_PIN_MASK);
#endif
#if  _GPIO_PORT_B_PIN_MASK >0
DDRemulation DDRB(gpioPortB,_GPIO_PORT_B_PIN_MASK);
#endif
#if  _GPIO_PORT_C_PIN_MASK >0
DDRemulation DDRC(gpioPortC,_GPIO_PORT_C_PIN_MASK);
#endif
#if  _GPIO_PORT_D_PIN_MASK >0
DDRemulation DDRD(gpioPortD,_GPIO_PORT_D_PIN_MASK);
#endif
#if  _GPIO_PORT_E_PIN_MASK >0
DDRemulation DDRE(gpioPortE,_GPIO_PORT_E_PIN_MASK);
#endif
#if  _GPIO_PORT_F_PIN_MASK >0
DDRemulation DDRF(gpioPortF,_GPIO_PORT_F_PIN_MASK);
#endif
#if  _GPIO_PORT_G_PIN_MASK >0
DDRemulation DDRA(gpioPortG,_GPIO_PORT_G_PIN_MASK);
#endif
#if  _GPIO_PORT_H_PIN_MASK >0
DDRemulation DDRH(gpioPortH,_GPIO_PORT_H_PIN_MASK);
#endif
#if  _GPIO_PORT_I_PIN_MASK >0
DDRemulation DDRI(gpioPortI,_GPIO_PORT_I_PIN_MASK);
#endif
#if  _GPIO_PORT_J_PIN_MASK >0
DDRemulation DDRJ(gpioPortJ,_GPIO_PORT_J_PIN_MASK);
#endif
#if  _GPIO_PORT_K_PIN_MASK >0
DDRemulation DDRK(gpioPortK,_GPIO_PORT_K_PIN_MASK);
#endif
