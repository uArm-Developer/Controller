#include "main.h"
enum pick_mode mode = red_mode;
extern char  color_sel;
bool work_mode_flag;
int mode_change = 1;
extern char buf[20], flag;
extern int num;
extern unsigned long times;

void button_init()
{
  //buttondriver
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_D, INPUT_PULLUP);
}
void button_mode()
{
  if (digitalRead(BUTTON_A) == LOW) {
    delay(10);                              // <! delay
    if (digitalRead(BUTTON_A) == LOW) {
      while (digitalRead(BUTTON_A) == LOW);
      Serial.print("button b\r\n");
      color_sel = 1;
      work_mode_flag = true;
//          num = 0;
//    times = millis();
//    //flag = 0;
//    buf[0]='a';
    }
  }
  if (digitalRead(BUTTON_B) == LOW) {
    delay(10);                              // <! delay
    if (digitalRead(BUTTON_B) == LOW) {
      while (digitalRead(BUTTON_B) == LOW);
      Serial.print("button b\r\n");
      color_sel = 2;
      work_mode_flag = true;
//    num = 0;
//    times = millis();
//   // flag = 0;
//    buf[0]='a';
    }
  }
  if (digitalRead(BUTTON_C) == LOW) {
    delay(10);
    if (digitalRead(BUTTON_C) == LOW) {
      while (digitalRead(BUTTON_C) == LOW);
      Serial.print("button c\r\n");
      color_sel = 0;
      work_mode_flag = true;
//    num = 0;
//    times = millis();
//   // flag = 0;
//    buf[0]='a';
    }
  }
  if (digitalRead(BUTTON_D) == LOW) {
    delay(10);                              // <! delay
    if (digitalRead(BUTTON_D) == LOW) {
      while (digitalRead(BUTTON_D) == LOW);
      work_mode_flag = false;
      mode_change++;
    }
  }
}
bool mode_choose()
{
  button_mode();

  if (work_mode_flag == true)
  {

    return true;
  }
  if (work_mode_flag == false)
  {
    if (mode_change % 2 == 1)
    {
      mode_page();
    }
    else if (mode_change % 2 == 0)
    {

      joystick_work();

    }
    mode_choose();

  }
}
