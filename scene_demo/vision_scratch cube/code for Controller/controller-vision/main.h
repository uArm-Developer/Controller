#ifndef   _MAIN_H
#define   _MAIN_H
#include "oled.h"
#include "openmv.h"
#include "button.h"
#include "joystick.h"
#define LED_R 2
#define LED_ON digitalWrite(LED_R,LOW)
#define LED_OFF digitalWrite(LED_R,HIGH)
enum pick_mode
{
  red_mode,
  green_mode,
  yellow_mode,
};
enum commuincation{
  beready,
  bedoing,
  bedata,
  befailed
};
#endif 
