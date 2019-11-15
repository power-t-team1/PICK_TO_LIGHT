#include "main.h"
#include "digital_keypad.h"
#include "ssd_display.h"
#include "external_interrupt.h"
#include "isr.h"
#include "can.h"
#include "pic_specific.h"

extern bit key_detected;
char mask = 0x10;
 unsigned int flag = 0;
// extern unsigned char can_payload[13];

unsigned char local_can_payload[13];

void create_payload(unsigned char can_payload[])
{
	can_payload[EIDH] = 0x00;
	can_payload[EIDL] = 0x00;
	can_payload[SIDH] = 0x6B;
	can_payload[SIDL] = 0xC0;
	can_payload[DLC] = 0x08;
	can_payload[D0] = 0x31;//clock_reg[0];
	can_payload[D1] = 0x32;//clock_reg[1];
	can_payload[D2] = 0x33;//clock_reg[2];
	can_payload[D3] = '\0';
	can_payload[D4] = '\0';
	can_payload[D5] = '\0';
	can_payload[D6] = '\0';
	can_payload[D7] = '\0';
}

static void init_config(void)
{
	//configure PORTB as output port
	//TRISB7 = 0;
	//config PORTB as digital port
	ADCON1 =0x0E;
	//configure LATB with 0x55
	LATB = 0x55;
	//TRISB0 = 1;

	GIE = 1;
	//Initially turn off all LEDs
	PORTB = 0x00;
	init_external_interrupt();

	init_digital_keypad();
	init_can();
}

static unsigned char ssd[] = {0xA4, 0xE5, 0x08, 0x80, 0xE9};

void init_config_ssd(void)
{
	init_ssd_control();
}

void main(void)
{
	unsigned char key;
	int key1 = 1;

	init_config();
	init_config_ssd();

	static short i = 0, j = 0, select = 0, option = 1;
	static short k = 0, l = 0, temp = 0;
	unsigned char num[]={ 0xE7, 0x21, 0xCB, 0x6B, 0x2D, 0x6E, 0xEE, 0x23, 0xEF, 0x6F};
	unsigned char id[]={0xA8, 0xE5, 0x08, 0x80, 0xE9};
	//	unsigned char ch1, ch2, ch3, ch4;

	/*//read from the eeprom to a character
	//l = read_internal_eeprom(0x01);
	//k = read_internal_eeprom(0x02);
	j = read_internal_eeprom(0x03);
	i = read_internal_eeprom(0x04);
	*/ssd[0] = '\0';
	ssd[1] = '\0';
	ssd[2] = '\0';
	ssd[3] = '\0';

	//while(1)
	{
	//	create_payload(local_can_payload);
//		can_transmit(local_can_payload);	
	}
	
	while (1)
	{
		if(RC0 == 0)
		{
			key_detected = 0;
		//	flag = !flag;
			LED8 = !LED8;
		}

		if(flag)
		{
			//key_detected = 0;

			key = read_digital_keypad(STATE_CHANGE);
			if(temp == 0)
			{

				if (key == SWITCH4)
				{	
					++option;

					if (option > 2)
					{
						option = 1;
					}
				}
					switch(option)
					{
						case 1:
							ssd[0] = id[0];
							select = 1;
							break;
						case 2:
							ssd[0] = id[1];
							select = 2;
					}
					ssd[1] = id[2];
					ssd[2] = id[3];
					ssd[3] = id[4];
				

				if (key == SWITCH3)
				{
					temp = 1;
					
					
					ssd[0] = num[0];
					ssd[1] = num[0];
					ssd[2] = num[0];
					ssd[3] = num[0];
					i = j = k = l = 0;
				}
			}
			else if(temp == 1)
			{

				if(key == SWITCH2)
				{	
					key1++;		

					if(key1 == 5)
					{
						key1 = 1;
					}
				}

				if (key1 == 1)
				{
					ssd[3] = num[l] & ~mask; //MSB
					ssd[0] = num[i] | mask; //MSB
					if(key == SWITCH1)
					{
						if (i < 9)
						{
							i++;
						}
						else
						{
							i = 0;
						}
					}
				}
				if (key1 == 2)
				{
					ssd[0] = num[i] & ~mask; //MSB
					ssd[1] = num[j] | mask;
					if(key == SWITCH1)
					{
						if (j < 9)
						{
							j++;
						}
						else
						{
							j = 0;
						}
					}
				}
				if (key1 == 3)
				{
					ssd[1] = num[j] & ~mask;
					ssd[2] = num[k] | mask;
					if(key == SWITCH1)
					{
						if (k < 9)
						{
							k++;
						}
						else
						{
							k = 0;
						}
					}
				}
				if(key1 == 4)
				{
					ssd[2] = num[k] & ~mask;
					ssd[3] = num[l] | mask;
					if(key == SWITCH1)
					{
						if (l < 9)
						{
							l++;
						}
						else
						{
							l = 0;
						}
					} //LSB
				}
				if (key == SWITCH4)
				{
					switch(select)
					{
						case 1:
							//write to the eeprom --N-id
							write_internal_eeprom(0x01, l);
							write_internal_eeprom(0x02, k);
							write_internal_eeprom(0x03, j);
							write_internal_eeprom(0x04, i);
							break;

						case 2:
							//write to the eeprom --U-id
							write_internal_eeprom(0x05, l);
							write_internal_eeprom(0x06, k);
							write_internal_eeprom(0x07, j);
							write_internal_eeprom(0x08, i);
							break;
					}
				
					can_payload[EIDH] = 0x00;
					can_payload[EIDL] = 0x00;
					can_payload[SIDH] = 0x6B;
					can_payload[SIDL] = 0xC0;
					can_payload[DLC] = 0x08;
					can_payload[D0] = read_internal_eeprom(0x01) + 48; //i+48;//0x35;//
					can_payload[D1] = read_internal_eeprom(0x02) + 48;//j+48;//0x34;//read_internal_eeprom(0x02) + 30;
					can_payload[D2] = read_internal_eeprom(0x03) + 48;
					can_payload[D3] = read_internal_eeprom(0x04) + 48;
					can_payload[D4] = read_internal_eeprom(0x05) + 30;
					can_payload[D5] = read_internal_eeprom(0x06) + 30;
					can_payload[D6] = read_internal_eeprom(0x07) + 30;
					can_payload[D7] = '\0';//read_internal_eeprom(0x08) + 30;	
				
				//	create_payload(local_can_payload);
					can_transmit(can_payload);
					
					flag = 0;
					temp = 0;

				}
			}
		}
		else
		{
			temp = 0;	
			ssd[0] = 0xE7;
			ssd[1] = 0x8F;
			ssd[2] = 0xCE;
			ssd[3] = 0xAF;

		}
		display(ssd);

	}
}

