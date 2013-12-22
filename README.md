teensy_adapter
==============

Teensy joystick adapter

The code (and soon, the schematics) of a whatever custom joystick to SNES converter.
The final objective is to have at least a NES, SNES, Genesis and Playstation adapter. 

There are two sub projects:
*teensy_adapter_in -> A project to experiment around controllers readouts, to fully ensure the comprehension of the protocol, and of the pinouts. The controller will be converted to a HID keyboard.
*teensy_adapter_out -> The joystick to whatever support converter