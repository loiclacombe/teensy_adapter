#ifndef GAMEPAD_STATUS_H_
#define GAMEPAD_STATUS_H_

#include <stdint.h>

typedef struct {
	uint32_t buttons_mask;
	int8_t x_axis;
	int8_t y_axis;
} Buttons_Status;

uint32_t button_mask(uint8_t index);

extern Buttons_Status gamepad_status;

#endif /* GAMEPAD_STATUS_H_ */
