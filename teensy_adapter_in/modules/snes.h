/*
 * snes.h
 *
 *  Created on: 22 déc. 2013
 *      Author: Damaki
 */

#ifndef SNES_H_
#define SNES_H_

#define SNES_BUTTON_B 0
#define SNES_BUTTON_Y 1
#define SNES_BUTTON_SELECT 2
#define SNES_BUTTON_START 3
#define SNES_BUTTON_UP 4
#define SNES_BUTTON_DOWN 5
#define SNES_BUTTON_LEFT 6
#define SNES_BUTTON_RIGHT 7
#define SNES_BUTTON_A 8
#define SNES_BUTTON_X 9
#define SNES_BUTTON_L 10
#define SNES_BUTTON_R 11

void snes_set_data_latch_to_high(void);
void snes_set_data_latch_to_low(void);
void snes_set_data_clock_to_high(void);
void snes_set_data_clock_to_low(void);
uint8_t snes_read_button(void);

extern uint8_t buttons_status[];

void snes_read_buttons(void);
void snes_setup_pins_for_readout(void);

#endif /* SNES_H_ */
