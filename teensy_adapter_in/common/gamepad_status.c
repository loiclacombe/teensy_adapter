
#include "gamepad_status.h"

Buttons_Status gamepad_status;

inline uint32_t button_mask(uint8_t index){
	return 1 << index;
}
