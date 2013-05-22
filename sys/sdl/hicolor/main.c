/*

  hicolor sdl example

*/

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>





int u8g_sdl_get_key(void);


int main(void)
{
  u8g_uint_t w,h;
  u8g_uint_t r, g, b, x, y;
  u8g_t u8g;
  
  u8g_Init(&u8g, &u8g_dev_sdl_hicolor);
  u8g_FirstPage(&u8g);
  do
  {
    u8g_SetFont(&u8g, u8g_font_10x20);
    u8g_SetFont(&u8g, u8g_font_fur25);

    /*
  for ( x = 0; x < 128; x++ )
    for ( y = 0; y < 64; y++ )
    {
      u8g_SetColorIndex(&u8g, ((x&3)+y*4) & 255);
      u8g_DrawPixel(&u8g, x, y);
    }
    */
  w = 2;
  h = 2;
  for( b = 0; b < 4; b++ )
    for( g = 0; g < 32; g++ )
      for( r = 0; r < 32; r++ )
      {
        u8g_SetHiColorByRGB(&u8g, r<<3, g<<3, b<<5 );
	u8g_DrawPixel(&u8g, g + b*32, r);
        u8g_SetHiColorByRGB(&u8g, r<<3, g<<3, (b<<5)+64 );
	u8g_DrawPixel(&u8g, g + b*32, r+32);
        //u8g_DrawBox(&u8g, g*w + b*w*16, r*h, w, h);
        //u8g_DrawBox(&u8g, g*w + b*w*16, r*h+32, w, h);
      }

    
    w = u8g_GetFontBBXWidth(&u8g);
    h = u8g_GetFontBBXHeight(&u8g);
    u8g_SetColorIndex(&u8g, 1);
    //u8g_SetHiColorByRGB(&u8g, 255, 255, 255);
    u8g_SetHiColor(&u8g, 0xffff);
    u8g_DrawStr(&u8g, 20, 40, "U8glib");
    //u8g_SetHiColorByRGB(&u8g, 0, 255, 0);
    u8g_SetHiColor(&u8g, 0x001f);
    u8g_DrawStr(&u8g, 20+1, 40+1, "U8glib");
    //u8g_SetHiColorByRGB(&u8g, 255, 255, 255);
    //u8g_DrawStr(&u8g, 20+2, 40+2, "U8glib");
    
  }while( u8g_NextPage(&u8g) );
  
  while( u8g_sdl_get_key() < 0 )
    ;
  
  return 0;
}



