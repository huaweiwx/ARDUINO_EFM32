/*
  EMF32ARDUINO  avr_emulation.h
  
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


#ifndef __ARREMULATION_H__
#define __ARREMULATION_H__

#define PORTA  GPIOA.DOUT
#define  PINA  GPIOA.DIN
#define PORTB  GPIOB.DOUT
#define  PINB  GPIOB.DIN
#define PORTC  GPIOC.DOUT
#define  PINC  GPIOC.DIN
#define PORTD  GPIOD.DOUT
#define  PIND  GPIOD.DIN
#define PORTE  GPIOE.DOUT
#define  PINE  GPIOE.DIN
#define PORTF  GPIOF.DOUT
#define  PINF  GPIOF.DIN

#ifdef __cplusplus

class DDRemulation
{
  public:
    DDRemulation(const GPIO_Port_TypeDef port, uint16_t mask): port(port),mask(mask){}
	const GPIO_Port_TypeDef port;
	uint16_t mask;

    void mode(unsigned int pin, GPIO_Mode_TypeDef mode,unsigned int out = 0) {
		GPIO_PinModeSet(port,pin,mode,out);
    }

    operator int () const __attribute__((always_inline)) {
		return save_ddr;
    }

    DDRemulation& operator = (uint16_t val){
      this->save_ddr = val & mask;
	  for(uint8_t i = 0;i<16;i++){
		  if(bitRead(mask,i)){
			GPIO_PinModeSet(port,i, bitRead(val,i)?gpioModePushPull:gpioModeInput, 0);
 	      }
	  }
      return *this;
    }

    inline DDRemulation& operator |= (int val) __attribute__((always_inline)) {
	  for(uint8_t i = 0;i<16;i++){
		  if((bitRead(mask,i))&(~save_ddr)){
			 if(bitRead(val,i)){
			    GPIO_PinModeSet(port,i,gpioModePushPull,0);
				bitSet(save_ddr,i);
 	         }			 
		  }
	  }
      return *this;
    }
	
    inline DDRemulation& operator &= (int val) __attribute__((always_inline)) {
	  for(uint8_t i = 0;i<16;i++){
		  if(bitRead((save_ddr & mask),i)){
			 if(!bitRead(val,i)){
			    GPIO_PinModeSet(port,i,gpioModeInput,0);
				bitClear(save_ddr,i);
 	         }
		  }
	  }
      return *this;
    }
  private:
    uint16_t save_ddr = 0;	
};

#if  _GPIO_PORT_A_PIN_MASK >0
extern DDRemulation DDRA;
#endif
#if  _GPIO_PORT_B_PIN_MASK >0
extern DDRemulation DDRB;
#endif
#if  _GPIO_PORT_C_PIN_MASK >0
extern DDRemulation DDRC;
#endif
#if  _GPIO_PORT_D_PIN_MASK >0
extern DDRemulation DDRD;
#endif
#if  _GPIO_PORT_E_PIN_MASK >0
extern DDRemulation DDRE;
#endif
#if  _GPIO_PORT_F_PIN_MASK >0
extern DDRemulation DDRF;
#endif
#if  _GPIO_PORT_G_PIN_MASK >0
extern DDRemulation DDRG;
#endif
#if  _GPIO_PORT_H_PIN_MASK >0
extern DDRemulation DDRH;
#endif
#if  _GPIO_PORT_I_PIN_MASK >0
extern DDRemulation DDRI;
#endif
#if  _GPIO_PORT_J_PIN_MASK >0
extern DDRemulation DDRJ;
#endif
#if  _GPIO_PORT_K_PIN_MASK >0
extern DDRemulation DDRK;
#endif

#endif //__cplusplus
#endif //__ARREMULATION_H__
