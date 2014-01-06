/*


*/

#define DATA_LATCH_PIN 20
#define DATA_CLOCK_PIN 21
#define DATA_IN_PIN 19

#define SNES_BUTTON_B 1
#define SNES_BUTTON_Y 3
#define SNES_BUTTON_SELECT 7
#define SNES_BUTTON_START 8
#define SNES_DIRECTION_UP 0
#define SNES_DIRECTION_DOWN 180
#define SNES_DIRECTION_LEFT 270
#define SNES_DIRECTION_RIGHT 90
#define SNES_BUTTON_A 2
#define SNES_BUTTON_X 4
#define SNES_BUTTON_L 5
#define SNES_BUTTON_R 6

#define SNES_DIRECTION_UP_LEFT 315

#define HAT_DEFAULT -1

int hat_direction;

void snes_read_init(){
  pinMode(DATA_LATCH_PIN, OUTPUT); 
  pinMode(DATA_CLOCK_PIN, OUTPUT); 
  pinMode(DATA_IN_PIN, INPUT); 

  digitalWrite(DATA_LATCH_PIN, LOW);
  digitalWrite(DATA_CLOCK_PIN, LOW); 
}

void setup() {
  snes_read_init();

  Serial.begin(9600);
}

void snes_read_button_raw(int button_index){
  Joystick.button(button_index, !digitalRead(DATA_IN_PIN));
}

void snes_read_button(int button_index){
  digitalWrite(DATA_CLOCK_PIN, HIGH);
  delayMicroseconds(12);
  snes_read_button_raw(button_index);
  digitalWrite(DATA_CLOCK_PIN, LOW);
}

void snes_read_axis(int direction){
  digitalWrite(DATA_CLOCK_PIN, HIGH);
  delayMicroseconds(12);

  if(!digitalRead(DATA_IN_PIN)){
    if(hat_direction == HAT_DEFAULT){
      hat_direction = direction;
    } 
    else{
      if(hat_direction == SNES_DIRECTION_UP 
        && direction == SNES_DIRECTION_LEFT){
        hat_direction = SNES_DIRECTION_UP_LEFT;
      }
      else{
        hat_direction = (hat_direction + direction) / 2;
      }
    }
  }

  digitalWrite(DATA_CLOCK_PIN, LOW);
}

void snes_read_buttons(){
  digitalWrite(DATA_LATCH_PIN, HIGH);
  delayMicroseconds(12);
  digitalWrite(DATA_LATCH_PIN, LOW);
  delayMicroseconds(6);

  snes_read_button_raw(SNES_BUTTON_B);
  snes_read_button(SNES_BUTTON_Y);
  snes_read_button(SNES_BUTTON_SELECT);
  snes_read_button(SNES_BUTTON_START);

  hat_direction = HAT_DEFAULT;
  snes_read_axis(SNES_DIRECTION_UP);
  snes_read_axis(SNES_DIRECTION_DOWN);
  snes_read_axis(SNES_DIRECTION_LEFT);
  snes_read_axis(SNES_DIRECTION_RIGHT);

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













