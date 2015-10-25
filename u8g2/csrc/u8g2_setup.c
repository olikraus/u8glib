/*

  u8g2_setup.c
  
*/

#include "u8g2.h"
#include <string.h>



/*============================================*/
/* 
  update dimension: 
  calculate the following variables:
    u8g2_uint_t buf_x0;	left corner of the buffer
    u8g2_uint_t buf_x1;	right corner of the buffer (excluded)
    u8g2_uint_t buf_y0;
    u8g2_uint_t buf_y1;
*/

static void u8g2_update_dimension_common(u8g2_t *u8g2)
{
  u8g2_uint_t h, w;
  
  h = u8g2->tile_buf_height;
  
  /* handle the case, where the buffer is larger than the (remaining) part of the display */
  if ( h + u8g2->tile_curr_row > u8g2_GetU8x8(u8g2)->display_info->tile_height )
    h = u8g2_GetU8x8(u8g2)->display_info->tile_height - u8g2->tile_curr_row;
  
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

  u8g2->width = w;
  u8g2->height = u8g2_GetU8x8(u8g2)->display_info->tile_height * 8;  
}

void u8g2_update_dimension_r0(u8g2_t *u8g2)
{
  u8g2_update_dimension_common(u8g2);

  u8g2->user_x0 = u8g2->buf_x0;
  u8g2->user_x1 = u8g2->buf_x1;
  
  u8g2->user_y0 = u8g2->buf_y0;
  u8g2->user_y1 = u8g2->buf_y1;
  
  printf("x0=%d x1=%d y0=%d y1=%d\n", 
      u8g2->user_x0, u8g2->user_x1, u8g2->user_y0, u8g2->user_y1);
}

void u8g2_update_dimension_r1(u8g2_t *u8g2)
{
  u8g2_uint_t t;
  u8g2_update_dimension_common(u8g2);
  
  t = u8g2->width;
  u8g2->width = u8g2->height;
  u8g2->height = t;

  u8g2->user_x0 = u8g2->buf_y0;
  u8g2->user_x1 = u8g2->buf_y1;
  
  u8g2->user_y0 = u8g2->buf_x0;
  u8g2->user_y1 = u8g2->buf_x1;
  
  printf("x0=%d x1=%d y0=%d y1=%d\n", 
      u8g2->user_x0, u8g2->user_x1, u8g2->user_y0, u8g2->user_y1);
}

void u8g2_update_dimension_r2(u8g2_t *u8g2)
{
  u8g2_update_dimension_common(u8g2);

  u8g2->user_x0 = u8g2->buf_x0;
  u8g2->user_x1 = u8g2->buf_x1;
  
  u8g2->user_y0 = u8g2->height - u8g2->buf_y1;
  u8g2->user_y1 = u8g2->height - u8g2->buf_y0;
  
  printf("x0=%d x1=%d y0=%d y1=%d\n", 
      u8g2->user_x0, u8g2->user_x1, u8g2->user_y0, u8g2->user_y1);
}


/*============================================*/
extern void u8g2_draw_hv_line_4dir(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir);


void u8g2_draw_l90_r0(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
  u8g2_draw_hv_line_4dir(u8g2, x, y, len, dir);
}

void u8g2_draw_l90_r1(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
  u8g2_uint_t xx, yy;
  
  yy = x;
  
  xx = u8g2->height;
  xx -= y;
  xx--;
  
  dir ++;
  dir &= 3;
  u8g2_draw_hv_line_4dir(u8g2, xx, yy, len, dir);
}

void u8g2_draw_l90_r2(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
  u8g2_uint_t xx, yy;

  yy = u8g2->height;
  yy -= y;
  yy--;
  
  xx = u8g2->width;
  xx -= x;
  xx--;
  
  dir +=2;
  dir &= 3;
  u8g2_draw_hv_line_4dir(u8g2, xx, yy, len, dir);
}



/*============================================*/
const u8g2_cb_t u8g2_cb_r0 = { u8g2_update_dimension_r0, u8g2_draw_l90_r0 };
const u8g2_cb_t u8g2_cb_r1 = { u8g2_update_dimension_r1, u8g2_draw_l90_r1 };
const u8g2_cb_t u8g2_cb_r2 = { u8g2_update_dimension_r2, u8g2_draw_l90_r2 };
  
  
  
  
  
  