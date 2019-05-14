#ifndef _Main_h_
#define _Main_h_
#include "oled.h"
#include "slide_mode.h"
#include "color_senor.h"
#include <Wire.h>
#include "Ultrasonic.h"
#include "step_lowlevel.h"
#include "led.h"
enum pick_mode_e {
  RED_MODE = 0,
  GREEN_MODE,
  YELLOW_MODE,
  NOTHING_MODE,
};//color_mode
enum control_systerm
{
  conver_belt = 0,
  slider,
  automode,
  waitmode,
}; 

#endif
