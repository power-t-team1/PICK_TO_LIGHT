#ifndef CLCD_H
#define CLCD_H

/* Refer pic_specific.h for port specific definations */

#define INPUT											0xFF
#define OUTPUT											0x00

#define HI												1
#define LO												0

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0

#define LINE1(x)										(0x80 + (x))
#define LINE2(x)										(0xC0 + (x))

#define LEFT_ARROW										0x7F
#define RIGHT_ARROW										0x7E

#define TWO_LINE_5x7_MATRIX_8_BIT						clcd_write(0x38, INSTRUCTION_COMMAND)
#define ONE_LINE_5x7_MATRIX_8_BIT						clcd_write(0x30, INSTRUCTION_COMMAND)
#define TWO_LINE_5x10_MATRIX_8_BIT						clcd_write(0x3C, INSTRUCTION_COMMAND)
#define TWO_LINE_5x7_MATRIX_4_BIT						clcd_write(0x28, INSTRUCTION_COMMAND)
#define TWO_LINE_5x10_MATRIX_4_BIT						clcd_write(0x2C, INSTRUCTION_COMMAND)

#define	STABILIZE_LCD_4_BIT								clcd_write(0x33, INSTRUCTION_COMMAND)

#define MOV_CURSOR_TO_LINE1								clcd_write(0x80, INSTRUCTION_COMMAND)
#define MOV_CURSOR_ADDR(address)						clcd_write(address, INSTRUCTION_COMMAND)
#define MOV_CURSOR_TO_LINE2								clcd_write(0xC0, INSTRUCTION_COMMAND)
#define MOV_CURSOR_ADDR(address)						clcd_write(address, INSTRUCTION_COMMAND)

#define CLEAR_DISP_SCREEN								clcd_write(0x01, INSTRUCTION_COMMAND)
#define CLEAR_DISP_WITH_DELAY(delay)					clcd_write(0x01, INSTRUCTION_COMMAND)
#define CURSOR_HOME										clcd_write(0x02, INSTRUCTION_COMMAND)

#define DISP_OFF_AND_CURSOR_OFF							clcd_write(0x08, INSTRUCTION_COMMAND)
#define DISP_OFF_AND_CURSOR_ON							clcd_write(0x0A, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_ON							clcd_write(0x0E, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_OFF							clcd_write(0x0C, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_BILNK_OFF					clcd_write(0x0E, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_BILNK_ON						clcd_write(0x0F, INSTRUCTION_COMMAND)

#define	MOV_CURSOR_RIGHT								clcd_write(0x06, INSTRUCTION_COMMAND)
#define SHIFT_CURSOR_LEFT_WITH_DELAY(delay)				clcd_write(0x04, INSTRUCTION_COMMAND)
#define SHIFT_CURSOR_RIGHT_WITH_DELAY(delay)			clcd_write(0x07, INSTRUCTION_COMMAND)
#define SHIFT_CURSOR_POS_LEFT_WITH_DELAY(delay)			clcd_write(0x10, INSTRUCTION_COMMAND)
#define SHIFT_CURSOR_POS_RIGHT_WITH_DELAY(delay)		clcd_write(0x14, INSTRUCTION_COMMAND)
#define SHIFT_DISPLAY_LEFT_WITH_DELAY(delay)			clcd_write(0x07, INSTRUCTION_COMMAND)
#define SHIFT_DISPLAY_RIGHT_WITH_DELAY(delay)			clcd_write(0x05, INSTRUCTION_COMMAND)
#define SHIFT_ENTIRE_DISPLAY_LEFT_WITH_DELAY(delay)		clcd_write(0x18, INSTRUCTION_COMMAND)
#define SHIFT_ENTIRE_DISPLAY_RIGHT_WITH_DELAY(delay)	clcd_write(0x1C, INSTRUCTION_COMMAND)

void init_clcd(void);
void clcd_print(const unsigned char *data, unsigned char addr);
void clcd_putch(const unsigned char data, unsigned char addr);
void clcd_write(unsigned char bit_values, unsigned char control_bit);

#endif
