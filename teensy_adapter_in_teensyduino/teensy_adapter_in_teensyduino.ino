/*

 
 */

const int SNES_DATA_LATCH_PIN = 20;
const int SNES_DATA_CLOCK_PIN= 21;
const int SNES_DATA_IN_PIN = 19;

const int SNES_BUTTON_B = 1;
const int SNES_BUTTON_A = 2;
const int SNES_BUTTON_Y = 3;
const int SNES_BUTTON_X = 4;
const int SNES_BUTTON_L = 5;
const int SNES_BUTTON_R = 6;
const int SNES_BUTTON_SELECT = 7;
const int SNES_BUTTON_START = 8;

const int DIRECTION_UP = 0;
const int DIRECTION_DOWN = 180;
const int DIRECTION_LEFT = 270;
const int DIRECTION_RIGHT = 90;

const int DIRECTION_UP_LEFT = 315;

const int MEGADRIVE_BUTTON_A = 1;
const int MEGADRIVE_BUTTON_B = 2;
const int MEGADRIVE_BUTTON_C = 3;
const int MEGADRIVE_BUTTON_START = 4;

const int MEGADRIVE_DATA_RIGHT_PIN = 21;
const int MEGADRIVE_DATA_LEFT_PIN = 20;
const int MEGADRIVE_DATA_DOWN_PIN = 19;
const int MEGADRIVE_DATA_UP_PIN = 18;
const int MEGADRIVE_DATA_START_C_PIN = 17;
const int MEGADRIVE_SELECT_PIN = 16;
const int MEGADRIVE_DATA_A_B_PIN = 15;

const int MODE_SNES = 1;
const int MODE_GENESIS = 2;

const int HAT_DEFAULT = -1;

int hat_direction;

void snes_read_init(){
  pinMode(SNES_DATA_LATCH_PIN, OUTPUT); 
  pinMode(SNES_DATA_CLOCK_PIN, OUTPUT); 
  pinMode(SNES_DATA_IN_PIN, INPUT); 

  digitalWrite(SNES_DATA_LATCH_PIN, LOW);
  digitalWrite(SNES_DATA_CLOCK_PIN, LOW); 
}

void megadrive_init(){
  pinMode(MEGADRIVE_DATA_RIGHT_PIN, INPUT_PULLUP);
  pinMode(MEGADRIVE_DATA_LEFT_PIN, INPUT_PULLUP);
  pinMode(MEGADRIVE_DATA_DOWN_PIN, INPUT_PULLUP);
  pinMode(MEGADRIVE_DATA_UP_PIN, INPUT_PULLUP);
  pinMode(MEGADRIVE_DATA_LEFT_PIN, INPUT_PULLUP);
  pinMode(MEGADRIVE_DATA_START_C_PIN, INPUT_PULLUP);
  pinMode(MEGADRIVE_DATA_A_B_PIN, INPUT_PULLUP);

  pinMode(MEGADRIVE_SELECT_PIN, OUTPUT);
  digitalWrite(MEGADRIVE_SELECT_PIN, HIGH); 
}

void megadrive_read_buttons(){ 
  megadrive_read_axis_y(MEGADRIVE_DATA_RIGHT_PIN, DIRECTION_UP);
  megadrive_read_axis_y(MEGADRIVE_DATA_RIGHT_PIN, DIRECTION_DOWN);
  megadrive_read_axis_x(MEGADRIVE_DATA_RIGHT_PIN, DIRECTION_RIGHT);
  megadrive_read_axis_x(MEGADRIVE_DATA_RIGHT_PIN, DIRECTION_LEFT);
  Joystick.hat(hat_direction);
  
  megadrive_read_button(MEGADRIVE_BUTTON_C, MEGADRIVE_DATA_START_C_PIN);
  megadrive_read_button(MEGADRIVE_BUTTON_B, MEGADRIVE_DATA_A_B_PIN);
  
  digitalWrite(MEGADRIVE_SELECT_PIN, LOW); 
  delayMicroseconds(20);
  megadrive_read_button(MEGADRIVE_BUTTON_START, MEGADRIVE_DATA_START_C_PIN);
  megadrive_read_button(MEGADRIVE_BUTTON_A, MEGADRIVE_DATA_A_B_PIN);
  digitalWrite(MEGADRIVE_SELECT_PIN, HIGH); 
  delay(16);
  delayMicroseconds(666);
}

