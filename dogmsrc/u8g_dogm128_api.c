/*

  u8g_dogm128_api.c
  
  Simulation of the dogm128 api for the u8g library
  
*/

#include "u8g_dogm128_api.h"

u8g_t u8g_dogm128_obj;
uint8_t dog_height_minus_one;


uint8_t u8g_InitDogm128API(u8g_dev_t *dev)
{
  if ( u8g_Init(&u8g_dogm128_obj, dev) == 0 )
    return 0;
  dog_height_minus_one = DOG_HEIGHT;
  dog_height_minus_one--;
  return 1;
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
  y = dog_height_minus_one - y;
  u8g_SetColorIndex(&u8g_dogm128_obj, 1);
  u8g_DrawHLine(&u8g_dogm128_obj, x1, y, x2-x1+1);
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
  u8g_DrawBox(&u8g_dogm128_obj, x1, y1, x2-x1+1, y1-y2+1);
}

void dog_ClrBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  //printf("Clrbox %d %d %d %d\n", x1, x2, y1, y2);
  y1 = dog_height_minus_one - y1;
  y2 = dog_height_minus_one - y2;
  u8g_SetColorIndex(&u8g_dogm128_obj, 0);
  u8g_DrawBox(&u8g_dogm128_obj, x1, y1, x2-x1+1, y1-y2+1);
}

void dog_XorBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  /* not yet implemented */
}

uint8_t dog_DrawStr(uint8_t x, uint8_t y, DOG_PGM_P font, const char *s)
{
  y = dog_height_minus_one - y;
  u8g_SetFont(&u8g_dogm128_obj, font);
  return u8g_DrawStr(&u8g_dogm128_obj, x, y, s);
}

uint8_t dog_DrawStrP(uint8_t x, uint8_t y, DOG_PGM_P font, const u8g_pgm_uint8_t  *s)
{
  y = dog_height_minus_one - y;
  u8g_SetFont(&u8g_dogm128_obj, font);
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
