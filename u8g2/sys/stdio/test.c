


#include "u8g2.h"

u8g2_t u8g2;

int main(void)
{
  uint8_t tile[8] = { 0x0f, 0x0f, 0x0f, 0x0f, 0xf0, 0xf0, 0xf0, 0xf0 };
  u8g2_InitStdio(&u8g2);  
  u8g2_display_DrawTile(&u8g2, 1, 1, 1, tile);

  return 0;
}