/*
  clockOut.ino  shiftin/shiftout examples
  example:
    ClockedInput<bits,bit_order>  sinp(datapin,clockpin,pullup)	  
    ClockedOutput<bits,bit_order> sout(datapin,clockpin);
      bits: 0~32,default is 8
      bit_order: LSBFIRST/MSBFIRST default is MSBFIRST
      pullup:false/true default is true
	function:
      read()
      write(val)
      operate ()
      operate =	  
*/
//#define TEST_INPUT

#ifdef TEST_INPUT
ClockedInput<>  sinp(PA0,PA2);
#else
ClockedOutput<> sout(PA0,PA1);
#endif

void setup() {
   pinMode(LED_BUILTIN,OUTPUT);

#ifdef TEST_INPUT
/* setup alternate location default is 0# */  
   Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
   Serial.begin(115200);
#endif
}

void loop() {
#ifdef TEST_INPUT
  uint8_t indate = sinp;
  Serial.print("input is: ");
  Serial.println(indate,HEX);
#endif
  delay(1000);
  digitalToggle(LED_BUILTIN);
}

