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

double vectors[8][3] = {{20, 20, 20},{-20, 20, 20},{-20, -20, 20},{20, -20, 20},{20, 20, -20},{-20, 20, -20},{-20, -20, -20},{20, -20, -20}};

double perspective = 100.0f;
int deltaX, deltaY, deltaZ, iter = 0;
long stime, fps = 0, frames = 0;

void setup()
{
  randomSeed(analogRead(0));

  myOLED.begin();
  myOLED.setFont(SmallFont);  /* TinyFont / SmallFont /MediumNumbers / BigNumbers */
  stime = micros();
}

void loop()
{
  myOLED.clrScr();
  drawVectors();
  if (iter == 0)
  {
    deltaX = random(7) - 3;
    deltaY = random(7) - 3;
    deltaZ = random(7) - 3;
    iter   = random(250) + 5;
  }
  rotateX(deltaX);
  rotateY(deltaY);
  rotateZ(deltaZ);
  iter--;
  fps += 1000000 / (micros() - stime);
  stime = micros();
  frames++;
  myOLED.printNumI(fps / frames, 0, 0, 3);  // Print average FPS on screen
  myOLED.update();
}

int translateX(double x, double z)
{
  return (int)((x + 64) + (z * (x / perspective)));
}

int translateY(double y, double z)
{
  return (int)((y + 32) + (z * (y / perspective)));
}

void rotateX(int angle)
{
  double rad, cosa, sina, Yn, Zn;
 
  rad = angle * PI / 180;
  cosa = cos(rad);
  sina = sin(rad);
  for (int i = 0; i < 8; i++)
  {
    Yn = (vectors[i][1] * cosa) - (vectors[i][2] * sina);
    Zn = (vectors[i][1] * sina) + (vectors[i][2] * cosa);
    vectors[i][1] = Yn;
    vectors[i][2] = Zn;
  }
}

void rotateY(int angle)
{
  double rad, cosa, sina, Xn, Zn;
 
  rad = angle * PI / 180;
  cosa = cos(rad);
  sina = sin(rad);
  for (int i = 0; i < 8; i++)
  {
    Xn = (vectors[i][0] * cosa) - (vectors[i][2] * sina);
    Zn = (vectors[i][0] * sina) + (vectors[i][2] * cosa);
    vectors[i][0] = Xn;
    vectors[i][2] = Zn;
  }
}

void rotateZ(int angle)
{
  double rad, cosa, sina, Xn, Yn;
 
  rad = angle * PI / 180;
  cosa = cos(rad);
  sina = sin(rad);
  for (int i = 0; i < 8; i++)
  {
    Xn = (vectors[i][0] * cosa) - (vectors[i][1] * sina);
    Yn = (vectors[i][0] * sina) + (vectors[i][1] * cosa);
    vectors[i][0] = Xn;
    vectors[i][1] = Yn;
  }
}

void drawVectors()
{
  myOLED.drawLine(translateX(vectors[0][0], vectors[0][2]), translateY(vectors[0][1], vectors[0][2]), translateX(vectors[1][0], vectors[1][2]), translateY(vectors[1][1], vectors[1][2]));
  myOLED.drawLine(translateX(vectors[1][0], vectors[1][2]), translateY(vectors[1][1], vectors[1][2]), translateX(vectors[2][0], vectors[2][2]), translateY(vectors[2][1], vectors[2][2]));
  myOLED.drawLine(translateX(vectors[2][0], vectors[2][2]), translateY(vectors[2][1], vectors[2][2]), translateX(vectors[3][0], vectors[3][2]), translateY(vectors[3][1], vectors[3][2]));
  myOLED.drawLine(translateX(vectors[3][0], vectors[3][2]), translateY(vectors[3][1], vectors[3][2]), translateX(vectors[0][0], vectors[0][2]), translateY(vectors[0][1], vectors[0][2]));
  myOLED.drawLine(translateX(vectors[4][0], vectors[4][2]), translateY(vectors[4][1], vectors[4][2]), translateX(vectors[5][0], vectors[5][2]), translateY(vectors[5][1], vectors[5][2]));
  myOLED.drawLine(translateX(vectors[5][0], vectors[5][2]), translateY(vectors[5][1], vectors[5][2]), translateX(vectors[6][0], vectors[6][2]), translateY(vectors[6][1], vectors[6][2]));
  myOLED.drawLine(translateX(vectors[6][0], vectors[6][2]), translateY(vectors[6][1], vectors[6][2]), translateX(vectors[7][0], vectors[7][2]), translateY(vectors[7][1], vectors[7][2]));
  myOLED.drawLine(translateX(vectors[7][0], vectors[7][2]), translateY(vectors[7][1], vectors[7][2]), translateX(vectors[4][0], vectors[4][2]), translateY(vectors[4][1], vectors[4][2]));
  myOLED.drawLine(translateX(vectors[0][0], vectors[0][2]), translateY(vectors[0][1], vectors[0][2]), translateX(vectors[4][0], vectors[4][2]), translateY(vectors[4][1], vectors[4][2]));
  myOLED.drawLine(translateX(vectors[1][0], vectors[1][2]), translateY(vectors[1][1], vectors[1][2]), translateX(vectors[5][0], vectors[5][2]), translateY(vectors[5][1], vectors[5][2]));
  myOLED.drawLine(translateX(vectors[2][0], vectors[2][2]), translateY(vectors[2][1], vectors[2][2]), translateX(vectors[6][0], vectors[6][2]), translateY(vectors[6][1], vectors[6][2]));
  myOLED.drawLine(translateX(vectors[3][0], vectors[3][2]), translateY(vectors[3][1], vectors[3][2]), translateX(vectors[7][0], vectors[7][2]), translateY(vectors[7][1], vectors[7][2]));
}
