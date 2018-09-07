// OLED_I2C_TinyFont_View
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my OLED_I2C library.
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// Display:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//           SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the
// hardware I2C interfaces.
//
// You can connect the OLED display to any available pin but if you use
// any other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

// add support ssd1306_12832 by huaweiwx@sina.com 2016.11.08
// class OLED_12832 128x32    OLED_12864 128x64
// OLED_128xx  myOLED(SDA, SCL);      //default unuse RST
// OLED_128xx  myOLED(SDA, SCL, RST); //use rst
//

/* OLED12864/32  检查你的连接接线，否则修改之
OLED:   CS  RST  DC  D1(SDA)  D0(SCL)   VCC     GND
STM32:  -   PA3  -    PA1      PA2      3.3/5V  0V
EFM32:  -   -    -    PA9      PA10     3.3/5V  0V
ZION    -   23        49       50       5V      0V   
*/

#include <OLED_I2C.h>
/* Selected oneof following for your OLED and modify it*/

//OLED_12832  myOLED(PG_1,PG_2,  PA_7);   //use soft i2c  12832 avr zion
//OLED_12864  myOLED(PG_1,PG_2,  PA_7);   //use soft i2c  12864 avr zion

// SDA:PC5 SCL:PC4 RST:PC1  my GD32 conected
//OLED_12832  myOLED(PC5,PC4,PC1);    //use soft i2c  12832 gd32
//OLED_12864 myOLED(PA1,PA2,PA3);     //use soft i2c  12864 gd32
//OLED_12832  myOLED(PC5,PC4);        //use soft i2c  12832 gd32 unuse reset
//OLED_12864  myOLED(PC5,PC4);        //use soft i2c  12864 gd32 unuse reset

//OLED_12832  myOLED(PA9,PA9);        //use soft i2c  12832 EFM32 unuse reset
OLED_12864  myOLED(PA9,PA10);         //use soft i2c  12864 EFM32 unuse reset

extern uint8_t logo[];
extern uint8_t The_End[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];
extern uint8_t pill[];

float y;
uint8_t* bm;
int pacy;

void setup()
{
  myOLED.begin();
  myOLED.setFont(SmallFont);  /* TinyFont / SmallFont /MediumNumbers / BigNumbers */
  randomSeed(analogRead(7));
}

void loop()
{
  myOLED.clrScr();
  myOLED.drawBitmap(0, 16, logo, 128, 36);
  myOLED.update();

  delay(3000);
  
  myOLED.clrScr();
  myOLED.printxy("OLED_I2C", CENTER, 0);
  myOLED.printxy("DEMO", CENTER, 28);
  myOLED.drawRect(50, 26, 78, 36);
  for (int i=0; i<6; i++)
  {
    myOLED.drawLine(79, 26+(i*2), 105-(i*3), 26+(i*2));
    myOLED.drawLine(22+(i*3), 36-(i*2), 50, 36-(i*2));
  }
  myOLED.printxy("(C)2015 by", CENTER, 48);
  myOLED.printxy("Henning Karlsen", CENTER, 56);
  myOLED.update();

  delay(5000);
  
  myOLED.clrScr();
  for (int i=0; i<64; i+=2)
  {
    myOLED.drawLine(0, i, 127, 63-i);
    myOLED.update();
  }
  for (int i=127; i>=0; i-=2)
  {
    myOLED.drawLine(i, 0, 127-i, 63);
    myOLED.update();
  }

  delay(2000);
  
  myOLED.clrScr();
  myOLED.drawRect(0, 0, 127, 63);
  for (int i=0; i<64; i+=4)
  {
    myOLED.drawLine(0, i, i*2, 63);
    myOLED.update();
  }
  for (int i=0; i<64; i+=4)
  {
    myOLED.drawLine(127, 63-i, 127-(i*2), 0);
    myOLED.update();
  }

  delay(2000);
  
  myOLED.clrScr();
  for (int i=0; i<10; i++)
  {
    myOLED.drawRoundRect(i*3, i*3, 127-(i*3), 63-(i*3));
    myOLED.update();
  }

  delay(2000);
  
  myOLED.clrScr();
  for (int i=0; i<25; i++)
  {
    myOLED.drawCircle(64, 32, i*3);
    myOLED.update();
  }

  delay(2000);
  
  myOLED.clrScr();
  myOLED.drawRect(0, 0, 127, 63);
  myOLED.drawLine(0, 31, 127, 31);
  myOLED.drawLine(63, 0, 63, 63);
  for (int c=0; c<4; c++)
  {
    for (int i=0; i<128; i++)
    {
      y=i*0.04974188368183839294232518690191;
      myOLED.invPixel(i, (sin(y)*28)+31);
      myOLED.update();
      delay(10);
    }
  }

  delay(2000);

  for (int pc=0; pc<3; pc++)
  {
    pacy=random(0, 44);
  
    for (int i=-20; i<132; i++)
    {
      myOLED.clrScr();
      for (int p=6; p>((i+20)/20); p--)
        myOLED.drawBitmap(p*20-8, pacy+7, pill, 5, 5);
      switch(((i+20)/3) % 4)
      {
        case 0: bm=pacman1;
                break;
        case 1: bm=pacman2;
                break;
        case 2: bm=pacman3;
                break;
        case 3: bm=pacman2;
                break;
      }
      myOLED.drawBitmap(i, pacy, bm, 20, 20);
      myOLED.update();
      delay(10);
    }
  }

  for (int i=0; i<41; i++)
  {
    myOLED.clrScr();
    myOLED.drawBitmap(22, i-24, The_End, 84, 24);
    myOLED.update();
    delay(50);
  }
  myOLED.printxy("Runtime (ms):", CENTER, 48);
  myOLED.printNumI(millis(), CENTER, 56);
  myOLED.update();
  for (int i=0; i<5; i++)
  {
    myOLED.invert(true);
    delay(1000);
    myOLED.invert(false);
    delay(1000);
  }
}


