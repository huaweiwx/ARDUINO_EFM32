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


#ifndef __EFM32_H__
#define __EFM32_H__

#include <stddef.h>
#include "em_device.h"
#include "efm32_hal/emlib.h"
#include "efm32_build_defines.h"
#include "utils/utils_all.h"

//mydriver:
#include "armclock.h"
#include "gpiointerrupt.h"

#define GPIOA	gpio->P[0]
#define GPIOB	gpio->P[1]
#define GPIOC	gpio->P[2]
#define GPIOD	gpio->P[3]
#define GPIOE	gpio->P[4]

//GPIO_PIN
enum {
  GPIO_PIN_0,
  GPIO_PIN_1,
  GPIO_PIN_2,
  GPIO_PIN_3, 
  GPIO_PIN_4,
  GPIO_PIN_5,
  GPIO_PIN_6,
  GPIO_PIN_7,
  GPIO_PIN_8,
  GPIO_PIN_9,
  GPIO_PIN_10,
  GPIO_PIN_11,
  GPIO_PIN_12,
  GPIO_PIN_13,
  GPIO_PIN_14,
  GPIO_PIN_15,
};


// #define BUTTON		gpioPortE, 0
#define LEDx_PORT	    gpioPortD
#define LED1		    LEDx_PORT, 6

#define HOST_TX2	gpioPortE, 10
#define HOST_RX2	gpioPortE, 11

#define BUTTON_SETTLE_TIME	10

#define RTC_FREQ    		32768

#include "variant.h"
#include "efm32_pin_list.h"  
#endif
