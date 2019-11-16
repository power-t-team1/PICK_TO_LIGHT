#include "pic_specific.h"
#include "uart.h"

void init_uart(void)
{
	/* Serial initialization */
	RX_PIN = 1;
	TX_PIN = 0;

	/* TXSTA:- Transmitor Status and control Register */
	
	/* Clock selection control bit */	
	CSRC = 0;
	/* 9bit TX enable or disable bit */ 
	TX9 = 0;
	/* UART Tarsmition enable bit */
	TXEN = 1;
	/* Synchronous or Asynchronous mode selection */
	/* Asynchronous */
	SYNC = 0;
	/* Send the Break character bit */
	SENDB = 0;
	/* Low or High baud rate selection bit */
	/* High Baud Rate */
	BRGH = 1;
	/* Trasmiter Shift register status bit */ 
	TRMT = 0;
	/* 9th bit trasmite data */
	TX9D = 0;

	/* RCSTA :- Recepition Status and control Register */
	
	/* TX/RC7 and RX/RC6 act as serial port */ 
	SPEN = 1;
	/* 9bit RX enable or disable bit */
	RX9 = 0;
	/* Single reception enable or disable */
	SREN = 0;
	/* Continous reception enable or disable */ 
	CREN = 1;
	/* Adress detection enable bit */	
	ADDEN = 0;
	/* Frame error bit */
	FERR = 0;
	/* Overrun error bit */ 
	OERR = 0;
	/* 9th bit received bit */
	RX9D = 0;

	/* BAUDCTL:- Baud rate control register */

	/* Auto baud detection overflow bit */
	ABDOVF = 0;
	/* Receive idle flag bit */
	RCIDL = 1;
	/* Synchronous clock polarity selecton bit */ 
	SCKP = 0;
	/* 16bit baud generate bit */ 
	BRG16 = 0;
	/* Wakeup enable bit */
	WUE = 0;
	/* Auto baud detect enable bit */
	ABDEN = 0;

	/* Baud Rate Setting Register */
	/* Set to 10 for 115200, 64 for 19200 and 129 for 9600 */
	SPBRG = 10;

	/* TX interrupt enable bit */
	TXIE = 1;
	/* TX interrupt flag bit */
	TXIF = 0;
	/* RX interrupt enable bit */
	RCIE = 1;
	/* RX interrupt enable bit */
	RCIF = 0;
}

void putch(unsigned char byte) 
{
	/* Output one byte */
	/* Set when register is empty */
	while(!TXIF)
	{
		continue;
	}
	TXREG = byte;
}

int puts(const char *s)
{
	while(*s)		
	{
		putch(*s++);	
	}

	return 0;
}

unsigned char getch(void)
{
	/* Retrieve one byte */
	/* Set when register is not empty */
	while(!RCIF)
	{
		continue;
	}

	return RCREG;
}

unsigned char getche(void)
{
	unsigned char c;

	putch(c = getch());

	return (c);
}
