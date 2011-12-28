

#include "u8glib.h"
#include <stdlib.h>
#include <stdio.h>


int u8g_sdl_get_key(void);

U8GLIB u8g(&u8g_dev_sdl_1bit);


int main(void)
{  
  u8g.firstPage();
  
  do
  {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(0, 20, "Hello World!");
  } while( u8g.nextPage() );

  while( u8g_sdl_get_key() < 0 )
    ;
}

