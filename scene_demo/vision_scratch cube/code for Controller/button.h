#ifndef _BUTTO_H
#define _BUTTO_H

#include <Arduino.h>

#define BUTTON_A        47
#define BUTTON_B        49
#define BUTTON_C        12
#define BUTTON_D        11

void button_mode();
void button_init();
bool mode_choose();

#endif
