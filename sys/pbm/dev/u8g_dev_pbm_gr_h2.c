/*

  u8g_dev_pbm_h2.c
  
  write file u8g.pbm
  
  for 8 and 16 bit mode, this is a 128x64 monochrome picture
  simulates grayscale
  
*/

#include <stdio.h>
#include "u8g.h"


#define WIDTH 128
#define HEIGHT 64
#define PAGE_HEIGHT 4


extern void *u8g_buf_lower_limit;
extern void *u8g_buf_upper_limit;


uint8_t u8g_dev_pbm_h2_enable = 1;

/* 8h2 */
uint8_t u8g_dev_pbm_8h2_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);


static uint8_t u8g_pb_dev_pbm_buf[WIDTH];
static u8g_pb_t u8g_pb_dev_pbm = { {PAGE_HEIGHT, HEIGHT, 0, 0, 0},  WIDTH, u8g_pb_dev_pbm_buf };



u8g_dev_t u8g_dev_pbm_8h2 = { u8g_dev_pbm_8h2_fn, &u8g_pb_dev_pbm };




uint8_t u8g_dev_pbm_8h2_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  static FILE *fp;
  u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
  
  switch(msg)
  {
    
    case U8G_DEV_MSG_PAGE_FIRST:
#ifdef __unix__      
      u8g_buf_lower_limit = u8g_pb_dev_pbm_buf;
      u8g_buf_upper_limit = u8g_pb_dev_pbm_buf + WIDTH;
#endif

      u8g_pb_Clear(pb);
      u8g_page_First(&(pb->p));
    
      if ( u8g_dev_pbm_h2_enable != 0 )
      {
	fp = fopen("u8g.pbm", "w");
	fprintf(fp, "P4\n%d %d\n", WIDTH, HEIGHT);
      }
      return 1;
    case U8G_DEV_MSG_PAGE_NEXT:

      if ( u8g_dev_pbm_h2_enable != 0 )
      {
        u8g_uint_t i, j, k;
        uint8_t b, b1,b2;
        for( j = 0; j < PAGE_HEIGHT; j++ )
        {
          b = 0;
	  i = 0;
	  for(;;)
          {
	    b1 = 0;
	    b = ((uint8_t *)(pb->buf))[i+j*(WIDTH/4)];
	    for( k = 0; k < 4; k ++ )
	    {
	      b1 >>= 1;
	      if ( (b&0xc0) != 0 )
		b1 |= 8;
	      b <<= 2;
	    }
	    i++;
	    b2 = 0;
	    b = ((uint8_t *)(pb->buf))[i+j*(WIDTH/4)];
	    for( k = 0; k < 4; k ++ )
	    {
	      b2 >>= 1;
	      if ( (b&0xc0) != 0 )
		b2 |= 8;
	      b <<= 2;
	    }
	    i++;
	    fprintf(fp, "%c", b1*16+b2);
	    if ( i >= WIDTH/4 )
	      break;
	  }
        }
      }
      
      
      if ( u8g_page_Next(&(pb->p)) == 0 )
      {
	if ( u8g_dev_pbm_h2_enable != 0 )
	  fclose(fp);
        return 0;
      }
      u8g_pb_Clear(pb);
      return 1;
  }
  return u8g_dev_pb8h2_base_fn(u8g, dev, msg, arg);
}
