/*
  show_f_cpu.ino
  This example code is in the public domain.
  huaweiwx@sina.com 2018.8
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT); 

/* setup alternate location default is 0*/  
//  Serial.setRouteLoc(1); /*set to 1. the serial port's Alternate LOCATION see datasheet*/
  Serial.begin(9600); /*for LEUART baudrate is 9600 only */
}

// the loop function runs over and over again forever
void loop() {
  digitalToggle(LED_BUILTIN);   // turn the LED on (HIGH is the voltage level)
  Serial.print("The Serial write buf length:");
  Serial.print(SERIAL_TX_BUFFER_SIZE);
  uint8_t count = Serial.availableForWrite();
  Serial.print(" free:");
  Serial.println(count);
  delay(2000);                  // wait for a second
}
