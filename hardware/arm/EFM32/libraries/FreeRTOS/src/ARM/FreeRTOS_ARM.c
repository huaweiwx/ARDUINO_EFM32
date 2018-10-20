
#include <Arduino.h>
#include "FreeRTOS_ARM.h"

//------------------------------------------------------------------------------
/** vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. 
*/

void  __attribute__((weak)) vApplicationIdleHook( void ) {
  void loop();
  loop();
}
/** assertBlink
 * Blink one short pulse every two seconds if configASSERT fails.
*/
extern void errorLedBlink(int n);

//void assertBlink() {
//  errorLedBlink(1);
//}

void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.*/
    //taskDISABLE_INTERRUPTS();
#if USE_ERRORBLINK
	errorLedBlink(22);
#else
	for(;;);
#endif
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    //taskDISABLE_INTERRUPTS();
#if USE_ERRORBLINK
	errorLedBlink(23);
#else
	for(;;);
#endif
}


#if (portINFO >0)

#if (portTickUSE_TIMx == 0)
#pragma message "SysTick Timer used for scheduler."
#elif (portTickUSE_TIMx == 6)	
#pragma message "TIM6 used for scheduler."
#elif (portTickUSE_TIMx == 7)	
#pragma message "TIM7 used for scheduler."
#elif (portTickUSE_TIMx == 11)	
#pragma message "TIM11 used for scheduler."
#elif (portTickUSE_TIMx == 17)	
#pragma message "TIM17 used for scheduler."
#endif

#if portUSE_HEAP == 1
#pragma message "port heap use heap_1.c"
#elif portUSE_HEAP == 2
#pragma message "port heap use heap_2.c"
#elif portUSE_HEAP == 3
#pragma message "port heap use heap_3.c"
#elif portUSE_HEAP == 4
#pragma message "port heap use heap_4.c"
#elif portUSE_HEAP == 5
#pragma message "port heap use heap_5.c"
#endif

#if configUSE_COUNTING_SEMAPHORES > 0
#pragma message "use counting semaphores"
#endif

#if configUSE_IDLE_HOOK > 0
#pragma message "use idle hook"
#endif

#if  configUSE_TICK_HOOK >0
#pragma message "use tick hook"
#endif

#if  INCLUDE_vTaskDelayUntil >0
#pragma message "include INCLUDE_vTaskDelayUntil"
#endif

#endif
