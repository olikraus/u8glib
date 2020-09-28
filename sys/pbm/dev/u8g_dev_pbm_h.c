/*

  u8g_dev_pbm_h.c
  
  write file u8g.pbm
  
  for 8 and 16 bit mode, this is a 128x64 monochrome picture
  
*/

#include <stdio.h>
#include "u8g.h"


// These are default sizes. They can be changed without changing this
// file by modifying the corresponding parts of the ug8_dev_t struct.
// Changing the height and lowering the width is always possible. To
// increase the width, the page buffer (u8g_pb_dev_pbm below) should
// also be replaced by something bigger. The page height cannot be
// changed.
#define WIDTH 128
#define HEIGHT 64
#define PAGE_HEIGHT 8


extern void *u8g_buf_lower_limit;
extern void *u8g_buf_upper_limit;


uint8_t u8g_dev_pbm_h_enable = 1;

/* 8h1 */
uint8_t u8g_dev_pbm_8h1_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);


static uint8_t u8g_pb_dev_pbm_buf[WIDTH];
static u8g_pb_t u8g_pb_dev_pbm = { {PAGE_HEIGHT, HEIGHT, 0, 0, 0},  WIDTH, u8g_pb_dev_pbm_buf };



u8g_dev_t u8g_dev_pbm_8h1 = { u8g_dev_pbm_8h1_fn, &u8g_pb_dev_pbm };




uint8_t u8g_dev_pbm_8h1_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  static FILE *fp;
  u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
  u8g_uint_t width = ((u8g_pb_t*)dev->dev_mem)->width;
  u8g_uint_t height = ((u8g_pb_t*)dev->dev_mem)->p.total_height;
  
  switch(msg)
  {
    
    case U8G_DEV_MSG_PAGE_FIRST:
#ifdef __unix__      
      u8g_buf_lower_limit = u8g_pb_dev_pbm_buf;
      u8g_buf_upper_limit = u8g_pb_dev_pbm_buf + width;
#endif

      u8g_pb_Clear(pb);
      u8g_page_First(&(pb->p));
    
      if ( u8g_dev_pbm_h_enable != 0 )
      {
	fp = fopen("u8g.pbm", "w");
	fprintf(fp, "P4\n%d %d\n", width, height);
      }
      return 1;
    case U8G_DEV_MSG_PAGE_NEXT:

      if ( u8g_dev_pbm_h_enable != 0 )
      {
        u8g_uint_t i, j;
        uint8_t b;
        for( j = 0; j < 8; j++ )
        {
          b = 0;
          for( i = 0; i < width/8; i++ )
          {
	    b = ((uint8_t *)(pb->buf))[i+j*(width/8)];
	    fprintf(fp, "%c", b);
	  }
        }
      }
      
      
      if ( u8g_page_Next(&(pb->p)) == 0 )
      {
	if ( u8g_dev_pbm_h_enable != 0 )
	  fclose(fp);
        return 0;
      }
      u8g_pb_Clear(pb);
      return 1;
  }
  return u8g_dev_pb8h1_base_fn(u8g, dev, msg, arg);
}
