#ifndef _BELT_H
#define _BELT_H
#include <FlexiTimer2.h>
#include <Arduino.h>
#define STEP_PWM              7
#define MS3                   A12
#define MS2                   A11
#define MS1                   A10

void belt_init();

void belt_move();

void belt_stop();



#endif
