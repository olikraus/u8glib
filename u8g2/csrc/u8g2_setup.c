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
  
  
  /*
  printf("x0=%d x1=%d y0=%d y1=%d\n", 
      u8g2->buf_x0, u8g2->buf_x1, u8g2->buf_y0, u8g2->buf_y1);
  */
}


/*============================================*/
extern void u8g2_draw_hv_line_4dir(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir);


void u8g2_draw_l90_r0(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
  u8g2_draw_hv_line_4dir(u8g2, x, y, len, dir);
}




/*============================================*/
const u8g2_cb_t u8g2_cb_r0 = { u8g2_update_dimension_r0, u8g2_draw_l90_r0 };
  
  
  
  
  
  