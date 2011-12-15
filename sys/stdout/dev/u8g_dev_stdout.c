/*

  u8g_dev_stdout.c
  
*/

#include <stdio.h>
#include "u8g.h"


#define WIDTH 70
#define HEIGHT 30
#define PAGE_HEIGHT 8

uint8_t u8g_dev_stdout_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);

U8G_PB_DEV(u8g_dev_stdout, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_stdout_fn, NULL);

uint8_t u8g_dev_stdout_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  
  switch(msg)
  {
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        uint8_t i, j;
        uint8_t page_height;
        page_height = pb->p.page_y1;
        page_height -= pb->p.page_y0;
        page_height++;
        for( j = 0; j < page_height; j++ )
        {
          printf("%02d ", j);
          for( i = 0; i < WIDTH; i++ )
          {
            if ( (((uint8_t *)(pb->buf))[i] & (1<<j)) != 0 )
              printf("#");
            else
              printf(".");
          }
          printf("\n");
        }
      }
      break;    /* continue to base fn */
  }
  return u8g_dev_pb8v1_base_fn(u8g, dev, msg, arg);
}

