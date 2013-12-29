/*
 * snes.c
 *
 *  Created on: 22 déc. 2013
 *      Author: Loic Lacombe
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>

#include "../io_pin_utils.h"
#include "../common/gamepad_status.h"
#include "snes.h"

//private method
void snes_set_data_latch_to_high(void);
void snes_set_data_latch_to_low(void);
void snes_set_data_clock_to_high(void);
void snes_set_data_clock_to_low(void);
void snes_read_button(uint8_t index);

void snes_set_data_latch_to_high(void) {
	set_output_pinf_to_high(PORTF1);
}

void snes_set_data_latch_to_low(void) {
	set_output_pinf_to_low(PORTF1);
}

void snes_set_data_clock_to_high(void) {
	set_output_pinf_to_high(PORTF0);
}

void snes_set_data_clock_to_low(void) {
	set_output_pinf_to_low(PORTF0);
}

void snes_raw_read_button(uint8_t index) {
	if (!read_pinf(PORTF4)) {
		gamepad_status.buttons_mask |= button_mask(index);
	}
}

void snes_raw_read_axis(int8_t* p_axis, int8_t value) {
	if (!read_pinf(PORTF4)) {
		*p_axis = value;
	}
}

void snes_read_button(uint8_t index) {
	snes_set_data_clock_to_high();
	_delay_us(12);
	snes_raw_read_button(index);
	snes_set_data_clock_to_low();
}

void snes_read_axis(int8_t* p_axis, int8_t value) {
	snes_set_data_clock_to_high();
	_delay_us(12);
	snes_raw_read_axis(p_axis, value);
	snes_set_data_clock_to_low();
}

void snes_read_buttons(void) {
	snes_set_data_latch_to_high();
	_delay_us(12);
	snes_set_data_latch_to_low();
	_delay_us(6);

	gamepad_status.buttons_mask = 0;
	gamepad_status.y_axis=0;
	gamepad_status.x_axis=0;

	snes_raw_read_button(SNES_BUTTON_B);
	snes_read_button(SNES_BUTTON_Y);
	snes_read_button(SNES_BUTTON_SELECT);
	snes_read_button(SNES_BUTTON_START);

	snes_read_axis(&(gamepad_status.y_axis), SNES_DIR_UP);
	snes_read_axis(&(gamepad_status.y_axis), SNES_DIR_DOWN);
	snes_read_axis(&(gamepad_status.x_axis), SNES_DIR_LEFT);
	snes_read_axis(&(gamepad_status.x_axis), SNES_DIR_RIGHT);

	snes_read_button(SNES_BUTTON_A);
	snes_read_button(SNES_BUTTON_X);
	snes_read_button(SNES_BUTTON_L);
	snes_read_button(SNES_BUTTON_R);
	//4 empty reads
	snes_read_button(SNES_NO_BUTTON);
	snes_read_button(SNES_NO_BUTTON);
	snes_read_button(SNES_NO_BUTTON);

	_delay_ms(16);
	_delay_us(466);
}

void snes_setup_pins_for_readout(void) {

	set_pinf_to_output(PORTF0);
	set_pinf_to_output(PORTF1);
	set_pinf_to_input(PORTF4);

	set_output_pinf_to_high(PORTF0);
	set_output_pinf_to_high(PORTF1);
}

