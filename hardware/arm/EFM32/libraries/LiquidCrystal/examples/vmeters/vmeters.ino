/*
  LiquidCrystal Library - vmeter4

  This sketch prints ADC to the LCD

  The circuit:
   LCD RS pin to digital pin PD5
   LCD Enable pin to digital pin PD7
   LCD D4 pin to digital pin PB4
   LCD D5 pin to digital pin PB5
   LCD D6 pin to digital pin PB6
   LCD D7 pin to digital pin PB7
   LCD R/W pin to PD6
   LCD VSS pin to ground
   LCD VCC pin to 5V
   LCD A   BackLight on  by pin PD3 HIGH
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

   7/28/2018 by huaweiwx@sina.com
*/

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
#define rs 	PF3
#define rw 	PF2
#define en 	PF1
#define d0 	PF0
#define d1 	PC8
#define d2 	PC9
#define d3 	PC10
#define d4 	PC11
#define d5 	PC13
#define d6 	PC14
#define d7 	PC15

GPIOPIN lcd_bkPin(PF4);
//#define ADC_RENFERENCE_INTERNAL  /*use1.1v/2.56v internal renference*/

typedef struct {
  uint8_t c;
  uint8_t l;
} pos_t;

#define CHS 4
uint8_t AIN[CHS] = {PD4, PD5, PD6 ,PD7};  /*ADC4/5/6/7*/
uint16_t Ax_MIN[CHS] = {0u, 0u, 0u, 0u};

#ifdef ADC_RENFERENCE_INTERNAL
#if defined(INTERNAL1V1)
uint16_t Ax_MAX[CHS] = {11000u, 11000u, 11000u, 11000u};  /*1.10v*/
#elif defined(INTERNAL2V56)
uint16_t Ax_MAX[CHS] = {2560u, 2560u, 2560u, 2560u};  /*2.56v*/
#endif
#else
uint16_t Ax_MAX[CHS] = {5000u, 5000u, 5000u, 5000u};  /*5.00v*/
#endif

pos_t pos[CHS] = {
  {0, 0},
  {8, 0},
  {0, 1},
  {8, 1},
};

//LiquidCrystal lcd(rs,en, d4, d5, d6, d7);  //4 bit mode,unused rwPin
LiquidCrystal lcd(rs,rw,en, d4, d5, d6, d7);  //4 bit mode
//LiquidCrystal lcd(rs, rw, en, d0, d1, d2, d3, d4, d5, d6, d7); //8 bit mode, unused rwPin
//LiquidCrystal<const int> lcd(rs, rw, en, d0, d1, d2, d3, d4, d5, d6, d7); //8 bit mode

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd_bkPin.mode(OUTPUT);
  lcd_bkPin = HIGH; /*BK ON*/

  // Print a message to the LCD.
  // lcd.setCursor(2, 0);
  lcd.print("Vmeter 4CHs demo");
  lcd.setCursor(1, 1);
  lcd.print("Renference:");

#ifdef ADC_RENFERENCE_INTERNAL
#if defined(INTERNAL1V1)
  lcd.print("1.10V");
#elif defined(INTERNAL2V56)
  lcd.print("2.56V");
#endif
#else
  lcd.print(" VDD");
#endif

  delay(2000);
  lcd.clear();

#ifdef ADC_RENFERENCE_INTERNAL
# ifdef INTERNAL1V1
  analogReference(INTERNAL);
# else
  analogReference(INTERNAL);   /*use default 3(INTERNAL2V56)*/
# endif
#endif
}

void loop() {
  uint16_t V[CHS];

  for (int8_t j = 0; j < CHS; j++) {
    V[j] = analogRead(AIN[j]);

    V[j] = 0;
    for (uint8_t i = 0; i < 64; i++) {
      V[j]  += analogRead(AIN[j]);
    }

    V[j] = map( V[j], Ax_MIN[j], (uint32_t)1023 * 64, 0, Ax_MAX[j]);

    lcd.setCursor(pos[j].c, pos[j].l);
    lcd.print(j); lcd.print(": ");
    if (V[j] > (Ax_MAX[j] - 3)) lcd.print(" OVL");
    else {
      if (V[j] < 1000) lcd.print(" ");
      if (V[j] < 100) lcd.print(" ");
      if (V[j] < 10) lcd.print(" ");
      lcd.print(V[j]);
    }
  }

  delay(500);
}
