#include "main.h"
enum pick_mode_e mode;
extern enum control_systerm system_s;
extern int i;//finish block number
extern bool reset_flag;
extern enum pick_mode_e lastmode;
bool finish_flag = false;
Ultrasonic ultrasonic(23);//Ultrasonic module
void slide_pick_up()
{
  Serial2.write("G0 X250 Y0 Z160 F100\n");
  delay(500);
  Serial2.write("G0 X250 Y100 Z100 F100\n");
  delay(100);
  Serial2.write("G0 X250 Y100 Z100 F100\n");
  delay(100);
  Serial2.write("G0 X250 Y100 Z-25 F100\n");
  delay(2000);
  Serial2.write("M2231 V1\n");
  delay(1000);
  Serial2.write("G0 X180 Y0 Z160 F100\n");
  delay(1000);
}
void slide_pick_down()
{
  switch (mode) {
    case RED_MODE:
      Serial2.write("G0 X200 Y-80 Z100 F100\n");
      delay(100);
      Serial2.write("G0 X200 Y-80 Z-45 F100\n");
      delay(100);
      delay(1000);
      Serial2.write("M2231 V0\n");
      delay(1000);
      Serial2.write("G0 X180 Y0 Z160 F100\n");
      delay(2000);
      set_steps(5000, 30, NULL, true );
      Serial.println("Slider_red");
      break;
    case GREEN_MODE:
      Serial2.write("G0 X200 Y0 Z100 F100\n");
      delay(100);
      Serial2.write("G0 X200 Y0 Z-45 F100\n");
      delay(100);
      delay(1000);
      Serial2.write("M2231 V0\n");
      delay(1000);
      Serial2.write("G0 X180 Y0 Z160 F100\n");
      delay(2000);
      set_steps(10000, 30, NULL, true );
      Serial.println("Slider_Green");
      break;
    case YELLOW_MODE:
      Serial2.write("G0 X200 Y80 Z100 F100\n");
      delay(100);
      Serial2.write("G0 X200 Y80 Z-45 F100\n");
      delay(100);
      delay(1000);
      Serial2.write("M2231 V0\n");
      delay(1000);
      Serial2.write("G0 X180 Y0 Z160 F100\n");
      delay(2000);
      set_steps(15000, 30, NULL, true );            
      Serial.println("Slider_Yellow");
      break;
  }
}
void uarm_slider_pick()
{
  get_color();
  if (mode != NOTHING_MODE && reset_flag == true)
  {
    if (finish_flag == true && lastmode != NOTHING_MODE)
    {
      Serial.println("seconde");
      switch (lastmode)
      {
        Serial.println("secondresete");
        case YELLOW_MODE: set_steps(21500, 30, NULL, true );   Serial.println("yellow");
          break;
        case RED_MODE:    set_steps(31500, 30, NULL, true );   Serial.println("red");
          break;
        case GREEN_MODE:  set_steps(26500, 30, NULL, true );   Serial.println("green");
          break;
      }
      lastmode = NOTHING_MODE;
    }
    Serial.println("start_work");
    delay(1000);
    if (digitalRead(25) == HIGH)
    {
      Serial.println("picking");
      slide_pick_up();
      if(ultrasonic.MeasureInCentimeters() < 10 ){i++;} 
    }
    if (i >= 1 && lastmode == NOTHING_MODE)
    {
      Serial.println("first");
      set_steps(-36500, 30, NULL, true );
      delay(1000);
      finish_flag = true;
    }
    slide_pick_down();
    lastmode = mode;
    Serial.println("end");
  }
  mode = NOTHING_MODE;
}
