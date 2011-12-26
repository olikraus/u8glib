

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>


int u8g_sdl_get_key(void);



int main(void)
{
  
  u8g_t u8g;
  u8g_Init(&u8g, &u8g_dev_sdl_1bit);
  u8g_FirstPage(&u8g);
  
  do
  {
    u8g_SetFont(&u8g, u8g_font_unifont);
    //u8g_SetFont(&u8g, u8g_font_osb18r);
    
    u8g_DrawStr(&u8g, 0, 20, "Hello World!");
  } while( u8g_NextPage(&u8g) );

  while( u8g_sdl_get_key() < 0 )
    ;
}

