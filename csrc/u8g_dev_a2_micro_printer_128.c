/*

  u8g_dev_a2_micro_printer_128.c

  Use DC2 bitmap command of the A2 Micro panel termal printer
  Height is 128 pixel

  Universal 8bit Graphics Library
  
  Copyright (c) 2011, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  
  
*/

#include "u8g.h"

#define WIDTH 240
#define HEIGHT 128
#define PAGE_HEIGHT 8


uint8_t u8g_dev_a2_micro_printer_128_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_InitCom(u8g, dev, U8G_SPI_CLK_CYCLE_NONE);
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        uint8_t y, i, j;
        uint8_t *ptr;
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        
        y = pb->p.page_y0;
        ptr = pb->buf;
	u8g_WriteByte(u8g, dev, 18);      /* DC2 */
	u8g_WriteByte(u8g, dev, 86 );      /* V  */
	u8g_WriteByte(u8g, dev,  ((uint16_t)PAGE_HEIGHT*(uint16_t)48)&255 );      /* low byte */
	u8g_WriteByte(u8g, dev,  ((uint16_t)PAGE_HEIGHT*(uint16_t)48)>>8 );      /* hight byte */
	
        for( i = 0; i < 8; i ++ )
        {
	  for( j = 0; j < WIDTH/8; j++ )
	  {
	    u8g_WriteByte(u8g, dev, *ptr);
	    ptr++;
	  }
	  for( ; j < 48; j++ )
	  {
	    u8g_WriteByte(u8g, dev, 0);
	  }
          y++;
        }
      }
      break;
  }
  return u8g_dev_pb8h1_base_fn(u8g, dev, msg, arg);
}


U8G_PB_DEV(u8g_dev_a2_micro_printer_128, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_a2_micro_printer_128_fn, U8G_COM_NONE);
