/*
 * io_pin_utils.h
 *
 *  Created on: 22 déc. 2013
 *      Author: Damaki
 */

#ifndef IO_PIN_UTILS_H_
#define IO_PIN_UTILS_H_
#include <stdint.h>

void disable_analog_inputs(void);

uint8_t pin(uint8_t index);

void set_pinf_to_output(uint8_t index);
void set_pinf_to_input(uint8_t index);

void set_output_pinf_to_high(uint8_t index);
void set_output_pinf_to_low(uint8_t index);

void set_pinb_to_output(uint8_t index);
void set_pinb_to_input(uint8_t index);

void set_intput_pinf_to_pull_up(uint8_t index);

void set_ddrb_to_0(uint8_t index);
void set_ddrb_to_1(uint8_t index);

void set_ddrf_to_0(uint8_t index);
void set_ddrf_to_1(uint8_t index);

void set_ddrd_to_0(uint8_t index);
void set_ddrd_to_1(uint8_t index);

uint8_t read_pinf(uint8_t index);
uint8_t read_pinb(uint8_t index);

uint8_t read_pind(uint8_t index);

#endif /* IO_PIN_UTILS_H_ */
