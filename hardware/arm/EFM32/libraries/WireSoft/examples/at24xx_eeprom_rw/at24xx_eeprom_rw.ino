/*
    at24cxx_eeprom_rw.ino
    huawei huaweiwx@sina.com 2017.2.21
*/


#include "WireSoft.h"
#include "at24cxx.h"

#define EE_SDA     SDA
#define EE_SCL     SCL
#define EE_TYPE    AT24C02

#define   EE_DISK0 0x50    //Address of AT24LC512 A2A1A0=000

EXTEEPROM  mywire(EE_SDA, EE_SCL);

void setup() {
/* setup alternate location default is 0# */  
  Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 9600bps 8N1) */
  delay(2000);
  
  Serial << "\nAT24CXX RW";
  mywire.begin(EE_DISK0, EE_TYPE); //
  //write all eeprom with page number; run one times only
  //  for (uint16_t i = 0; i < 256; i++) {
  //    for (uint16_t j = 0; j < 256; j++) {
  //       if ((i * 256 + j) <=  EE_TYPE)
  //          mywire.write(i * 256 + j, j);
  //      else return;
  //    }
  //  }

}

void loop() {
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial.print(mywire.read( i * 16 + j), HEX); Serial.print("  ");
    }
    Serial.println();
  }

  Serial.print("disk @000 ok\n");
  delay(5000);           // wait 5 seconds for next scan
}

