/*
   Hello World! arduino Serial.println it on USART0/1/LEUART
   demo by huawei<huaweiwx@sina.com> 2016.9.18
 */

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);

/* setup alternate location default is 0# */  
  Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 9600bps 8N1) */
  
}

void loop() {
  digitalToggle(LED_BUILTIN);
  Serial.println(PORTD,HEX);
  delay(1000);
}
