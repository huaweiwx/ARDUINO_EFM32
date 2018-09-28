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
uint32_t pulseIn( uint32_t ulPin, uint32_t state, uint32_t timeout);

static inline void digitalWriteHigh(uint32_t ulPin)
{
		GPIO_PinOutSet(g_Pin2PortMapArray[ulPin].GPIOx_Port,g_Pin2PortMapArray[ulPin].Pin_abstraction);
}
static inline void digitalWriteLow(uint32_t ulPin)
{
		GPIO_PinOutClear(g_Pin2PortMapArray[ulPin].GPIOx_Port,g_Pin2PortMapArray[ulPin].Pin_abstraction);
}

#ifdef __cplusplus
}
inline void pinMode(__ConstPin cPin, const uint32_t mode){
	GPIO_PinModeSet(cPin.GPIOx_Port,cPin.pin,(GPIO_Mode_TypeDef)mode, 0);
}

inline void digitalWriteHigh(__ConstPin cPin){
    GPIO_PinOutSet(cPin.GPIOx_Port,cPin.pin);
}

inline void digitalWriteLow(__ConstPin cPin){
	GPIO_PinOutClear(cPin.GPIOx_Port,cPin.pin);;
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

/*gpio low layer interface class*/
class LL_PIN{
 public:
     LL_PIN(__ConstPin cpin): cpin(cpin){};
       __ConstPin cpin;
 
 	 template<typename T = bool>
     inline  T read() {return digitalRead(cpin);}

 	 template<typename T>
     inline void write(T value){digitalWrite(cpin,value);}
  
 	 template<typename T>
     inline LL_PIN & operator = (T value){
       this->write(value);
       return *this;
     }
  
     LL_PIN& operator = (LL_PIN& rhs) {
       this->write(rhs.read());
       return *this;
     }
  
 	 template<typename T>
     inline LL_PIN & operator << (T value){
       this->write(value);
       return *this;
     }

    template<typename T> 
    inline LL_PIN & operator >> (T &value){
       value = this->read();
       return *this;
    }

    inline __attribute__((always_inline))
    void high(){digitalWriteHigh(cpin);}

    inline __attribute__((always_inline))
    void low(){digitalWriteLow(cpin);}

    template<typename T> 
    inline operator T (){
      return read();
    }

	inline void operator  !() __attribute__((always_inline)) {
      toggle();
    }

/*----- comptabled with DigitalPin ----------*/
    inline __attribute__((always_inline))
    void toggle(){digitalToggle(cpin);}

    inline __attribute__((always_inline))
    void config(uint32_t mode, bool value) {  /*compatale with digitalPin*/
	  this->mode(mode);
      this->write(value);
    }

    inline __attribute__((always_inline))
    void mode(uint32_t mode){
           pinMode(cpin,mode);
	}
	  
    inline __attribute__((always_inline))
    void attach(voidFuncPtr callback, uint32_t mode){
	   attachInterrupt(cpin, callback, mode);
    }
  
    inline __attribute__((always_inline))
    void detach(void){
	  detachInterrupt(cpin);
    }
};

class InputPin : public LL_PIN{
  public: 
	InputPin(__ConstPin cpin, bool initial_value = 1): LL_PIN(cpin){
			digitalWrite(cpin,initial_value);
			pinMode(cpin,INPUT);
	}
	  
    inline operator bool (){
       return read();
    }
	uint32_t pulseIn(bool state = false, uint32_t timeout = 1000000L )
	{
		// Cache the port and bit of the pin in order to speed up the
		// pulse width measuring loop and achieve finer resolution.
		// Calling digitalRead() instead yields much coarser resolution.
		uint32_t startMicros = micros();
		
		// wait for any previous pulse to end
		while (read() == state) {
			if (micros()-startMicros > timeout)
			return 0;
		}
		
		// wait for the pulse to start
		while (read() != state) {
			if (micros()-startMicros > timeout)
			return 0;
		}
		
		uint32_t start = micros();
		// wait for the pulse to stop
		while (read() == state) {
			if (micros()-startMicros > timeout)
			return 0;
		}
		return (micros() - start);
	}
};

class OutputPin : public LL_PIN{
	public: 
	  OutputPin(__ConstPin cpin, bool initial_value = 0): LL_PIN(cpin) {
			digitalWrite(cpin,initial_value);
			pinMode(cpin,OUTPUT);
		}

    void pulse(uint32_t delaycnt = 0, bool value = true) { 
       this->write(value); 
	   if(delaycnt){
		   for(volatile uint32_t i = delaycnt;i>0;i--);
	   }
       this->toggle(); 
    }

    template<typename T>
    inline OutputPin & operator = (T value) {
       LL_PIN::write(value);
       return *this;
    }
};

#define GPIOPIN LL_PIN

#endif /*__cplusplus*/
#endif /*__EFM32GPIO_H__*/
