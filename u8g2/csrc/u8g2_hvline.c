/*

  u8g2_hvline.c

*/

#include "u8g2.h"


void u8g2_draw_pixel(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y)
{
  uint8_t *ptr;
  uint8_t bit_pos, mask;
  uint16_t offset;
  ptr = u8g2->tile_buf_ptr;
  /* bytes are vertical, lsb on top (y=0), msb at bottom (y=7) */
  bit_pos = y;		/* overflow truncate is ok here... */
  bit_pos &= 7; 	/* ... because only the lowest 3 bits are needed */
  y &= ~7;		/* zero the lowest 3 bits, y is tile-row * 8 from  now on */
  offset = y;		/* y might be 8 or 16 bit, but we need 16 bit, so use a 16 bit variable */
  offset *= u8g2_GetU8x8(u8g2)->display_info->tile_width;
  ptr += offset;
  ptr += x;
  mask = 1;
  mask <<= bit_pos;
  if ( u8g2->draw_color != 0 )
  {
    *ptr |= mask;
  }
  else
  {
    mask ^= 255;
    *ptr &= mask;
  }  
}

/*
  x,y		Upper left position of the line
  len		length of the line in pixel, len must not be 0
  dir		0: horizontal line (left to right)
		1: vertical line (top to bottom)
*/
void u8g2_DrawHVLine(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
  if ( dir == 0 )
  {
    do
    {
      u8g2_draw_pixel(u8g2, x, y);
      x++;
      len--;
    } while( len != 0 );
  }
  else
  {
    do
    {
      u8g2_draw_pixel(u8g2, x, y);
      y++;
      len--;
    } while( len != 0 );
  }
}

/*
  Description:
    clip range from a (included) to b (excluded) agains c (included) to d (excluded)
  Assumptions:
    a <= b
    c <= d
*/
static uint8_t u8g2_clip_intersection(u8g2_uint_t *ap, u8g2_uint_t *bp, u8g2_uint_t c, u8g2_uint_t d)
{
  u8g2_uint_t a = *ap;
  u8g2_uint_t b = *bp;
  
  if ( a >= d )
    return 0;
  if ( b <= c )
    return 0;
  if ( a < c )
    *ap = c;
  if ( b > d )
    *bp = d;
  return 1;
}



/*
  x,y		Upper left position of the line
  len		length of the line in pixel, len must not be 0
  dir		0: horizontal line (left to right)
		1: vertical line (top to bottom)
*/
void u8g2_ClipAndDrawHVLine(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
  
}



