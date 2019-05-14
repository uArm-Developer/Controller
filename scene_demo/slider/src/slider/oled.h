#ifndef   _OLED_H
#define   _OLED_H
#include <U8glib.h>
#include <stdio.h>
#include <Arduino.h>
#define LCD_CS              42
#define LCD_RES             43
#define LCD_CD              44
#define LCD_SCK             30
#define LCD_MOSI            35


void oled_init();


void first_page();

#endif 
