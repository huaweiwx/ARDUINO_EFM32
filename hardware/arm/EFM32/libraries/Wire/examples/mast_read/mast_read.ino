// Wire Master Reader 
2 // by Nicholas Zambetti <http://www.zambetti.com> 
3 
 
4 // Demonstrates use of the Wire library 
5 // Reads data from an I2C/TWI slave device 
6 // Refer to the "Wire Slave Sender" example for use with this 
7 
 
8 // Created 29 March 2006 
9 
 
10 // This example code is in the public domain. 
11 
 
12 
 
13 #include <Wire.h> 
14 
 
15 void setup() 
16 { 
17   Wire.begin();        // join i2c bus (address optional for master) 
18   Serial.begin(115200);  // start serial for output 
19 } 
20 
 
21 void loop() 
22 { 
23   Wire.requestFrom(2, 6);    // request 6 bytes from slave device #2 
24 
 
25   while(Wire.available())    // slave may send less than requested 
26   {  
27     char c = Wire.read(); // receive a byte as character 
28     Serial.print(c);         // print the character 
29   } 
30 
 
31   delay(500); 
32 } 
