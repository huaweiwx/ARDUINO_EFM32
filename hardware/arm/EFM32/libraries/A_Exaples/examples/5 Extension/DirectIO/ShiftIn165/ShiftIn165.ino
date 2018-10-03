/*
  74165  series input demo
  huaweiwx@sina.com 2018.9.28
*/


#define OUT_PIN   PF2
#define CLK_PIN   PF3
#define nPL_PIN   PF4
//#define nCE_PIN   PF5   //connet to GND

ClockedInput<>  sinp165(OUT_PIN, CLK_PIN);
OutputPin       readCLK(nPL_PIN);

#ifdef OE_PIN
OutputPin outputEnable(nOE_PIN);
#endif

uint8_t read165(void) {
  readCLK.pulse();    //getdate
  uint8_t val = sinp165; //shiftin
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);

/* setup alternate location default is 0# */  
  Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 9600bps 8N1) */
  
#ifdef OE_PIN
  outputEnable = LOW;
#endif
}

void loop() {
  Serial.println(read165(),HEX);
  
  digitalToggle(LED_BUILTIN);
  delay(1000);
}
