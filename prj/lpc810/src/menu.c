
#include <stdint.h>
#include "chip.h"
#include "sys.h"
#include "oled.h"
#include "clk.h"
#include "key.h"

const char * const menu_str[] = 
{
  "STUNDE:",
  "MIN:",
  "SEK:",
};


struct menu_struct
{
  unsigned total;
  unsigned curr;
  
  const char *str[4];
  unsigned num[4];
};
typedef struct menu_struct menu_t;

menu_t menu_o;

void menu_init(unsigned total)
{
  menu_o.total = total;
  menu_o.curr = 0;
}

unsigned menu_handle_key(void)
{
  unsigned ret = 0;
  unsigned code;
  for(;;)
  {
    code = key_get_from_queue();
    if ( code == 0 )
    {
      break;
    }
    else if ( code == KEY_NEXT )
    {
      menu_o.curr++;
      if ( menu_o.curr >= menu_o.total )
	menu_o.curr = 0;
      ret = 1;
    }
    else if ( code == KEY_SELECT )
    {
      menu_o.num[menu_o.curr]++;
      ret = 1;
    }
  }
  return ret;
}

void menu_draw(void)
{
  unsigned y, i;
  oled_set_font(&oled_o, helvR14small);
  y = 14;
  for( i = 0; i < menu_o.total; i++ )
  {
      if ( menu_o.curr == i )
      {
	oled_draw_string(&oled_o, 0, y, ":");
      }
      oled_draw_string(&oled_o, 10, y, menu_o.str[i]);    
      oled_draw_num(&oled_o, 100, y, 10, 1, menu_o.num[i]);    
      y += 16;
  }
}

void menu(void)
{
  menu_init(3);
  
  menu_o.str[0] = menu_str[0];
  menu_o.str[1] = menu_str[1];
  menu_o.str[2] = menu_str[2];
  
  key_add_to_queue(KEY_NEXT);
  
  for(;;)
  {
    if ( menu_handle_key() != 0 )
    {
      oled_start_page(&oled_o);
      do
      {
	menu_draw();
      }
      while( oled_next_page(&oled_o) );      
    }
  }
  
}
