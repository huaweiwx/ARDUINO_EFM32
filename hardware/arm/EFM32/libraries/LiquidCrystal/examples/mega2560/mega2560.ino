/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 40
   LCD Enable pin to digital pin 41
   LCD D4 pin to digital pin 34
   LCD D5 pin to digital pin 35
   LCD D6 pin to digital pin 36
   LCD D7 pin to digital pin 37
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   LCD A   BackLight on  by pin 39 HIGH
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = PG_1, 	// 40
          en = PG_0, 	// 41
          d4 = PC_3, 	// 34
          d5 = PC_2, 	// 35
          d6 = PC_1, 	// 36
          d7 = PC_0, 	// 37
          lcd_bk = PG_2; // 39
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  pinMode(lcd_bk, OUTPUT);
  digitalWrite(lcd_bk, HIGH); /*BK ON*/

  // Print a message to the LCD.
  // lcd.setCursor(2, 0);
  lcd.print(" HELLO, WORLD!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(7, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
