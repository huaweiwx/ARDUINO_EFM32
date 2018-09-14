/*
  adcDiffRead.ino  efm32adc differential read demo
  This example code is in the public domain.
  huaweiwx@sina.com 2018.8
*/

// the setup function runs once when you press reset or power the board
ADC adc;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

/* setup alternate location default is 0# */  
  Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
  Serial.begin(115200);

  adc.reference(INTERNAL2V5); /* setup ADC reference INTERNAL1V25/INTERNAL2V5/INTERNAL3V3*/
}

// the loop function runs over and over again forever
void loop() {
  digitalToggle(LED_BUILTIN);   // turn the LED on (HIGH is the voltage level)
#if defined(A4 )&& defined(A5)  /* adc channel see datasheet */
  Serial.print("ADC differential ch4 ch5 read:");
  Serial.println(adc.read(A4, A5));
#else
  Serial.print("ADC differential ch6 ch7 read:");
  Serial.println(adc.read(A6, A7));
#endif  
  delay(2000);  // wait for 2 seconds
}
