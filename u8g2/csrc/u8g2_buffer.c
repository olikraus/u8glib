/* 

  u8g2_buffer.c 
  
*/

#include "u8g2.h"
#include <string.h>

/*============================================*/
void u8g2_ClearBuffer(u8g2_t *u8g2)
{
  size_t cnt;
  cnt = u8g2_GetU8x8(u8g2)->display_info->tile_width;
  cnt *= u8g2->tile_buf_height;
  cnt *= 8;
  memset(u8g2->tile_buf_ptr, 0, cnt);
}

/*============================================*/

static void u8g2_send_tile_row(u8g2_t *u8g2, uint8_t tile_row)
{
  uint8_t *ptr;
  uint16_t offset;
  uint8_t w;
  
  w = u8g2_GetU8x8(u8g2)->display_info->tile_width;
  offset = tile_row;
  ptr = u8g2->tile_buf_ptr;
  offset *= w;
  offset *= 8;
  ptr += offset;
    
  u8x8_display_DrawTile(u8g2_GetU8x8(u8g2), 0, tile_row, w, ptr);
}

void u8g2_SendBuffer(u8g2_t *u8g2)
{
  uint8_t cnt = u8g2->tile_buf_height;
  uint8_t row = u8g2->tile_curr_row;
  do
  {
    u8g2_send_tile_row(u8g2, row);
    cnt--;
    row++;
  } while( cnt > 0 );
}

