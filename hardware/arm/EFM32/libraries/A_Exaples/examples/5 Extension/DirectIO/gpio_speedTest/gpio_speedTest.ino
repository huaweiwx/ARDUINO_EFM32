/*
  gpio_speedTest.ino arduino gpio speed test example for stm32/efm32

   mode 4:  use avr emulate;
   mode 3:  use LL_PIN class
   mode 2:  use BB_PIN class (for M3/M4 only others LL_BIN)
   mode 1:  cplus mode
   mode 0:  c mode

   F_CPU at 28 mHz EFM32G222F128 
    read speed:    mode4   2331khz  429us in avr emulate
                   mode1/3  607khz 1645us in cplus and  LL_PIN
                   mode2   2150khz  465us in use bitband
                   mode0    635khz 1573us in c mode
     write speed:  mode4   2702khz  370us in avr emulate
                   mode1/3 2710khz  369us in cplus and  LL_PIN
                   mode2   1162khz  860us in use bitband
                   mode0    362khz 2759us in c mode

  by  huawei <huaweiwx@sina.com> 2019.9.10
*/

#define GPIOMODE 0   /*please select mode 0/1/2/3 */

#if GPIOMODE == 4    /*avr emulate*/
#  define inp  (bitRead(PINA,0))
#  define ledddr  DDRD
#  define ledport PORTD
#elif GPIOMODE == 3
  GPIOPIN led(LED_BUILTIN); /*GPIOPIN is alias of LL_PIN class*/
  GPIOPIN inp(PA0);
#elif GPIOMODE == 2
  BB_PIN led(LED_BUILTIN);
  BB_PIN inp(PA0);
#elif GPIOMODE == 1                        /* cplus mode*/
  ARDUINOPIN_TypeDef led = LED_BUILTIN;  /* led is __ConstPin   type var */
  ARDUINOPIN_TypeDef inp = PA0;
#else                                      /*c mode */
  uint32_t led = LED_BUILTIN;
  uint32_t inp = PA0;
#endif

void setup() {
  // put your setup code here, to run once:

  /* setup alternate location default is 0# */
  Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 9600bps 8N1) */
  delay(2000);
#if  GPIOMODE == 4
  DDRD |= bit(6); //  pinMode(LED_BUILTIN,OUTPUT);
#elif   GPIOMODE >= 2
  led.mode(OUTPUT);
#else
  pinMode(led, OUTPUT);
#endif

  uint32_t timers = getTimers(1000, 0);
  Serial.println("\nRead:");
  Serial.print(1000000 / timers);
  Serial.print(" khz  Timer elapsed:");
  Serial.print(timers);
  Serial.println(" us\n");

  timers = getTimers(1000, 1);
  Serial.println("Write:");
  Serial.print(1000000 / timers);
  Serial.print(" khz  Timer elapsed:");
  Serial.print(timers);
  Serial.println(" us\n");
}

//Measuring toggle frequency with an oscilloscope:
void loop() {
#if  GPIOMODE == 4
  PORTD ^= BIT6;
#elif   GPIOMODE >= 2
  led.toggle();
#else
  digitalToggle(led);
#endif
  //  delay(500);
}

uint32_t getTimers(uint32_t count, uint8_t op) {
  uint32_t timeBegan, loopTimeElapsed, timeElapsed, i;
  i = 0;
  uint32_t tmp = 0;
  timeBegan = micros();
  while (i < count) {
    i++;
  }
  loopTimeElapsed = (micros() - timeBegan); // Time taken to do nothing but increment a variable
  i = 0;
  if (op) {  //write
    timeBegan = micros();
    while (i < count) {
#if  GPIOMODE == 4
      PORTD |= BIT6;
      PORTD &= ~BIT6;
#elif   GPIOMODE >= 2
      led.high();
      led.low();
#else
      digitalWrite(led, HIGH);
      digitalWrite(led, LOW);
#endif
      i++;
    }
    timeElapsed = (micros() - timeBegan - loopTimeElapsed); // Time taken to read a pin
  } else { //read
    timeBegan = micros();
    while (i < count) {
#if   GPIOMODE == 4
      tmp += inp;
#elif   GPIOMODE >= 2
      tmp += inp.read();
#else
      tmp += digitalRead(inp);
#endif
      i++;
    }
    timeElapsed = (micros() - timeBegan - loopTimeElapsed); // Time taken to read a pin
  }
  return timeElapsed;
}

