/*

  u8g2_hvline.c

*/

#include "u8g2.h"
#include <assert.h>


void u8g2_draw_pixel(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y)
{
  uint8_t *ptr;
  uint8_t bit_pos, mask;
  uint16_t offset;
  
  assert(x >= u8g2->buf_x0);
  assert(x < u8g2->buf_x1);
  assert(y >= u8g2->buf_y0);
  assert(y < u8g2->buf_y1);

  
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
static void u8g2_draw_hv_line(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
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
    a <= b		(this is checked and handled correctly)
    c <= d		(this is not checked)
  will return 0 if there is no intersection and if a > b
*/
static uint8_t u8g2_clip_intersection(u8g2_uint_t *ap, u8g2_uint_t *bp, u8g2_uint_t c, u8g2_uint_t d)
{
  u8g2_uint_t a = *ap;
  u8g2_uint_t b = *bp;
  
  /* handle the a>b case correctly. If code and time is critical, this could */
  /* be removed completly (be aware about memory curruption for wrong */
  /* arguments) or return 0 for a>b (will lead to skipped lines for wrong */
  /* arguments) */  
  
  /* removing the following if clause completly may lead to memory corruption of a>b */
  if ( a > b )
  {    
    /* replacing this if with a simple "return 0;" will not handle the case with negative a */    
    if ( a < d )
    {
      b = d;
      b--;
      *bp = b;
    }
    else
    {
      a = 0;
      *ap = a;
    }
  }
  
  /* from now on, the asumption a <= b is ok */
  
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
void u8g2_DrawHVLine(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
  u8g2_uint_t a;
  if ( dir == 0 )
  {
    if ( y < u8g2->buf_y0 )
      return;
    if ( y >= u8g2->buf_y1 )
      return;
    a = x;
    a += len;
    if ( u8g2_clip_intersection(&x, &a, u8g2->buf_x0, u8g2->buf_x1) == 0 )
      return;
    len = a;
    len -= x;
  }
  else
  {
    if ( x < u8g2->buf_x0 )
      return;
    if ( x >= u8g2->buf_x1 )
      return;
    a = y;
    a += len;
    if ( u8g2_clip_intersection(&y, &a, u8g2->buf_y0, u8g2->buf_y1) == 0 )
      return;
    len = a;
    len -= y;
  }
  u8g2_draw_hv_line(u8g2, x, y, len, dir);
}



