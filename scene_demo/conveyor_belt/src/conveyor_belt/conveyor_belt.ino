#include "main.h"
#define SOFTWARE_VERSION "V1.0\n"
extern enum control_systerm system_s;
extern enum pick_mode_e mode;
bool work_state = false;
bool detect_switch_flag = false;
extern Adafruit_TCS34725 tcs;
Ultrasonic ultrasonic(23);
extern int i;
void setup() {
  Serial.begin(115200);
  Serial.println(SOFTWARE_VERSION);
  Serial2.begin(115200);
  Serial3.begin(115200);
  pinMode(25, INPUT_PULLUP);
  belt_init();
  oled_init();
  convert_rgb();
  //initiate stepper driver
  step_init_ll();
  uarm_reset();
  tcs.begin();
  system_s = conver_belt;
  i = 0;
  mode = NOTHING_MODE;

}
void loop() {
  first_page();
  get_color();
  conver_work();
}
