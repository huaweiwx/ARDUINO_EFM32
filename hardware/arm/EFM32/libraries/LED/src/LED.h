/*
  LED.h - LED library head file
  huaweiwx@sina.com 2017.  All right reserved.

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
*/
#ifndef __LIB_LED_h__
#define __LIB_LED_h__

#include <Arduino.h>

#if FREERTOS >0
  #define  LED_DELAY(x) vTaskDelay(x)
#else
  #define  LED_DELAY(x) delay(x)
#endif

class LEDClass : public OutputPin{
 public:
   LEDClass(__ConstPin cpin, const bool onval=false):OutputPin(cpin), onval(onval){}
   const bool onval;

   void Init(void) {}

   inline LEDClass& operator = (bool value) __attribute__((always_inline)){
	this->write(value);
	return *this;
   }

   inline void operator  !() __attribute__((always_inline)) {
     this->toggle();
   }

   inline void on(void){
 	 this->write(onval?1:0);
   }

   inline void off(void){
 	 this->write(onval?0:1);
   }

   void flash(uint16_t timeon,uint16_t timeoff,uint8_t cnt=1){
 	 for(uint8_t i=cnt;i>0;i--){
 		this->on();
 		if(timeon)	LED_DELAY(timeon);
 		this->toggle();
 		if(timeoff)	LED_DELAY(timeoff);
 	 }
   }
};

#ifdef LED_BUILTIN
extern LEDClass Led;
#endif

#ifdef LED1_BUILTIN
extern LEDClass Led1;
#endif

#ifdef LED2_BUILTIN
extern LEDClass Led2;
#endif

#ifdef LED3_BUILTIN
extern LEDClass Led3;
#endif

#ifdef LED4_BUILTIN
extern LEDClass Led4;
#endif

#ifdef LED5_BUILTIN
extern LEDClass Led5;
#endif

#ifdef LED6_BUILTIN
extern LEDClass Led6;
#endif

#ifdef LED7_BUILTIN
extern LEDClass Led7;
#endif

#endif /*__LIB_LED_h__*/

