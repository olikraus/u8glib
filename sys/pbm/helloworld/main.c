

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>


int main(void)
{
  u8g_uint_t w,h;
  u8g_t u8g;
  
  u8g_Init(&u8g, &u8g_dev_pbm_8h1);
  u8g_FirstPage(&u8g);
  do
  {
    u8g_SetColorIndex(&u8g, 1);
    u8g_SetFont(&u8g, u8g_font_10x20);
    w = u8g_GetFontBBXWidth(&u8g);
    h = u8g_GetFontBBXHeight(&u8g);
    u8g_DrawStr(&u8g, 0, h, "Hello World!");
  }while( u8g_NextPage(&u8g) );
  return 0;
}



