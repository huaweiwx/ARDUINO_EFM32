
#if defined(EFM32GENERIC)||defined(STM32GENERIC)
OutputPin pin(LED_BUILTIN);

#elif defined(__AVR__)
#include <DirectIO.h>
Output<2> pin;

#else
#error "un supported"
#endif

void setup() {}

void loop() {
    pin = HIGH;
	delay(500);
    pin = LOW;
	delay(500);
}

