#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H

#define LEVEL					0
#define STATE_CHANGE			1

#define SWITCH1					0x0E
#define SWITCH2					0x0D
#define SWITCH3					0x0B
#define SWITCH4					0x07
#define ALL_RELEASED			0x0F

#define INPUT_PINS				0x0F


unsigned char read_digital_keypad(unsigned char detection_type);
void init_digital_keypad(void);

#endif
