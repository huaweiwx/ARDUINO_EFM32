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

#define GPIOA	GPIO->P[0]
#define GPIOB	GPIO->P[1]
#define GPIOC	GPIO->P[2]
#define GPIOD	GPIO->P[3]
#define GPIOE	GPIO->P[4]
#define GPIOF	GPIO->P[5]

//GPIO_PIN compatiblet with stm32generic
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

#include "avr_emulation.h"
#include "efm32_build_defines.h"
#include "variant.h"
#include "efm32_pin_list.h"  
#include "efm32gpio.h"

//#include "utils/utils_all.h"
#include "utils/utils_all.h"

//mydriver:
#include "armclock.h"
#include "gpiointerrupt.h"
#include "efm32adc.h"
#include "efm32pwm.h"
#include "efm32dac.h"
#include "efm32weak.h"
#endif
