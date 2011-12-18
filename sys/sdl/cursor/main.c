

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>

u8g_uint_t cursor_x = 10;
u8g_uint_t cursor_y = 10;
u8g_uint_t uiIncrement = 2;

// calculate new output values
int uiStep(u8g_t *u8g) 
{
  int key = u8g_sdl_get_key();
  switch( key )
  {
    case ' ':
      return 1;
    case 273:
    case 'x':
      if ( cursor_y >= 0 +  uiIncrement )
	cursor_y -= uiIncrement;
      return 1;
    case 274:
    case 's':
      if ( cursor_y <= u8g_GetHeight(u8g) -  uiIncrement )
	cursor_y += uiIncrement;
      return 1;
    case 276:
    case 'c':
      if ( cursor_x >= 0 +  uiIncrement )
	cursor_x -= uiIncrement;
      return 1;
    case 275:
    case 'v':
      if ( cursor_x <= u8g_GetWidth(u8g) -  uiIncrement )
	cursor_x += uiIncrement;
      return 1;
    case 'q':
      exit(0);
  }
  return 0;
}


int main(void)
{
  u8g_uint_t w,h;
  u8g_t u8g;
  
  u8g_Init(&u8g, &u8g_dev_sdl_1bit);
  u8g_SetCursorFont(&u8g, u8g_font_cursor);
  u8g_SetCursorStyle(&u8g, 34);
  u8g_SetCursorColor(&u8g, 1, 0);
  u8g_EnableCursor(&u8g);
  
  for(;;)
  {
    
    u8g_FirstPage(&u8g);
    do
    {
      u8g_SetColorIndex(&u8g, 1);
      u8g_SetFont(&u8g, u8g_font_10x20);
      //u8g_SetFont(&u8g, u8g_font_fur17);
      w = u8g_GetFontBBXWidth(&u8g);
      h = u8g_GetFontBBXHeight(&u8g);
      //u8g_DrawStr(&u8g, 0, 2*h, 0, "ABCgdef");
      u8g_DrawStrDir(&u8g, 0, 5, 0, "g");
      u8g_DrawStrDir(&u8g, 10, 7, 0, "g");
      u8g_DrawStrDir(&u8g, 20, 9, 0, "g");
      u8g_DrawStrDir(&u8g, 20, 9, 0, "ga");

      //u8g_DrawStr(&u8g, 40, 9, 0, "g");
      u8g_DrawStr(&u8g, 70+3, 25, "gabc");
      u8g_DrawStr90(&u8g, 70, 25+3, "gabc");
      u8g_DrawStr180(&u8g, 70-3, 25, "gabc");
      u8g_DrawStr270(&u8g, 70, 25-3, "gabc");

      
      //u8g_DrawFrame(&u8g, 2, 2, 9, 3);
      //u8g_DrawFrame(&u8g, 0, 0, 13, 7);
      //u8g_DrawHLine( &u8g, 0, 16, 50 );   
      
      u8g_SetColorIndex(&u8g, 1);
      
      u8g_DrawHLine( &u8g, 0, 3, 127 );   
      
      u8g_SetColorIndex(&u8g, 0);
      u8g_DrawHLine( &u8g, 0, 4, 127 );   

    }while( u8g_NextPage(&u8g) );

    while( uiStep(&u8g) == 0 )
      ;
    printf("%d %d\n", cursor_x, cursor_y);
    u8g_SetCursorPos(&u8g, cursor_x, cursor_y);
  }
  
  
  return 0;
}



