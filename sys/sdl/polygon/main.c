

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>


int u8g_sdl_get_key(void);

int main(void)
{
  
  u8g_t u8g;
  uint16_t offset;
  
  u8g_Init(&u8g, &u8g_dev_sdl_1bit);
  u8g_FirstPage(&u8g);


  for( offset = 0; offset < 4; offset++ )
  {
    u8g_FirstPage(&u8g);
    do
    {
      //u8g_SetFont(&u8g, u8g_font_unifont);
      //u8g_SetFont(&u8g, u8g_font_osb18r);
      
      u8g_DrawTriangle(&u8g, 14,7, 45,30, 10,40);

      u8g_DrawTriangle(&u8g, 14+offset,7-offset, 45+offset,30-offset, 57+offset,10-offset);

      u8g_DrawTriangle(&u8g, 57+offset*2,10, 45+offset*2,30, 86+offset*2,53);

      u8g_DrawTriangle(&u8g, 10+offset,40+offset, 45+offset,30+offset, 86+offset,53+offset);
      
    } while( u8g_NextPage(&u8g) );

  while( u8g_sdl_get_key() < 0 )
    ;
    
  }

  
#ifdef CIRCLE
  
  do
  {
    //u8g_SetFont(&u8g, u8g_font_unifont);
    //u8g_SetFont(&u8g, u8g_font_osb18r);
    
    for( rad = 2+3*2; rad < 30; rad += 3 )
    {
      u8g_DrawCircle(&u8g, 0, 35, rad, U8G_DRAW_UPPER_RIGHT);
      u8g_DrawCircle(&u8g, 0, 35+35, rad, U8G_DRAW_UPPER_RIGHT);
      
      u8g_DrawCircle(&u8g, 0+31, 5, rad, U8G_DRAW_LOWER_RIGHT);
      u8g_DrawCircle(&u8g, 0+31, 5+35, rad, U8G_DRAW_LOWER_RIGHT);

      u8g_DrawCircle(&u8g, 30+31*2, 5, rad, U8G_DRAW_LOWER_LEFT);
      u8g_DrawCircle(&u8g, 30+31*2, 5+35, rad, U8G_DRAW_LOWER_LEFT);

      u8g_DrawCircle(&u8g, 0+31*4, 35, rad, U8G_DRAW_UPPER_LEFT);
      u8g_DrawCircle(&u8g, 0+31*4, 35+35, rad, U8G_DRAW_UPPER_LEFT);
      
    }
  } while( u8g_NextPage(&u8g) );

  while( u8g_sdl_get_key() < 0 )
    ;


  for( rad = 2+3*2; rad < 30; rad += 3 )
  {
    u8g_FirstPage(&u8g);
    do
    {
      //u8g_SetFont(&u8g, u8g_font_unifont);
      //u8g_SetFont(&u8g, u8g_font_osb18r);
      
      u8g_DrawCircle(&u8g, 0, 35, rad, U8G_DRAW_UPPER_RIGHT);
      u8g_DrawDisc(&u8g, 0, 35+35, rad, U8G_DRAW_UPPER_RIGHT);
      
      u8g_DrawCircle(&u8g, 0+31, 5, rad, U8G_DRAW_LOWER_RIGHT);
      u8g_DrawDisc(&u8g, 0+31, 5+35, rad, U8G_DRAW_LOWER_RIGHT);

      u8g_DrawCircle(&u8g, 30+31*2, 5, rad, U8G_DRAW_LOWER_LEFT);
      u8g_DrawDisc(&u8g, 30+31*2, 5+35, rad, U8G_DRAW_LOWER_LEFT);

      u8g_DrawCircle(&u8g, 0+31*4, 35, rad, U8G_DRAW_UPPER_LEFT);
      u8g_DrawDisc(&u8g, 0+31*4, 35+35, rad, U8G_DRAW_UPPER_LEFT);
      
    } while( u8g_NextPage(&u8g) );

  while( u8g_sdl_get_key() < 0 )
    ;
    
  }
  
#endif

  return 0;
}

