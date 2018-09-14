/**
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	lcd.begin();
	lcd.backlight();
  
/* setup alternate location default is 0# */  
  Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 9600bps 8N1) */
}

void loop()
{
	// If characters arrived over the serial port...
	if (Serial.available()) {
		// Wait a bit for the entire message to arrive
		delay(100);
		// Clear the screen
		lcd.clear();

		// Write all characters received with the serial port to the LCD.
		while (Serial.available() > 0) {
			lcd.write(Serial.read());
		}
	}
}
