/*

  u8g_dev_ht1632_26x16.c
  
  1-Bit (BW) Driver for HT1632 controller

  Universal 8bit Graphics Library
  
  Copyright (c) 2013, olikraus@gmail.com
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

#define WIDTH 26
#define HEIGHT 16
#define PAGE_HEIGHT 8


void ht1632_init(void)
{
  /* init display once after startup */
}

/*
  page: 0=data contain lines 0..7, 1=data contain lines 8..16
  cnt: number of bytes in the buffer
  data: pointer to a buffer with "cnt" bytes.
*/
void ht1632_transfer_data(uint8_t page, uint8_t cnt, uint8_t *data)
{
  /* send data to the ht1632 */
}


uint8_t u8g_dev_ht1632_26x16_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        
	/* current page: pb->p.page */
	/* ptr to the buffer: pb->buf */
	ht1632_transfer_data(pb->p.page, WIDTH, pb->buf);
      }
      break;
    case U8G_DEV_MSG_CONTRAST:
      return 1;
  }
  return u8g_dev_pb8v1_base_fn(u8g, dev, msg, arg);
}

U8G_PB_DEV(u8g_dev_ht1632_26x16 , WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_ht1632_26x16_fn, u8g_com_null_fn);

