
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

