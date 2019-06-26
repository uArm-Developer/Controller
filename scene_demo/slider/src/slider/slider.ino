#include "main.h"
#define SOFTWARE_VERSION "V1.2\n"
extern int i;
extern enum control_systerm system_s;
extern enum pick_mode_e mode;
extern Adafruit_TCS34725 tcs;
enum pick_mode_e lastmode = NOTHING_MODE;
void setup() {
  Serial.begin(115200);
  Serial.println(SOFTWARE_VERSION);
  Serial2.begin(115200);
  pinMode(25, INPUT_PULLUP); //limit switch
  Serial2.write("G0 X180 Y0 Z160 F100\n");
  oled_init();
  slider_rgb();//r g b value
  led_init();
  step_init();
  tcs.begin();
  system_s = slider;
  i = 0;
  mode = NOTHING_MODE;
}
void loop() {
  first_page();  
  belt_resetflag();
  if (system_s == slider)
  {
    uarm_slider_pick();
  }
}
