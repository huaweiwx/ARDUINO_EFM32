/*
   direct_io.ino
   efm32/stm32  class LL_PIN is built in and GPIOPIN is it's an alias.
   OutputPin and  InputPin is a derived class of LL_PIN.
   avr series included in the DirectIO lib.

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
#if ARDUINO_EXTEND >0
OutputPin pin(LED_BUILTIN);

#elif defined(__AVR__)
#include <DirectIO.h>
Output<2> pin;

#else
#error "un supported"
#endif

void setup() {

}

void loop() {
  pin = HIGH;
  delay(500);
  pin = LOW;
  delay(500);
}

