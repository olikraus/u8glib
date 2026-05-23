#include "u8g_linux.h"

int main(int argc, const char *argv[])
{
  u8g_t u8g;

  u8g_linux_Init(&u8g, argc, argv);
  u8g_FirstPage(&u8g);
  
  do
  {
    u8g_SetFont(&u8g, u8g_font_unifont);
    u8g_DrawStr(&u8g, 0, 20, argc > 2 ? argv[2] : "Hello World!");
  } while( u8g_NextPage(&u8g) );

  return 0;
}

