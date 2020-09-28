#include <stdio.h>
#include <stdlib.h>

#include "u8g_linux.h"

u8g_t u8g;

#define MENU_ITEMS 4
char *menu_strings[MENU_ITEMS] = { "First Line", "Second Item", "3333333", "abcdefg" };


uint8_t menu_current = 0;
uint8_t menu_redraw_required = 0;


void draw_menu(void)
{
  uint8_t i, h;
  u8g_uint_t w, d;

  u8g_SetFont(&u8g, u8g_font_6x13);
  u8g_SetFontRefHeightText(&u8g);
  u8g_SetFontPosTop(&u8g);
  
  h = u8g_GetFontAscent(&u8g)-u8g_GetFontDescent(&u8g);
  w = u8g_GetWidth(&u8g);
  for( i = 0; i < MENU_ITEMS; i++ )
  {
    d = (w-u8g_GetStrWidth(&u8g, menu_strings[i]))/2;
    u8g_SetDefaultForegroundColor(&u8g);
    if ( i == menu_current )
    {
      u8g_DrawBox(&u8g, 0, i*h+1, w, h);
      u8g_SetDefaultBackgroundColor(&u8g);
    }
    u8g_DrawStr(&u8g, d, i*h, menu_strings[i]);
  }
}

void update_menu(void)
{
  switch ( u8g_linux_getch() )
  {
    case 'n':
      menu_current++;
      if ( menu_current >= MENU_ITEMS )
        menu_current = 0;
      menu_redraw_required = 1;
      break;
    case 'p':
      if ( menu_current == 0 )
        menu_current = MENU_ITEMS;
      menu_current--;
      menu_redraw_required = 1;
      break;
    case 'q':
      exit(0);
  }
}


int main(int argc, const char *argv[])
{
  u8g_linux_Init(&u8g, argc, argv);

  menu_redraw_required = 1;

  for(;;)
  {
    
    if (  menu_redraw_required != 0 )
    {
      u8g_FirstPage(&u8g);
      do 
      {
        draw_menu();
      } while( u8g_NextPage(&u8g) );
      menu_redraw_required = 0;
    }
    
    update_menu();    
  }
  
}