void megadrive_read_button(int button_index, int pin_index){
  Joystick.button(button_index, !digitalRead(pin_index));
}

void megadrive_read_axis_y(int pin_index, int axis_value){
  if(digitalRead(pin_index)){
    hat_direction = axis_value;
  }
}

void megadrive_read_axis_x(int pin_index, int direction){
  if(digitalRead(pin_index)){

    if(hat_direction == HAT_DEFAULT){
      hat_direction = direction;
    } 
    else {
      if(hat_direction == DIRECTION_UP 
        && direction == DIRECTION_LEFT){
        hat_direction = DIRECTION_UP_LEFT;
      }
      else{
        hat_direction = (hat_direction + direction) / 2;
      }
    }
  }
}

void setup() {
  megadrive_read_buttons();

  Serial.begin(9600);
}

void snes_read_button_raw(int button_index){
  Joystick.button(button_index, !digitalRead(SNES_DATA_IN_PIN));
}

void snes_read_button(int button_index){
  digitalWrite(SNES_DATA_CLOCK_PIN, HIGH);
  delayMicroseconds(12);
  snes_read_button_raw(button_index);
  digitalWrite(SNES_DATA_CLOCK_PIN, LOW);
}


void snes_read_axis_y(int direction){
  digitalWrite(SNES_DATA_CLOCK_PIN, HIGH);
  delayMicroseconds(12);

  if(!digitalRead(SNES_DATA_IN_PIN)){
    hat_direction = direction;
  }

  digitalWrite(SNES_DATA_CLOCK_PIN, LOW);
}

void snes_read_axis_x(int direction){
  digitalWrite(SNES_DATA_CLOCK_PIN, HIGH);
  delayMicroseconds(12);

  if(!digitalRead(SNES_DATA_IN_PIN)){
    if(hat_direction == HAT_DEFAULT){
      hat_direction = direction;
    } 
    else {
      if(hat_direction == DIRECTION_UP 
        && direction == DIRECTION_LEFT){
        hat_direction = DIRECTION_UP_LEFT;
      }
      else{
        hat_direction = (hat_direction + direction) / 2;
      }
    }
  }

  digitalWrite(SNES_DATA_CLOCK_PIN, LOW);
}

void snes_read_buttons(){
  digitalWrite(SNES_DATA_LATCH_PIN, HIGH);
  delayMicroseconds(12);
  digitalWrite(SNES_DATA_LATCH_PIN, LOW);
  delayMicroseconds(6);

  snes_read_button_raw(SNES_BUTTON_B);
  snes_read_button(SNES_BUTTON_Y);
  snes_read_button(SNES_BUTTON_SELECT);
  snes_read_button(SNES_BUTTON_START);

  hat_direction = HAT_DEFAULT;
  snes_read_axis_y(DIRECTION_UP);
  snes_read_axis_y(DIRECTION_DOWN);
  snes_read_axis_x(DIRECTION_LEFT);
  snes_read_axis_x(DIRECTION_RIGHT);

  Joystick.hat(hat_direction);

  snes_read_button(SNES_BUTTON_A);
  snes_read_button(SNES_BUTTON_X);
  snes_read_button(SNES_BUTTON_L);
  snes_read_button(SNES_BUTTON_R);

  delay(16);
  delayMicroseconds(466); 
  Serial.println(hat_direction, DEC);
}

void loop() {
  snes_read_buttons();
}
















