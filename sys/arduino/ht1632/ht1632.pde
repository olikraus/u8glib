
#include "U8glib.h"

void setup(void)
{
}

void loop(void)
{
  u8g_t u8g;
  
  u8g_Init(&u8g, &u8g_dev_ht1632_24x16);
  u8g_FirstPage(&u8g);
  u8g_SetColorIndex(&u8g, 1);
  do  {
    u8g_SetFont(&u8g, u8g_font_7x13);
    u8g_DrawStr(&u8g, 0, 14, "ABCgdef");
  }while( u8g_NextPage(&u8g) );
  delay(1000);
}
