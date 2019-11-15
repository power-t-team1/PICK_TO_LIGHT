#ifndef PIC_SPECIFIC_H
#define PIC_SPECIFIC_H

#include <xc.h>


#define _XTAL_FREQ 20000000

#define SSD_DATA_PORT		PORTD
#define SSD_CNT_PORT		PORTA

#pragma config OSC			= XT
#pragma config WDT			= OFF
#pragma config BOREN		= OFF
#pragma config PBADEN		= OFF
#pragma config LVP			= OFF

#define KEY_PORT			PORTC
#define LED8 RB7

#endif