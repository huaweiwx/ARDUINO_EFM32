/*
  digital read  pin PA0 and print it on uart1
  demo by huaweiwx<huaweiwx@sina.com> 2016.9.18
 */

void setup() {
	Serial1.begin(115200);
	pinMode(LED_BUILTIN,OUTPUT);
	
	pinMode(PA0,INPUT);
}

void loop() {
	int sensorValue = digitalRead(PA0);
	Serial1.println(sensorValue, DEC);
	
	digitalToggle(LED_BUILTIN);
	delay(1000);
}
