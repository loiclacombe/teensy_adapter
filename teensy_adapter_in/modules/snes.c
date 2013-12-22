/*
 * snes.c
 *
 *  Created on: 22 déc. 2013
 *      Author: Damaki
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>

#include "../io_pin_utils.h"
#include "snes.h"


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

uint8_t snes_raw_read_button(void) {
	return read_pinf(PORTF4);
}

uint8_t snes_read_button(void) {
	uint8_t val;
	snes_set_data_clock_to_high();
	_delay_us(12);
	val = snes_raw_read_button();
	snes_set_data_clock_to_low();
	return val;
}

void snes_read_buttons(void) {
	snes_set_data_latch_to_high();
	_delay_us(12);
	snes_set_data_latch_to_low();
	_delay_us(6);
	buttons_status[SNES_BUTTON_B] = snes_raw_read_button();
	buttons_status[SNES_BUTTON_Y] = snes_read_button();
	buttons_status[SNES_BUTTON_SELECT] = snes_read_button();
	buttons_status[SNES_BUTTON_START] = snes_read_button();
	buttons_status[SNES_BUTTON_UP] = snes_read_button();
	buttons_status[SNES_BUTTON_DOWN] = snes_read_button();
	buttons_status[SNES_BUTTON_LEFT] = snes_read_button();
	buttons_status[SNES_BUTTON_RIGHT] = snes_read_button();
	buttons_status[SNES_BUTTON_A] = snes_read_button();
	buttons_status[SNES_BUTTON_X] = snes_read_button();
	buttons_status[SNES_BUTTON_L] = snes_read_button();
	buttons_status[SNES_BUTTON_R] = snes_read_button();
	//4 empty reads
	snes_read_button();
	snes_read_button();
	snes_read_button();
	snes_read_button();

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




