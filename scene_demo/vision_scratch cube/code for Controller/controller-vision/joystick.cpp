#include "main.h"
int x_offest = 0, y_offest = 0;
void joystick_init()
{
  pinMode(JOY_UP, INPUT_PULLUP);
  pinMode(JOY_DOWN, INPUT_PULLUP);
  pinMode(JOY_LEFT, INPUT_PULLUP);
  pinMode(JOY_RIGHT, INPUT_PULLUP);
  pinMode(JOY_CENTRE, INPUT_PULLUP);
}
void joystick_work()
{
  if (digitalRead(JOY_UP) == LOW) {
    delay(10);                              // <!
    if (digitalRead(JOY_UP) == LOW) {
      while (digitalRead(JOY_UP) == LOW);
      Serial.print("joystick up\r\n");
      x_offest -= 5;
    }
  }
  if (digitalRead(JOY_DOWN) == LOW) {
    delay(10);                              // <!
    if (digitalRead(JOY_DOWN) == LOW) {
      while (digitalRead(JOY_DOWN) == LOW);
      Serial.print("joystick down\r\n");
      x_offest += 5;
    }
  }
  if (digitalRead(JOY_LEFT) == LOW) {
    delay(10);                              // <!
    if (digitalRead(JOY_LEFT) == LOW) {
      while (digitalRead(JOY_LEFT) == LOW);
      Serial.print("joystick left\r\n");
      y_offest -= 5;
    }
  }
  if (digitalRead(JOY_RIGHT) == LOW) {
    delay(10);                              // <!
    if (digitalRead(JOY_RIGHT) == LOW) {
      while (digitalRead(JOY_RIGHT) == LOW);
      Serial.print("joystick right\r\n");
      y_offest += 5;
    }
  }
  if (digitalRead(JOY_CENTRE) == LOW) {
    delay(10);                              // <!
    if (digitalRead(JOY_CENTRE) == LOW) {
      while (digitalRead(JOY_CENTRE) == LOW);
      Serial.print("joystick center\r\n");
    }
  }
  offest_page();
}
