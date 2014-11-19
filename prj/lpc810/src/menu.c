
#include <stdint.h>
#include "chip.h"
#include "sys.h"
#include "oled.h"
#include "clk.h"
#include "key.h"


struct menu_struct
{
  unsigned current_dialog;
  unsigned entry_type;
  unsigned entry_arg;
  const char *entry_label;
  
  unsigned total;	/* number of menu entries */
  unsigned curr;	/* current menu entry (starts at 0) */
  
  const char *str[4];
  unsigned num[4];
};
typedef struct menu_struct menu_t;

menu_t menu_o;

/*=============================================================*/
const char menu_top[] = "\xf1\x02ZEIT\xf1\x02TAGE\xf1\x02WOCHE";
const char menu_hms[] = "\xf3\x18STUNDE\xf3\x3cMIN\xf3\x3cSEK\xf1\x01ZURUECK";

const char * const menu_dialog_list[] = 
{
  menu_top,
  menu_hms
};


/*=============================================================*/
/*
  1st char: Type
    0		terminate
    \xf1	jmp
    \xf2	bool
    \xf3	num
    \xf4	read only label
    \xf5	read only variable string
  2nd char: Value arg
  3rd char: string
*/

unsigned menu_get_entry_cnt(const char *me)
{
  unsigned cnt = 0;
  while( *me != '\0' )
  {
    if ( *me > 0x0f0 )
      cnt++;
    me++;
  }
  return cnt;
}

const char *menu_get_entry(const char *me, unsigned idx)
{
  while( idx > 0 )
  {
    do
    {
      me++;      
    } while( *me < 0xf0 );
    idx--;
  }
  return me;
}

void menu_prepare_entry(unsigned entry_idx)
{
  const char *s;
  
  if ( entry_idx >= menu_o.total )
    entry_idx = 0;
  
  menu_o.curr = entry_idx;
  s = menu_get_entry(menu_dialog_list[menu_o.current_dialog], menu_o.curr);
  menu_o.entry_type = *s++;
  menu_o.entry_arg = *s++;
  menu_o.entry_label  = s;  
}


void menu_prepare_dialog(unsigned idx)
{
  
  menu_o.current_dialog = idx;
  
  menu_o.total  = menu_get_entry_cnt(menu_dialog_list[menu_o.current_dialog]);
  menu_prepare_entry(0);
 }

void menu_init(unsigned total)
{
  menu_o.total = total;
  menu_prepare_dialog(0);
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
      menu_prepare_entry(menu_o.curr+1);
      ret = 1;
    }
    else if ( code == KEY_SELECT )
    {
      if ( menu_o.entry_type == 0xf1 )
      {
	menu_prepare_dialog(menu_o.entry_arg-1);
      }
      else
      {
	  menu_o.num[menu_o.curr]++;
	  if ( menu_o.num[menu_o.curr] >= menu_o.entry_arg )
	    menu_o.num[menu_o.curr] = 0;
      }
      ret = 1;
    }
  }
  return ret;
}

void draw_hm(oled_t *oled, clk_t *clk)
{
  unsigned x, y, d;
  y = 47;
  x = 0;
  d = 25;


  oled_set_font(&oled_o, logisoso46);
  
  x += oled_draw_num(oled,x,y,d,0,clk->cnt[2]);
  oled_draw_glyph(oled, x, y, ':');
  x += d/2;
  x += oled_draw_num(oled,x,y,d,1,clk->cnt[1]);

  oled_set_font(&oled_o, helvR14small);
  oled_draw_num(oled,100,64,10,1,clk->cnt[0]);
  
}

void menu_draw(void)
{
  unsigned y, i;
  
  if ( menu_o.current_dialog == 15 )
  {
	draw_hm(&oled_o, &clk_current_time);
  }
  else
  {
    const char *m = menu_dialog_list[menu_o.current_dialog];
    
    oled_set_font(&oled_o, helvR14small);
    
    y = 14;
    for( i = 0; i < menu_o.total; i++ )
    {
	if ( menu_o.curr == i )
	{
	  oled_draw_string(&oled_o, 0, y, ":");
	}
	oled_draw_string(&oled_o, 10, y, m+2); 
	if ( *m == 0xf3 || *m == 0xf2 )
	{
	  oled_draw_num(&oled_o, 100, y, 10, 1, menu_o.num[i]);    
	}
	
	y += 16;
	m = menu_get_entry(m, 1);
    }
  }
}

void menu(void)
{
  menu_init(3);
  
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
