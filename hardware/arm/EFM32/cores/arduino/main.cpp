#include "arduino.h"

extern "C" void init(void);
extern void setup(void);
extern void  loop(void);

int main()
{
	init();
	setup();
    while(1)
    {
		loop();
    }
//	return 1; //
}