#include "main.h"
#include "can.h"
#include "clcd.h"

unsigned char clock_reg[3];
unsigned char time[9];
/*
void create_payload(unsigned char can_payload[])
{
	can_payload[EIDH] = 0x00;
	can_payload[EIDL] = 0x00;
	can_payload[SIDH] = 0x6B;
	can_payload[SIDL] = 0xC0;
	can_payload[DLC] = 0x03;
	can_payload[D0] = clock_reg[0];
	can_payload[D1] = clock_reg[1];
	can_payload[D2] = clock_reg[2];
	can_payload[D3] = '\0';
	can_payload[D4] = '\0';
	can_payload[D5] = '\0';
	can_payload[D6] = '\0';
	can_payload[D7] = '\0';
}*/
/*
static void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);
}
*/
/* delay 1ms function */
void delay(unsigned short factor)
{
	unsigned short i, j;

	for (i = 0; i < factor; i++)
	{
		for (j = 500; j--; );
	}
}

void init_config(void)
{
	/* Initialize Matrix Keypad */
//	init_matrix_keypad();

	/* Initialize CLCD module */
	init_clcd();

	/* Initialize CAN module */
	init_can();
	init_uart();
//	init_i2c();
//	init_ds1307();

	/* Set buzzer as output */
	TRISE0 = 0;
	BUZZER = 0;

	clcd_print("CAN Bus Demo", LINE1(2));
}


void can_demo(void)
{
//	unsigned char key;
	unsigned char i = 0;
	unsigned char local_can_payload[13];

//	key = read_switches(1);
/*
	if (key == MK_SW1)
	{
		get_time();
		create_payload(local_can_payload);
		can_transmit(local_can_payload);
		clcd_print("Tx DATA : -->   ", LINE2(0));
		delay(1000);
		CLEAR_DISP_SCREEN;
	}
*/
	if (can_receive())
	{
		//puts(can_payload);
		char time[9] = {'\0'};
		time[0] = can_payload[D0];
		time[1] = can_payload[D1];
		time[2] = can_payload[D2];
		time[3] = can_payload[D3];
		time[4] = can_payload[D4];
		time[5] = can_payload[D5];
		time[6] = can_payload[D6];
		time[7] = can_payload[D7];
		clcd_print(time, LINE2(0));
	}
}

void main(void)
{    
	init_config();

	while (1)
	{
		can_demo();	
	}
}
