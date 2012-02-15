/*

  u8g_pb8h8.c
  
  8 bits per pixel, horizontal
  
  Universal 8bit Graphics Library
  
  Copyright (c) 2012, olikraus@gmail.com
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


struct _u8g_pb_t
{
  u8g_page_t p;
  u8g_uint_t width;
  void *buf;
};
typedef struct _u8g_pb_t u8g_pb_t;


uint8_t u8g_index_color_8h8_buf[WIDTH*PAGE_HEIGHT] U8G_NOCOMMON ; 
u8g_pb_t u8g_index_color_8h8_pb = { {PAGE_HEIGHT, HEIGHT, 0, 0, 0},  WIDTH, u8g_index_color_8h8_buff}; 
u8g_dev_t name = { dev_fn, &u8g_index_color_8h8_pb, com_fn }

*/

#define WIDTH_BITS 7
#define WIDTH (1<<WIDTH_BITS)
#define PAGE_HEIGHT_BITS 3
#define PAGE_HEIGHT (1<<)
#define HEIGHT 128

void u8g_pb8h8_Clear(u8g_pb_t *b)
{
  uint8_t *ptr = (uint8_t *)b->buf;
  uint8_t *end_ptr = ptr;
  uint8_t cnt = PAGE_HEIGHT;
  do
  {
    end_ptr += b->width;
    cnt--;
  } while( cnt > 0 );
  do
  {
    *ptr++ = 0;
  } while( ptr != end_ptr );
}


void u8g_pb8h8_Init(u8g_pb_t *b, void *buf, u8g_uint_t width)
{
  b->buf = buf;
  b->width = width;
  u8g_pb8h8_Clear(b);
}

void u8g_pb8v2_set_pixel(u8g_pb_t *b, u8g_uint_t x, u8g_uint_t y, uint8_t color_index)
{
  register uint8_t mask;
  uint16_t tmp;
  uint8_t *ptr = b->buf;
  y -= b->p.page_y0;
  tmp = y;
  tmp <<= WIDTH_BITS;
  tmp += x;
  ptr += tmp;
  *ptr = color_index;
}



