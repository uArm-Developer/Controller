#ifndef _LED_H
#define _LED_H
#include "main.h"
#define RGB_LED_R 2
#define RGB_LED_G 3
#define RGB_LED_B 5
#define R_LED   {digitalWrite(RGB_LED_R,LOW);  \
                 digitalWrite(RGB_LED_G,HIGH); \
                 digitalWrite(RGB_LED_B,HIGH); }
                 
#define B_LED   {digitalWrite(RGB_LED_B,LOW);  \
                 digitalWrite(RGB_LED_G,HIGH); \
                 digitalWrite(RGB_LED_R,HIGH); } 
                 
#define G_LED   {digitalWrite(RGB_LED_G,LOW);  \
                 digitalWrite(RGB_LED_R,HIGH); \
                 digitalWrite(RGB_LED_B,HIGH); }   
                 
#define LED_OFF {digitalWrite(RGB_LED_G,HIGH);  \
                 digitalWrite(RGB_LED_R,HIGH); \
                 digitalWrite(RGB_LED_B,HIGH); }                           
void led_init();
#endif
