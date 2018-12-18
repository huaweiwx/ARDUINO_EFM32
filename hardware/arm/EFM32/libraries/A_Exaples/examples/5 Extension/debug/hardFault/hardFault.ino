/*
  hardFaultl.ino: Capture and print hardware failure information(捕捉并打印硬件失败信息)

  use interrupt HardFault_Handler/MemManage_Handler/BusFault_Handler/UsageFault_Handler
  application api: 
     _Error_Handler(char* , uint32_t); 
     assert_param(int condition);
  hook: 
     errorCallback(char* file, uint32_t n);
  debug:
    debug(const char *format, ...);
    debug_if(int condition, const char *format, ...);
  log:
     PRINT_FATAL(...)
     PRINT_ERROR(...)
     PRINT_WARNING(...)
     PRINT_INFO(...)
     PRINT_DEBUG(...)
     PRINT_TRACE(...)
*/

// the setup function runs once when you press reset or power the board
static int val = 0;
void setup() {
/* setup alternate location default is 0# */  
  Serial.setRouteLoc(1); /*set to 1#. the serial port's Alternate LOCATION(see datasheet)*/
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 115200bps 8N1) */

  while (!Serial) {};    /*if used usb serial,wait for it ready*/
  
  delay(1000); /*wait for serial ready*/

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial <<"hardfault demo\r\n";  
}
extern "C" void _Error_Handler(char* file, uint32_t line);
void test (int n) {
//  assert_param( n < 20);
  void (*func)(void) = (void (*)(void))0x00000000;

  if ((n % 10) == 0) {
    PRINT_TRACE("val= %d\n", n);
  } else if ((n % 2) == 0) {
    PRINT_DEBUG("val= %d\n", n);
  } else {
    PRINT_INFO("val= %d\n", n);
  }
  if (n >20) {
    PRINT_INFO("\nval= %d must <= 30 \n", n);
//    func();         /*hardfault code demo 1*/
    MEM_ADDR(0) = 0;  /*hardfault code demo 2*/
    _Error_Handler(__FILENAME__, __LINE__);
   }
}

// the loop function runs over and over again forever
void loop() {
  val++;
  debug_if(val < 4, "val = %d\n", val);
  test(val);
  digitalToggle(LED_BUILTIN);
  delay(1000);
}

#ifdef USE_FULL_ASSERT     /*use user errorCallBack show info */
extern "C" void errorCallback(char* file, uint32_t n) {
  Serial <<"Err at file: "<< file << " Line:" << n << "\r\n";
  while (1);
}
#endif
