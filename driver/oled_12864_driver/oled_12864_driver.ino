#include <U8glib.h>
/************************* LCD io *************************/
#define LCD_CS          42
#define LCD_RES         43
#define LCD_CD          44
#define LCD_SCK         8
#define LCD_MOSI        53

U8GLIB_SH1106_128X64 u8g(LCD_SCK, LCD_MOSI, LCD_CS, LCD_CD);  // SW SPI Com: SCK = 52, MOSI = 51, CS = 42, CD = 44

void setup() {
  // put your setup code here, to run once:
  pinMode(LCD_RES, OUTPUT);
  digitalWrite(LCD_RES, HIGH);
  u8g.firstPage();
  do{
    draw();
    u8g.setColorIndex(1);
  } while(u8g.nextPage());  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void drawColorBox(void) 
{
  u8g_uint_t w, h;
  u8g_uint_t r, g, b;

  w = u8g.getWidth() / 32;
  h = u8g.getHeight() / 8;
  for ( b = 0; b < 4; b++ )
    for ( g = 0; g < 8; g++ )
      for ( r = 0; r < 8; r++ ) 
      {
        u8g.setColorIndex((r << 5) |  (g << 2) | b );
        u8g.drawBox(g * w + b * w * 8, r * h, w, h);
      }
}

void drawLogo(uint8_t d) 
{
#ifdef MINI_LOGO
  u8g.setFont(u8g_font_gdr17r);
  u8g.drawStr(0 + d, 22 + d, "U");
  u8g.setFont(u8g_font_gdr20n);
  u8g.drawStr90(17 + d, 8 + d, "8");
  u8g.setFont(u8g_font_gdr17r);
  u8g.drawStr(39 + d, 22 + d, "g");

  u8g.drawHLine(2 + d, 25 + d, 34);
  u8g.drawVLine(32 + d, 22 + d, 12);
#else
  u8g.setFont(u8g_font_gdr25r);
  u8g.drawStr(0 + d, 30 + d, "U");
  u8g.setFont(u8g_font_gdr30n);
  u8g.drawStr90(23 + d, 10 + d, "8");
  u8g.setFont(u8g_font_gdr25r);
  u8g.drawStr(53 + d, 30 + d, "g");

  u8g.drawHLine(2 + d, 35 + d, 47);
  u8g.drawVLine(45 + d, 32 + d, 12);
#endif
}

void drawURL(void) 
{
#ifndef MINI_LOGO
  u8g.setFont(u8g_font_4x6);
  if ( u8g.getHeight() < 59 ) 
  {
    u8g.drawStr(53, 9, "code.google.com");
    u8g.drawStr(77, 18, "/p/u8glib");
  } 
  else 
  {
    u8g.drawStr(1, 54, "code.google.com/p/u8glib");
    u8g.drawStr(1, 64, "https://www.ufactory.cc");
  }
#endif
}


void draw(void) 
{
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) 
  {
    drawColorBox();
  }
  u8g.setColorIndex(1);
  if ( U8G_MODE_GET_BITS_PER_PIXEL(u8g.getMode()) > 1 ) 
  {
    drawLogo(2);
    u8g.setColorIndex(2);
    drawLogo(1);
    u8g.setColorIndex(3);
  }
  drawLogo(0);
  drawURL();
}
