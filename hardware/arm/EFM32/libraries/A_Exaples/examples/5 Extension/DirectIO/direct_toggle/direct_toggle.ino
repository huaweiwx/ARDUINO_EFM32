/*
   direct_io.ino
   efm32 stm32  class LL_PIN is built in and GPIOPIN is it's an alias.
   OutputPin and  InputPin is a derived class of LL_PIN.
   avr series included in the DirectIO lib

   class func list:
     high()
     low()
     toggle()
     write(boll)
     read()
     pulse()
     pulseIn()
     operate =
     operate ()
*/


//Check the Environment
#if defined(EFM32GENERIC)||defined(STM32GENERIC)
OutputPin out(LED_BUILTIN);

#elif defined(__AVR__)
#include <DirectIO.h>
Output<2> out;

#else
#error "un supported"
#endif

void setup() {}

void loop() {
  out.toggle();
  delay(500);
}

