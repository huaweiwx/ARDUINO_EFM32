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

#ifndef __EFM32GPIO_H__
#define __EFM32GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif

extern void pinMode( uint32_t dwPin, uint32_t dwMode ) ;
extern void digitalWrite( uint32_t dwPin, uint32_t dwVal ) ;
extern int digitalRead( uint32_t ulPin ) ;
extern void digitalToggle( uint32_t ulPin );

#ifdef __cplusplus
}
inline void pinMode(__ConstPin cPin, const uint32_t mode){
	 		GPIO_PinModeSet(cPin.GPIOx_Port,cPin.pin,(GPIO_Mode_TypeDef)mode, 0);
}

template<typename T>
inline void digitalWrite(__ConstPin cPin, T val )
{
	if(val) {
		GPIO_PinOutSet(cPin.GPIOx_Port,cPin.pin);
	}else{
		GPIO_PinOutClear(cPin.GPIOx_Port,cPin.pin);;
	}
}

template<typename T>
inline T digitalRead(__ConstPin cPin)
{
	/* can add a section here to see if pin is readable */	
	return bitRead(GPIO_PortInGet(cPin.GPIOx_Port),cPin.pin);
}

inline void digitalToggle(__ConstPin cPin)
{
	/* can add a section here to see if pin is readable */
	GPIO_PinOutToggle(cPin.GPIOx_Port,cPin.pin);
}


#endif /*__cplusplus*/
#endif /*__EFM32GPIO_H__*/
