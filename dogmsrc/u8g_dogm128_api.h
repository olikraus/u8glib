/*

  u8g_dogm128_api.h
  
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

#ifndef _U8G_DOGM128_API_H
#define _U8G_DOGM128_API_H

#include "u8g.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef u8g_pgm_uint8_t dog_pgm_uint8_t;

#define DOG_PGM_P const dog_pgm_uint8_t *
#define DOG_PSTR_P const dog_pgm_uint8_t *
#define DOG_PSTR(s) U8G_PSTR(s)

#if defined(__AVR__)
#define DOG_PROGMEM PROGMEM
#else
#define DOG_PROGMEM
#endif

/* rom keyword on the chipkit environment */
#define DOG_ROM

#define DOG_ATTR_FN_NOINLINE U8G_NOINLINE

#define dog_pgm_read(adr) u8g_pgm_read(adr)


extern u8g_t u8g_dogm128_obj;
extern uint8_t dog_height_minus_one;

#define DOG_WIDTH (u8g_dogm128_obj.width)
#define DOG_HEIGHT (u8g_dogm128_obj.height)


/* this is a special u8g procedure to start up the dogm128 interface */
uint8_t u8g_InitDogm128API(u8g_dev_t *dev);
uint8_t u8g_InitSPIDogm128API(u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset);
uint8_t u8g_InitHWSPIDogm128API(u8g_dev_t *dev, uint8_t cs, uint8_t a0, uint8_t reset);
void u8g_SetDogmRot90(void);
void u8g_SetDogmRot180(void);
void u8g_SetDogmRot270(void);


/* the following procedures are supported in the dogm128 API */
void dog_StartPage(void);
uint8_t dog_NextPage(void);
void dog_SetPixel(uint8_t x, uint8_t y);
void dog_ClrPixel(uint8_t x, uint8_t y);
void dog_SetHLine(uint8_t x1, uint8_t x2, uint8_t y);
void dog_ClrHLine(uint8_t x1, uint8_t x2, uint8_t y);
void dog_SetVLine(uint8_t x, uint8_t y1, uint8_t y2);
void dog_ClrVLine(uint8_t x, uint8_t y1, uint8_t y2);
void dog_SetBitmapP(uint8_t x, uint8_t y, DOG_PGM_P bitmap, uint8_t w, uint8_t h);
void dog_SetBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void dog_ClrBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
uint8_t dog_GetStrWidth(DOG_PGM_P font, const char *s);
uint8_t dog_DrawStr(uint8_t x, uint8_t y, DOG_PGM_P font, const char *s);
uint8_t dog_DrawStrP(uint8_t x, uint8_t y, DOG_PGM_P font, const u8g_pgm_uint8_t  *s);
char *dog_itoa(unsigned long v);

/* mapping from dogm128 fonts to u8g fonts */
#define font_4x6 u8g_font_4x6r
#define font_5x7 u8g_font_5x7r
#define font_5x8 u8g_font_5x8r
#define font_6x9 u8g_font_6x9r
#define font_6x10 u8g_font_6x10r
#define font_6x12 u8g_font_6x12r
#define font_6x13 u8g_font_6x13r
#define font_7x13 u8g_font_7x13r
#define font_7x14 u8g_font_7x14r
#define font_8x13 u8g_font_8x13r
#define font_9x15 u8g_font_9x15r
#define font_9x18 u8g_font_9x18r

#ifdef __cplusplus
}
#endif

#endif /* _U8G_DOGM128_API_H */
