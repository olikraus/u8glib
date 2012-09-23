/*

  u8g_dev_pbm.c
  
  write file u8g.pbm
  
*/

#include <stdio.h>
#include "u8g.h"


#if defined(U8G_16BIT)
#define WIDTH 1024
#define HEIGHT 768
#else
#define WIDTH 128
#define HEIGHT 64
#endif
#define PAGE_HEIGHT 8

/* 8v1 */
uint8_t u8g_dev_pbm_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);


static uint8_t u8g_pb_dev_pbm_buf[WIDTH];
static u8g_pb_t u8g_pb_dev_pbm = { {PAGE_HEIGHT, HEIGHT, 0, 0, 0},  WIDTH, u8g_pb_dev_pbm_buf };

u8g_dev_t u8g_dev_pbm = { u8g_dev_pbm_fn, &u8g_pb_dev_pbm };


uint8_t u8g_dev_pbm_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  static FILE *fp;
  u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
  
  switch(msg)
  {
    case U8G_DEV_MSG_PAGE_FIRST:
      u8g_pb_Clear(pb);
      u8g_page_First(&(pb->p));
      fp = fopen("u8g.pbm", "w");
      fprintf(fp, "P4\n%d %d\n", WIDTH, HEIGHT);
      return 1;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_uint_t i, j;
        uint8_t b;
        for( j = 0; j < 8; j++ )
        {
          b = 0;
          for( i = 0; i < WIDTH; i++ )
          {
            b<<= 1;
            if ( (((uint8_t *)(pb->buf))[i] & (1<<j)) != 0 )
              b |= 1;
            if ( i % 8 == 7 )
              fprintf(fp, "%c", b);
          }
          if ( i%8  != 0 )
              fprintf(fp, "%c", b);
        }
      }
      if ( u8g_page_Next(&(pb->p)) == 0 )
      {
        fclose(fp);
        return 0;
      }
      u8g_pb_Clear(pb);
      return 1;
  }
  return u8g_dev_pb8v1_base_fn(u8g, dev, msg, arg);
}


