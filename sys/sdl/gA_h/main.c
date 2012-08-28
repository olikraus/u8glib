/*
  check font 
*/

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>


int u8g_sdl_get_key(void);


void glyph(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t encoding)
{
  char s[2] = ".";
  u8g_GetGlyph(u8g, encoding);
  s[0] = encoding;
  u8g_DrawStr(u8g, x, y, "öÄ");
  u8g_DrawPixel(u8g, x, y);
  u8g_DrawPixel(u8g, x-1, y);
  //u8g_DrawPixel(u8g, x, y-u8g->glyph_y);
}

int main(void)
{
  u8g_t u8g;
  
  u8g_Init(&u8g, &u8g_dev_sdl_1bit_h);
  u8g_FirstPage(&u8g);
  do
  {
    u8g_SetColorIndex(&u8g, 1);
    u8g_DrawPixel(&u8g,0,0);
    u8g_DrawPixel(&u8g,0,1);
    u8g_SetFont(&u8g, u8g_font_unifont);
    //u8g_SetFont(&u8g, u8g_font_10x20);
    //u8g_SetFont(&u8g, u8g_font_gdb17);
    u8g_SetFontRefHeightText(&u8g);
    //u8g_SetRefHeightAll(&u8g);
    
    //u8g_SetFontPosBaseline(&u8g);
    //u8g_SetFontPosCenter(&u8g);
    
    u8g_SetFontPosTop(&u8g);
    glyph(&u8g, 5,25, 'g');

    u8g_SetFontPosCenter(&u8g);
    glyph(&u8g, 5+25,25, 'g');
    
    u8g_SetFontPosBaseline(&u8g);
    glyph(&u8g, 5+2*25,25, 'g');

    u8g_SetFontPosBottom(&u8g);
    glyph(&u8g, 5+3*25,25, 'g');
    
  }while( u8g_NextPage(&u8g) );
  
  while( u8g_sdl_get_key() < 0 )
    ;
  
  return 0;
}



