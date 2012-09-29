

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>

u8g_t u8g;

extern uint8_t u8g_dev_pbm_h_enable ;


void draw_clip_test(void) {
  u8g_uint_t i, j, k;
  char buf[3] = "AB";
  k = 0;
  u8g_SetColorIndex(&u8g, 1);
  u8g_SetFont(&u8g, u8g_font_6x10);
  
  u8g_DrawHLine(&u8g, 0-3, 5, 5);
  
  for( i = 0; i  < 6; i++ ) {
    for( j = 1; j  < 8; j++ ) {
      u8g_DrawHLine(&u8g, i-3, k, j);
      u8g_DrawHLine(&u8g, i-3+10, k, j);
      
      u8g_DrawVLine(&u8g, k+20, i-3, j);
      u8g_DrawVLine(&u8g, k+20, i-3+10, j);
      
      k++;
    }
  }
  u8g_DrawStr(&u8g, 0-3, 50, buf);
  u8g_DrawStr180(&u8g, 0+3, 50, buf);
  
  u8g_DrawStr(&u8g, u8g_GetWidth(&u8g)-3, 40, buf);
  u8g_DrawStr180(&u8g, u8g_GetWidth(&u8g)+3, 40, buf);

  u8g_DrawStr90(&u8g, u8g_GetWidth(&u8g)-10, 0-3, buf);
  u8g_DrawStr270(&u8g, u8g_GetWidth(&u8g)-10, 3, buf);

  u8g_DrawStr90(&u8g, u8g_GetWidth(&u8g)-20, u8g_GetHeight(&u8g)-3, buf);
  u8g_DrawStr270(&u8g, u8g_GetWidth(&u8g)-20, u8g_GetHeight(&u8g)+3, buf);  
  
  //u8g_DrawStr(&u8g, 0, 20, "Hello!");


/*  
  u8g_DrawBox(&u8g, 0, 0, 10, 10);
  u8g_DrawBox(&u8g, u8g_GetWidth(&u8g)-10-1, 0, 10, 10);
  u8g_DrawBox(&u8g, u8g_GetWidth(&u8g)-10-1, u8g_GetHeight(&u8g)-10-1, 10, 10);
  u8g_DrawBox(&u8g, 0, u8g_GetHeight(&u8g)-10-1, 10, 10);
*/  
}


int main(void)
{
  int i;
  u8g_Init(&u8g, &u8g_dev_pbm_8h1);
  
  //u8g_SetRot90(&u8g);

  
  for( i = 0; i < 10000; i++ )
  //for( i = 0; i < 1; i++ )
  {
    u8g_FirstPage(&u8g);
    do
    {
      draw_clip_test();
    }while( u8g_NextPage(&u8g) );
    
    u8g_dev_pbm_h_enable = 0;
  }
  return 0;
}



