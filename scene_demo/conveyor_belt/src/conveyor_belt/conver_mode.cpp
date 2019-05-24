#include "main.h"
enum pick_mode_e mode;
extern enum control_systerm system_s;
extern int i;
extern bool work_state;
extern bool detect_switch_flag;
extern   uint16_t r, g, b, c;
extern Ultrasonic ultrasonic;
void covert_pick_up()
{
  Serial2.write("G0 X69 Y-217 Z100 F100\n"); delay(100);
  Serial2.write("G2202 N3 V108 F100\n"); delay(500);
  Serial2.write("G0 X59 Y-217 Z15 F100\n"); delay(2000);
  Serial2.write("M2231 V1\n"); delay(100);
  Serial2.write("G0 X69 Y-217 Z100 F100\n"); delay(2000);
  Serial2.write("G2202 N3 V40 F100\n"); delay(100);
  Serial2.write("G0 X156 Y0 Z100 F100\n"); delay(100);
  Serial2.write("G0 X156 Y0 Z52 F100\n"); delay(2000);
  Serial2.write("M2231 V0\n"); delay(100);
  Serial2.write("G0 X165 Y0 Z100 F100\n"); delay(100);
  Serial2.write("G0 X180 Y0 Z160 F100\n"); delay(100);
}
void covert_pick_down()
{
  Serial3.write("G0 X157 Y59 Z80 F100\n"); delay(500);
  Serial3.write("G0 X157 Y59 Z40 F100\n"); delay(1500);
  Serial3.write("M2231 V1\n"); delay(1500);
  Serial3.write("G0 X157 Y59 Z160 F100\n"); delay(400);
  Serial3.write("G0 X160 Y59 Z160 F100\n"); delay(100);
  Serial2.write("G2202 N3 V90\n"); delay(500);
  switch (mode) {
    case RED_MODE :
      Serial.println("RED");
      Serial3.write("G0 X160 Y180 Z160 F100\n"); delay(1000);
      Serial3.write("G0 X160 Y180 Z10 F100\n"); delay(1000);
      Serial3.write("M2231 V0\n");
      Serial3.write("G0 X160 Y180 Z160 F100\n"); delay(100);
      break;
    case GREEN_MODE:
      Serial.println("GREEN");
      Serial3.write("G0 X160 Y230 Z160 F100\n"); delay(1000);
      Serial3.write("G0 X160 Y230 Z10 F100\n"); delay(1000);
      Serial3.write("M2231 V0\n");
      Serial3.write("G0 X160 Y230 Z160 F100\n"); delay(100);
      break;
    case YELLOW_MODE:
      Serial.println("YELLOW");
      Serial3.write("G0 X160 Y280 Z160 F100\n"); delay(1000);
      Serial3.write("G0 X160 Y280 Z10 F100\n"); delay(1000);
      Serial3.write("M2231 V0\n");
      Serial3.write("G0 X160 Y280 Z160 F100\n"); delay(100);
      break;
  }
  Serial3.write("G0 X180 Y0 Z160 F100\n");
  delay(400);
}
void uarm_reset()
{
  Serial2.write("G0 X180 Y0 Z160 F100\n"); delay(100);
  Serial3.write("G0 X180 Y0 Z160 F100\n");
}
void conver_work()
{
  if ( (digitalRead(25) == LOW) && (!work_state) ) {
    Serial.print( "start\r\n" );
    work_state = true;
    covert_pick_up();
    belt_move();
    detect_switch_flag = true;
  }
  if (work_state == true)
  {
    if (mode != NOTHING_MODE)
    {
      Serial.println(mode);
      belt_stop();
      covert_pick_down();
      work_state = false;
    }
    if ( detect_switch_flag ) {
      static bool detect_flag = false;
      if ( ultrasonic.MeasureInCentimeters() < 10 ) {
        if ( !detect_flag ) {
          i++;
          detect_switch_flag = false;
          set_speed(-1, -1, NULL, true);
          set_speed(-1, 200, NULL, true);
          Serial.println("en");
        }
        detect_flag = true;
      } else {
        detect_flag = false;
      }
    }
  }
}
