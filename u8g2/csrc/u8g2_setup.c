/*

  u8g2_setup.c
  
*/
#include "u8g2.h"


/*============================================*/
/* 
  update dimension: 
  calculate the following variables:
    u8g2_uint_t buf_x0;	left corner of the buffer
    u8g2_uint_t buf_x1;	right corner of the buffer (excluded)
    u8g2_uint_t buf_y0;
    u8g2_uint_t buf_y1;
*/

void u8g2_update_dimension_r0(u8g2_t *u8g2)
{
  u8g2_uint_t h, w;
  h = u8g2->tile_buf_height;
  h *= 8;
  w = u8g2_GetU8x8(u8g2)->display_info->tile_width;
  w *= 8;
  u8g2->buf_x0 = 0;
  u8g2->buf_y0 = u8g2->tile_curr_row;
  u8g2->buf_y0 *= 8;
  
  u8g2->buf_x1 = u8g2->buf_x0;
  u8g2->buf_x1 += w;
  u8g2->buf_y1 = u8g2->buf_y0;
  u8g2->buf_y1 += h;
}

