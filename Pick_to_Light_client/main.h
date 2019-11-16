#ifndef MAIN_H
#define MAIN_H

/* Please use this file to use all architecture dependent contents like Port Informations, system specific header files etc. */
#include "pic_specific.h"
#include <xc.h>
#include "eeprom.h"
#include <string.h>
#include <stdlib.h>

/* Please use this file to use all architecture dependent contents like Port Informations, system specific header files etc. */

#define MAX_SSD_CNT		4
#define MAX_COUNT		9

#define COUNT_ADDR		0x00

#define ON					1
#define OFF					0
#define TRUE			1
#define FALSE			0
//#define OFF				0xFF

#endif
