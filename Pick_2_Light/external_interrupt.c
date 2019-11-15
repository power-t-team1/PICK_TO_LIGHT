#include "main.h"
#include "external_interrupt.h"

void init_external_interrupt(void)
{
	INTEDG0 = 1;
	INT0F = 0;
	INT0E = 1;
}
