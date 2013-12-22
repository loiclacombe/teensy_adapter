/*
 * io_pin_utils.c
 *
 *  Created on: 22 déc. 2013
 *      Author: Damaki
 */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include "io_pin_utils.h"

inline void disable_analog_inputs(void) {
	DIDR0 = 0;
	DIDR1 = 0;
	DIDR2 = 0;
}

inline uint8_t pin(uint8_t index) {
	return 1 << index;
}

inline void set_pinf_to_output(uint8_t index) {
	DDRF |= pin(index);
}

inline void set_pinf_to_input(uint8_t index) {
	DDRF &= ~(pin(index));
}

inline void set_output_pinf_to_high(uint8_t index) {
	PORTF |= pin(index);
}

inline void set_output_pinf_to_low(uint8_t index) {
	PORTF &= ~(pin(index));
}

inline void set_intput_pinf_to_normal(uint8_t index) {
	set_ddrf_to_0(index);
}

inline void set_intput_pinf_to_pull_up(uint8_t index) {
	set_ddrf_to_1(index);
}

inline void set_pinb_to_output(uint8_t index) {
	set_ddrb_to_1(index);
}

inline void set_ddrb_to_0(uint8_t index) {
	DDRB &= ~(pin(index));
}

inline void set_ddrb_to_1(uint8_t index) {
	DDRB |= pin(index);
}

inline void set_ddrf_to_0(uint8_t index) {
	DDRF &= ~(pin(index));
}

inline void set_ddrf_to_1(uint8_t index) {
	DDRF |= pin(index);
}

inline uint8_t read_pinf(uint8_t index) {
	return PINF & pin(index);
}

inline void set_ddrd_to_0(uint8_t index) {
	DDRD &= ~(pin(index));
}

inline void set_ddrd_to_1(uint8_t index) {
	DDRD |= pin(index);
}

inline void set_pinb_to_input(uint8_t index) {
	set_ddrb_to_0(index);
}

inline uint8_t read_pinb(uint8_t index) {
	return PINB & (pin(index));
}

inline uint8_t read_pind(uint8_t index) {
	return PIND & (pin(index));
}

