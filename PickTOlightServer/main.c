#include "main.h"
#include "can.h"
#include "clcd.h"
#include <string.h>
unsigned char clock_reg[3];
unsigned char time[9];
unsigned char send_arr[9] = {'\0'};
int i, flag, tx = 1;
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
	//unsigned char i = 0;
	//unsigned char local_can_payload[13];
	
	char ch;
	if(tx)
	{
		if(flag == 0)
		{
			if(i <= 3)
			{
				puts("\r");
				puts("Enter the Node ID: ");
				for (i = 0; i < 4; i++)
				{
					send_arr[i] = getch();
					putch(send_arr[i]);
				}
				puts("\n\r");
			}
			else
			{
				puts("Enter the Stock ID: ");
				for( ; i < 8; i++)
				{
					send_arr[i] = getch();
					putch(send_arr[i]);
				}
				puts("\n\r");
				i = 0;
				flag = 1;

			}
			//fill array
		}
		if(flag == 1)
		{
			//tx
			can_payload[EIDH] = 0x00;
			can_payload[EIDL] = 0x00;
			can_payload[SIDH] = 0x6B;
			can_payload[SIDL] = 0xC0;
			can_payload[DLC] = 0x08;
			can_payload[D0] = send_arr[0];
			can_payload[D1] = send_arr[1];
			can_payload[D2] = send_arr[2];
			can_payload[D3] = send_arr[3];
			can_payload[D4] = send_arr[4];
			can_payload[D5] = send_arr[5];
			can_payload[D6] = send_arr[6];
			can_payload[D7] = send_arr[7];
			//strncpy(str,&can_payload[D0],8);
			can_transmit(can_payload);
			clcd_print(send_arr, LINE2(0));
			flag = 0;
			tx = 0;
		}
	}
	else
	{
		if (can_receive())
		{
			//puts(can_payload);
			char time[9] = {'\0'};
			char nid[5] = {'\0'};
			char uid[5] = {'\0'};
			
			nid[0] = can_payload[D0];
			nid[1] = can_payload[D1];
			nid[2] = can_payload[D2];
			nid[3] = can_payload[D3];

			uid[0] = can_payload[D4];
			uid[1] = can_payload[D5];
			uid[2] = can_payload[D6];
			uid[3] = can_payload[D7];

			//clcd_print(time, LINE2(0));
			puts("\n\r");
			puts("n-id:");
			puts(nid);
			puts(" u-id:");
			puts(uid);
			puts("\n\r");
			//can_transmit(can_payload);
			tx = 1;

		}
	}
	
}

void main(void)
{    
	init_config();

	puts("welcome\n\r");
	while (1)
	{
		can_demo();	
	}
}
