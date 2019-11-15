#include "main.h"
#include "isr.h"

 bit key_detected;
extern unsigned int flag;

void interrupt isr(void)
{
	if (INT0F == 1)
	{
		key_detected = 1;
		flag = !flag;
		INT0F = 0;
	}
}
