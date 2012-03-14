

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>


int u8g_sdl_get_key(void);

void u8g_DrawCircle(u8g_t *u8g, u8g_uint_t x0, u8g_uint_t y0, u8g_uint_t rad, uint8_t option);


int main(void)
{
  
  u8g_t u8g;
  uint8_t rad;
  
  u8g_Init(&u8g, &u8g_dev_sdl_1bit);
  u8g_FirstPage(&u8g);
  
  do
  {
    //u8g_SetFont(&u8g, u8g_font_unifont);
    //u8g_SetFont(&u8g, u8g_font_osb18r);
    
    for( rad = 2+3*2; rad < 30; rad += 3 )
    {
      u8g_DrawEmpCirc(&u8g, 0, 35, rad, U8G_CIRC_UPPER_RIGHT);
      u8g_DrawCircle(&u8g, 0, 35+35, rad, U8G_CIRC_UPPER_RIGHT);
      
      u8g_DrawEmpCirc(&u8g, 0+31, 5, rad, U8G_CIRC_LOWER_RIGHT);
      u8g_DrawCircle(&u8g, 0+31, 5+35, rad, U8G_CIRC_LOWER_RIGHT);

      u8g_DrawEmpCirc(&u8g, 30+31*2, 5, rad, U8G_CIRC_LOWER_LEFT);
      u8g_DrawCircle(&u8g, 30+31*2, 5+35, rad, U8G_CIRC_LOWER_LEFT);

      u8g_DrawEmpCirc(&u8g, 0+31*4, 35, rad, U8G_CIRC_UPPER_LEFT);
      u8g_DrawCircle(&u8g, 0+31*4, 35+35, rad, U8G_CIRC_UPPER_LEFT);
      
    }
  } while( u8g_NextPage(&u8g) );

  while( u8g_sdl_get_key() < 0 )
    ;
  
  return 0;
}

