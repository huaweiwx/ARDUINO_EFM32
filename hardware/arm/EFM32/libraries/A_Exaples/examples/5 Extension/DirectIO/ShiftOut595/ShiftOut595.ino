
ClockedOutput<> sout595(PF2, PF3);
OutputPin  storageCLK(PF4);
//OutputPin outputEnable(PF5);

void write595(uint8_t val) {
  sout595.write(val);
  storageCLK.pulse();
}
void setup() {
  //outputEnable = HIGH;
}

void loop() {
  static uint8_t i = 0;
  write595(i);
  i++;
  delay(100);
}
