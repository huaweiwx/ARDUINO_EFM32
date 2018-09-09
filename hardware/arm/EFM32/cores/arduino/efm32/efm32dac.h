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

 
#ifndef _EFMM32_DAC_H_
#define _EFMM32_DAC_H_

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_dac.h"


#include "efm32_build_defines.h"
#include "variant.h"
#include "wiring_constants.h"
#include "wiring_digital.h"

#ifdef __cplusplus
extern "C"{
#endif

void     setDacRef(uint32_t ref);
uint32_t dacValueCalcul(float vOut, float vRef);
uint32_t dacValueCalculRef(float vOut);
void     dacWrite(uint32_t channel,uint32_t dacValue);

#ifdef __cplusplus
} //extern "C"{
	
template<unsigned int ch =0>
class DAC {
  public:
	inline void Init(uint32_t ref = dacRef1V25){
		setDacRef(ref);
	}
	inline void reference(uint32_t ref){
		setDacRef(ref);
	}
	inline void write(uint32_t val){
		dacWrite(ch,val);
	}
	inline void enable(bool en = true){
        DAC_Enable(DAC0,ch,en);
	}
	inline void pause(void){
        enable(false);
	}
	inline void resume(void){
		enable();
	}
    inline uint32_t valueCalcul(float vOut){
		return dacValueCalculRef(vOut);
    }
private:
    
};

extern DAC<>dac;
#endif



#endif