#include "main.h"
U8GLIB_SH1106_128X64 u8g(LCD_SCK, LCD_MOSI, LCD_CS, LCD_CD);  // SW SPI Com: SCK = 52, MOSI = 51, CS = 42, CD = 44
enum control_systerm system_s = waitmode;
int i;
void   oled_init()
{
  //olcddriver
  pinMode(LCD_RES, OUTPUT);
  digitalWrite(LCD_RES, HIGH);
}
void first_page()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_cu12);
    u8g.drawStr(30, 20, "slider");
    u8g.drawStr(30, 40, "count:");
    u8g.setPrintPos(75, 40);
    u8g.print(i);
  } while (u8g.nextPage());
}
