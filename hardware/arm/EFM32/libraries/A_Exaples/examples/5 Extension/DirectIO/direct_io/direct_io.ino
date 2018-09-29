/*
   direct_io.ino
   efm32 stm32  class LL_PIN is built in and GPIOPIN is it's an alias.
   OutputPin and  InputPin is a derived class of LL_PIN.
   avr serials included in the DirectIO lib.

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
  pin = HIGH; //equivalent pin.high() or pin.write(HIGH)
  delay(500);
  pin = LOW; //equivalent pin.high() or pin.write(HIGH)
  delay(500);
}

