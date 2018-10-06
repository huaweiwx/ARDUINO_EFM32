/*
 Led_flash.ino
   This example shows how to flash an LED

 This example code is in the public domain.
 */

#include <LED.h>

void setup() {
}

void loop() {

//  Led.flash(10, 240,4); /*LED: on 10ms, off 240ms, repeat 4 times */
  Led.flash(100,990); /*LED: on 100ms, off 240ms, repeat 1 times is default*/

}
