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

#define LED_CONFIG	(DDRD |= (1<<6))
#define LED_ON		(PORTD &= ~(1<<6))
#define LED_OFF		(PORTD |= (1<<6))
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

#define ON 1
#define OFF 0

uint8_t buttons_status[] = {
OFF, OFF, OFF, OFF,
OFF, OFF, OFF, OFF,
OFF, OFF, OFF, OFF,
ON, ON, ON, ON };

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

void print_status(uint8_t index) {
	if (buttons_status[index])
		phex(1);
	else
		phex(0);
}

unsigned int print_count=0;

void snes_print_buttons_status(void) {
	print_count++;
	phex16(print_count);
	print(" Status ");

	print("B=");
	print_status(SNES_BUTTON_B);
	print(", Y=");
	print_status(SNES_BUTTON_Y);
	print(", SELECT=");
	print_status(SNES_BUTTON_SELECT);
	print(", START=");
	print_status(SNES_BUTTON_START);
	print(", UP=");
	print_status(SNES_BUTTON_UP);
	print(", DOWN=");
	print_status(SNES_BUTTON_DOWN);
	print(", LEFT=");
	print_status(SNES_BUTTON_LEFT);
	print(", RIGHT=");
	print_status(SNES_BUTTON_RIGHT);
	print(", A=");
	print_status(SNES_BUTTON_A);
	print(", X=");
	print_status(SNES_BUTTON_X);
	print(", L=");
	print_status(SNES_BUTTON_L);
	print(", R=");
	print_status(SNES_BUTTON_R);
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
			snes_print_buttons_status();
		}
		print_circular_counter++;
		print_circular_counter = print_circular_counter % circular_counter_size;

		_delay_ms(16);
		_delay_us(466);
	}
}

