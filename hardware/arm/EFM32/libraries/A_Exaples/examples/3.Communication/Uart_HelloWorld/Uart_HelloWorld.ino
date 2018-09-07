/*
   Hello World! arduino Serial.println it on USART0/1/LEUART
   demo by huawei<huaweiwx@sina.com> 2016.9.18
 */

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);
  
}

void loop() {
  digitalToggle(LED_BUILTIN);
  Serial.println("Hello World!");
  delay(1000);
}
