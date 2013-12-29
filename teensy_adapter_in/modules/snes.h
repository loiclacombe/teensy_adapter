/*
 * snes.h
 *
 *  Created on: 22 déc. 2013
 *      Author: Loic Lacombe
 *
 */

#ifndef SNES_H_
#define SNES_H_

enum SNES_BUTTONS{
	SNES_BUTTON_B = 0,
	SNES_BUTTON_Y = 1,
	SNES_BUTTON_SELECT = 2,
	SNES_BUTTON_START = 3,
	SNES_BUTTON_UP = 4,
	SNES_BUTTON_DOWN = 5,
	SNES_BUTTON_LEFT = 6,
	SNES_BUTTON_RIGHT = 7,
	SNES_BUTTON_A = 8,
	SNES_BUTTON_X = 9,
	SNES_BUTTON_L = 10,
	SNES_BUTTON_R = 11,
	SNES_NO_BUTTON = 12
};

#define SNES_DIR_UP 1
#define SNES_DIR_DOWN (-1)
#define SNES_DIR_RIGHT 1
#define SNES_DIR_LEFT (-1)

void snes_read_buttons(void);
void snes_setup_pins_for_readout(void);

#endif /* SNES_H_ */
