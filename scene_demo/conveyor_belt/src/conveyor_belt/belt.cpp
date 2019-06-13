#include "main.h"
void belt_init()
{
  pinMode( MS3, OUTPUT );
  pinMode( MS2, OUTPUT );
  pinMode( MS1, OUTPUT );
  pinMode( STEP_PWM, OUTPUT );

  digitalWrite( MS1, LOW );
  digitalWrite( MS2, HIGH );
  digitalWrite( MS3, LOW );
  digitalWrite( STEP_PWM, HIGH );
}
void belt_move()
{
  set_speed(-1, 200, NULL, false);
}
void belt_stop()
{ 
  set_speed(-1, -1, NULL, true);
}
