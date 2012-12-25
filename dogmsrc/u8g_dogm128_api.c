/*

  u8g_dogm128_api.c
  
  Simulation of the dogm128 api for the u8g library

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

#include "u8g_dogm128_api.h"

extern void st_Setup(u8g_t *u8g);

u8g_t u8g_dogm128_obj;
uint8_t dog_height_minus_one;


static void u8g_init_dogm_common(void)
{
  dog_height_minus_one = DOG_HEIGHT;
  dog_height_minus_one--;
  st_Setup(&u8g_dogm128_obj);

}

uint8_t u8g_InitDogm128API(u8g_dev_t *dev)
{
  if ( u8g_Init(&u8g_dogm128_obj, dev) == 0 )
    return 0;
  u8g_init_dogm_common();
  return 1;
}

uint8_t u8g_InitSPIDogm128API(u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset)
{

  if ( u8g_InitSPI(&u8g_dogm128_obj, dev, sck, mosi, cs, a0, reset) == 0 )
    return 0;
  u8g_init_dogm_common();
  return 1;  
}

uint8_t u8g_InitHWSPIDogm128API(u8g_dev_t *dev, uint8_t cs, uint8_t a0, uint8_t reset)
{

  if ( u8g_InitHWSPI(&u8g_dogm128_obj, dev, cs, a0, reset) == 0 )
    return 0;
  u8g_init_dogm_common();
  return 1;
}


void u8g_SetDogmRot90(void)
{
  u8g_SetRot90(&u8g_dogm128_obj);
  u8g_init_dogm_common();
}

void u8g_SetDogmRot180(void)
{
  u8g_SetRot180(&u8g_dogm128_obj);
  u8g_init_dogm_common();
}

void u8g_SetDogmRot270(void)
{
  u8g_SetRot270(&u8g_dogm128_obj);
  u8g_init_dogm_common();
}

void dog_StartPage(void)
{
  u8g_FirstPage(&u8g_dogm128_obj);
}

uint8_t dog_NextPage(void)
{
  return u8g_NextPage(&u8g_dogm128_obj);
}


void dog_SetPixel(uint8_t x, uint8_t y)
{
  y = dog_height_minus_one - y;
  u8g_SetColorIndex(&u8g_dogm128_obj, 1);  
  u8g_DrawPixel(&u8g_dogm128_obj, x, y);  
}

void dog_ClrPixel(uint8_t x, uint8_t y)
{
  y = dog_height_minus_one - y;
  u8g_SetColorIndex(&u8g_dogm128_obj, 0);
  u8g_DrawPixel(&u8g_dogm128_obj, x, y);  
}

void dog_XorPixel(uint8_t x, uint8_t y)
{
  /* not yet implemented */
}

/* x1 must be lower or equal to x2 */
void dog_SetHLine(uint8_t x1, uint8_t x2, uint8_t y)
{
  //printf("SetHLine x1:%d x2:%d y:%d\n", x1, x2, y);
  y = dog_height_minus_one - y;
  u8g_SetColorIndex(&u8g_dogm128_obj, 1);
  u8g_DrawHLine(&u8g_dogm128_obj, x1, y, x2-x1+1);
  //printf("SetHLine x:%d y:%d w:%d \n", x1, y, x2-x1+1);
}

void dog_ClrHLine(uint8_t x1, uint8_t x2, uint8_t y)
{
  y = dog_height_minus_one - y;
  u8g_SetColorIndex(&u8g_dogm128_obj, 0);
  u8g_DrawHLine(&u8g_dogm128_obj, x1, y, x2-x1+1);
}

void dog_XorHLine(uint8_t x1, uint8_t x2, uint8_t y)
{
  /* not yet implemented */
}


void dog_SetVLine(uint8_t x, uint8_t y1, uint8_t y2)
{
  
  y1 = dog_height_minus_one - y1;
  y2 = dog_height_minus_one - y2;
  u8g_SetColorIndex(&u8g_dogm128_obj, 1);
  u8g_DrawVLine(&u8g_dogm128_obj, x, y2, y1-y2+1);
}

void dog_ClrVLine(uint8_t x, uint8_t y1, uint8_t y2)
{
  y1 = dog_height_minus_one - y1;
  y2 = dog_height_minus_one - y2;
  u8g_SetColorIndex(&u8g_dogm128_obj, 0);
  u8g_DrawVLine(&u8g_dogm128_obj, x, y2, y1-y2+1);
}

void dog_XorVLine(uint8_t x, uint8_t y1, uint8_t y2)
{
  /* not yet implemented */
}

void dog_SetBitmapP(uint8_t x, uint8_t y, DOG_PGM_P bitmap, uint8_t w, uint8_t h)
{
  u8g_SetColorIndex(&u8g_dogm128_obj, 1);
  y = dog_height_minus_one - y;
  /*  not fully compatible, it is assumed, that the "not used" bits are set to zero */
  u8g_DrawBitmapP(&u8g_dogm128_obj, x, y, (w+7)/8, h, bitmap);
}

void dog_ClrBitmapP(uint8_t x, uint8_t y, DOG_PGM_P bitmap, uint8_t w, uint8_t h)
{
  u8g_SetColorIndex(&u8g_dogm128_obj, 0);
  y = dog_height_minus_one - y;
  /*  not fully compatible, it is assumed, that the "not used" bits are set to zero */
  u8g_DrawBitmapP(&u8g_dogm128_obj, x, y, (w+7)/8, h, bitmap);
}

/* x1 must be lower or equal to x2 */
/* y1 must be lower or equal to y2 */
void dog_SetBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  y1 = dog_height_minus_one - y1;
  y2 = dog_height_minus_one - y2;
  u8g_SetColorIndex(&u8g_dogm128_obj, 1);
  u8g_DrawBox(&u8g_dogm128_obj, x1, y2, x2-x1+1, y1-y2+1);
}

void dog_ClrBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  y1 = dog_height_minus_one - y1;
  y2 = dog_height_minus_one - y2;
  u8g_SetColorIndex(&u8g_dogm128_obj, 0);
  u8g_DrawBox(&u8g_dogm128_obj, x1, y2, x2-x1+1, y1-y2+1);
}

void dog_XorBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  /* not yet implemented */
}

uint8_t dog_GetStrWidth(DOG_PGM_P font, const char *s)
{
  u8g_SetFont(&u8g_dogm128_obj, font);
  return u8g_GetStrWidth(&u8g_dogm128_obj, s);
}


uint8_t dog_DrawStr(uint8_t x, uint8_t y, DOG_PGM_P font, const char *s)
{
  y = dog_height_minus_one - y;
  u8g_SetFont(&u8g_dogm128_obj, font);
  u8g_SetColorIndex(&u8g_dogm128_obj, 1);
  return u8g_DrawStr(&u8g_dogm128_obj, x, y, s);
}

uint8_t dog_DrawStrP(uint8_t x, uint8_t y, DOG_PGM_P font, const u8g_pgm_uint8_t  *s)
{
  y = dog_height_minus_one - y;
  u8g_SetFont(&u8g_dogm128_obj, font);
  u8g_SetColorIndex(&u8g_dogm128_obj, 1);
  return u8g_DrawStrP(&u8g_dogm128_obj, x, y, s);
}


char dog_itoa_buf[12];
char *dog_itoa(unsigned long v)
{
  volatile unsigned char i = 11;
  dog_itoa_buf[11] = '\0';
  while( i > 0)
  {
      i--;
      dog_itoa_buf[i] = (v % 10)+'0';
      v /= 10;
      if ( v == 0 )
	break;
  }
  return dog_itoa_buf+i;
}
