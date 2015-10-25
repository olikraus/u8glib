/*

  u8g2_hvline.c


  Calltree
    void u8g2_DrawHVLine(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
    u8g2->cb->draw_l90
    void u8g2_draw_hv_line_4dir(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
    void u8g2_draw_hv_line_2dir(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
    void u8g2_unsafe_draw_hv_line(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
    void u8g2_draw_pixel(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y)

*/

#include "u8g2.h"
#include <assert.h>



/*
  x,y position within the buffer
*/
void u8g2_draw_pixel(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y)
{
  uint8_t *ptr;
  uint8_t bit_pos, mask;
  uint16_t offset;
  
  //assert(x >= u8g2->buf_x0);
  assert(x < u8g2_GetU8x8(u8g2)->display_info->tile_width*8);
  //assert(y >= u8g2->buf_y0);
  assert(y < u8g2_GetU8x8(u8g2)->display_info->tile_height*8);
  
  // y -= u8g2->tile_curr_row*8;

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
  x,y		Upper left position of the line within the local buffer (not the display!)
  len		length of the line in pixel, len must not be 0
  dir		0: horizontal line (left to right)
		1: vertical line (top to bottom)
  asumption: 
    all clipping done
*/
static void u8g2_unsafe_draw_hv_line(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
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

  optimized clipping: c is set to 0
*/
//static uint8_t u8g2_clip_intersection(u8g2_uint_t *ap, u8g2_uint_t *bp, u8g2_uint_t c, u8g2_uint_t d)
static uint8_t u8g2_clip_intersection(u8g2_uint_t *ap, u8g2_uint_t *bp, u8g2_uint_t d)
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
  if ( b <= 0 )		// was b <= c, could be replaced with b == 0
    return 0;
  //if ( a < c )		// never true with c == 0
  //  *ap = c;
  if ( b > d )
    *bp = d;
    
  return 1;
}



/*
  x,y		Upper left position of the line
  len		length of the line in pixel, len must not be 0
  dir		0: horizontal line (left to right)
		1: vertical line (top to bottom)
  This function first adjusts the y position to the local buffer. Then it
  will clip the line and call u8g2_unsafe_draw_hv_line()
  
*/
static void u8g2_draw_hv_line_2dir(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
  u8g2_uint_t a;
  register u8g2_uint_t w, h;

  y -= u8g2->tile_curr_row*8;
  
  h = u8g2->pixel_buf_height;
  w = u8g2->pixel_buf_width;
  
  if ( dir == 0 )
  {
    if ( y >= h )
      return;
    a = x;
    a += len;
    if ( u8g2_clip_intersection(&x, &a, w) == 0 )
      return;
    len = a;
    len -= x;
  }
  else
  {
    if ( x >= w )
      return;
    a = y;
    a += len;
    if ( u8g2_clip_intersection(&y, &a, h) == 0 )
      return;
    len = a;
    len -= y;
  }
  
  u8g2_unsafe_draw_hv_line(u8g2, x, y, len, dir);
}

/*
  x,y		Upper left position of the line
  len		length of the line in pixel, len must not be 0
  dir		0: horizontal line (left to right)
		1: vertical line (top to bottom)
		2: horizontal line (right to left)
		3: vertical line (bottom to top)

  This function will remove directions 2 and 3. Instead 0 and 1 are used.

*/
void u8g2_draw_hv_line_4dir(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
#ifdef U8G2_WITH_HVLINE_COUNT
  u8g2->hv_cnt++;
#endif /* U8G2_WITH_HVLINE_COUNT */   
  
  if ( dir == 2 )
  {
    x -= len;
    x++;
  }
  else if ( dir == 3 )
  {
    y -= len;
    y++;
  }
  dir &= 1;  
  u8g2_draw_hv_line_2dir(u8g2, x, y, len, dir);
}

/*
  This is the toplevel function for the hv line draw procedures.
  This function should be called by the user.
*/
void u8g2_DrawHVLine(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t len, uint8_t dir)
{
  /* Make a call the the callback function. The callback may rotate the hv line */
  /* after rotation this will call u8g2_draw_hv_line_4dir() */
  if ( len != 0 )
    u8g2->cb->draw_l90(u8g2, x, y, len, dir);
}

