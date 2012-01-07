

#include "U8glib.h"
#include <stdlib.h>
#include <stdio.h>


int u8g_sdl_get_key(void);

U8GLIB u8g(&u8g_dev_sdl_2bit);

void drawLogo(uint8_t d)
{
  u8g.setFont(u8g_font_gdr25);
  u8g.drawStr(0+d, 30+d, "U");
  u8g.setFont(u8g_font_gdr30);
  u8g.drawStr90(23+d,10+d,"8");
  u8g.setFont(u8g_font_gdr25);
  u8g.drawStr(53+d,30+d,"g");
  
  u8g.drawHLine(2+d, 35+d, 47);
  u8g.drawVLine(45+d, 32+d, 12);
}

void drawURL(void)
{
  u8g.setFont(u8g_font_4x6);
  u8g.drawStr(1,54,"code.google.com/p/u8glib");
}

void draw(void)
{
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

int main(void)
{  
  u8g.firstPage();
  
  do
  {
    draw();
  } while( u8g.nextPage() );

  while( u8g_sdl_get_key() < 0 )
    ;
}

