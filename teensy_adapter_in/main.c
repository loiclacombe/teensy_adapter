/*
 * main program
 */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>

#include "usb_debug_only.h"
#include "print.h"
#include "io_pin_utils.h"
#include "modules/snes.h"
#include "common/gamepad_status.h"

#define LED_CONFIG	(DDRD |= (1<<6))
#define LED_ON		(PORTD &= ~(1<<6))
#define LED_OFF		(PORTD |= (1<<6))
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

#define ON 1
#define OFF 0

void set_cpu_to_16_mhz(void) {
	// set for 16 MHz clock, and turn on the LED
	CPU_PRESCALE(0);
}

void initialize(void) {
	set_cpu_to_16_mhz();
	disable_analog_inputs();

	snes_setup_pins_for_readout();
	LED_CONFIG;
	LED_ON;

	// initialize the USB, and then wait for the host
	// to set configuration.  If the Teensy is powered
	// without a PC connected to the USB port, this 
	// will wait forever.
	usb_init();
	while (!usb_configured())
		/* wait */
		;

	// wait an extra second for the PC's operating system
	// to load drivers and do whatever it does to actually
	// be ready for input
	_delay_ms(1000);
}

void print_button_status(uint8_t index) {
	if (gamepad_status.buttons & button_mask(index))
		print("1");
	else
		print("0");
}

void print_axis_status(int8_t axis_data) {
	if (axis_data < 0) {
		axis_data = -axis_data;
		print("-");
	}
	if(axis_data){
		print("1");
	}else{
		print("0");
	}

}

unsigned int print_count = 0;

void debug_snes_print_buttons_status(void) {
	print_count++;
	phex16(print_count);
	print(" Status ");

	print("B=");
	print_button_status(SNES_BUTTON_B);
	print(", Y=");
	print_button_status(SNES_BUTTON_Y);
	print(", SELECT=");
	print_button_status(SNES_BUTTON_SELECT);
	print(", START=");
	print_button_status(SNES_BUTTON_START);
	print(", Y_AXIS=");
	print_axis_status(gamepad_status.y_axis);
	print(", X_AXIS=");
	print_axis_status(gamepad_status.x_axis);
	print(", A=");
	print_button_status(SNES_BUTTON_A);
	print(", X=");
	print_button_status(SNES_BUTTON_X);
	print(", L=");
	print_button_status(SNES_BUTTON_L);
	print(", R=");
	print_button_status(SNES_BUTTON_R);
	print("\n");
}

#define circular_counter_size 60

int main(void) {
	uint8_t print_circular_counter = 0;
	initialize();

	// start printing stuff.  If hid_listen is running on
	// the host, this should appear.
	print("Starting USB debug\n");

	while (1) {
		snes_read_buttons();

		if (!print_circular_counter) {
			debug_snes_print_buttons_status();
		}
		print_circular_counter++;
		print_circular_counter = print_circular_counter % circular_counter_size;

	}
}

