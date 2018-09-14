/*
   AVR emulate DDRx PORTx and PINx demo
   test pin is PD6
   by huaweiwx <huaweiwx@sina.com> 2018.09.08
*/

void setup() {
  DDRD |= bit(6); //  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  PORTD |= bit(6);  /* PD6 set   */
  delay(500);
  PORTD &= ~bit(6); /* PD6 clear */
  delay(500);
}

