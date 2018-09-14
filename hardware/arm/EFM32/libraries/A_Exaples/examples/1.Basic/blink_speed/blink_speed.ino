/*
  blink_speed.ino arduino gpio speed test example for efm32g222fx
  F_CPU at 29 mHz
    toggle speed:  360 us in cplus mode
                   681 us in use bitband
                  1290 us in c mode

  by  huawei <huaweiwx@sina.com> 2019.9.10
*/

#define GPIOMODE 0

#if GPIOMODE == 2
#include "utils/bitband.h"
BB_PIN led(LED_BUILTIN);
#elif GPIOMODE == 1  /*cplus mode*/
#define  led LED_BUILTIN
#else  /*c mode*/
uint32_t led = LED_BUILTIN;
#endif

void setup() {
  // put your setup code here, to run once:

  /* setup alternate location default is 0# */
  Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 9600bps 8N1) */
  delay(2000);
#if   GPIOMODE == 2
  led.mode(OUTPUT);
#else
  pinMode(led, OUTPUT);
#endif
  uint32_t timers = getTimers(1000);
  Serial.println();
  Serial.print(1000000 / timers);
  Serial.print(" khz  Timer elapsed:");
  Serial.println(timers);
  Serial.print(" us");
}

void loop() {
#if   GPIOMODE == 2
  led.toggle();
#else
  digitalToggle(led);
#endif
  delay(500);
}

uint32_t getTimers(uint32_t count) {
  uint32_t timeBegan, loopTimeElapsed, timeElapsed, i;
  i = 0;
  timeBegan = micros();
  while (i < count) {
    i++;
  }
  loopTimeElapsed = (micros() - timeBegan); // Time taken to do nothing but increment a variable
  i = 0;
  while (i < count) {
#if   GPIOMODE == 2
    led.toggle();
#else
    digitalToggle(led);
#endif
    i++;
  }
  timeElapsed = (micros() - timeBegan - loopTimeElapsed); // Time taken to read a pin
  return timeElapsed;
}

