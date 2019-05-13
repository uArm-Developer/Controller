#include "main.h"
U8GLIB_SH1106_128X64 u8g(LCD_SCK, LCD_MOSI, LCD_CS, LCD_CD);  // SW SPI Com: SCK = 52, MOSI = 51, CS = 42, CD = 44
extern int x_uarm, y_uarm;
extern int x_offest, y_offest;
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
    u8g.drawStr(30, 20, "vision demo");
    u8g.drawStr(20, 40, "click buttonA ");
    u8g.drawStr(35, 60, "to start");
  } while (u8g.nextPage());
}
void second_page()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_cu12);
    u8g.drawStr(25, 20, "vision start");
    u8g.drawStr(10, 40, "waiting for cube");
  } while (u8g.nextPage());
}
void third_page()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_cu12);
    u8g.drawStr(25, 20, "vision start");
    u8g.drawStr(10, 40, "finding for cube");
  } while (u8g.nextPage());
}
void fourth_page()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_cu12);
    u8g.drawStr(10, 20, "error:disconnect  ");
    u8g.drawStr(10, 40, " with openmv ");
    u8g.drawStr(10, 60, "");
  } while (u8g.nextPage());
}
void fifth_page()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_tpss);
    u8g.drawStr(10, 15, "   handing cube  ");
    u8g.drawStr(30, 30, "   x:");
    u8g.setPrintPos(75, 30);

    u8g.print(x_uarm);
    u8g.drawStr(30, 45, "   y:");
    u8g.setPrintPos(75, 45);

    u8g.print(y_uarm);
            u8g.drawStr(0, 60, "buttonD:choose cube");

  } while (u8g.nextPage());
}
void sixth_page()//connect  but no cube
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_tpss);
    u8g.drawStr(10, 20, "error: cube is   ");
    u8g.drawStr(10, 40, "not exits ");
        u8g.drawStr(0, 60, "buttonD:choose cube");
  } while (u8g.nextPage());
}
void  mode_page()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_tpss);
    u8g.drawStr(0, 15, "buttonA:redcube");
    u8g.drawStr(0, 30, "buttonB:greencube");
    u8g.drawStr(0, 45, "buttonC:yellowcube");
    u8g.drawStr(0, 60, "buttonD:offestmode");

  } while (u8g.nextPage());
}
void offest_page()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_tpss);
    u8g.drawStr(10, 15, "   offest mode ");
    u8g.drawStr(0, 30, "  x_offest:");
    u8g.setPrintPos(95, 30);

    u8g.print(x_offest);
    u8g.drawStr(0, 45, "  y_offest:");
    u8g.setPrintPos(95, 45);

    u8g.print(y_offest);
        u8g.drawStr(10, 60, "buttonD:choose cube");

  } while (u8g.nextPage());

}
