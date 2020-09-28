/*
  
  u8g_logo.c

  Linux U8glib Example

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

#include "u8g_linux.h"

u8g_t u8g;

/* select, which color background to use  */
#define COLOR_BOX draw_color_box2

void draw_color_box1(void)
{
  u8g_uint_t w,h;
  u8g_uint_t r, g, b;
  
  w = u8g_GetWidth(&u8g)/64;
  h = u8g_GetHeight(&u8g)/32;
  for( b = 0; b < 4; b++ )
    for( g = 0; g < 16; g++ )
      for( r = 0; r < 32; r++ )
      {
	u8g_SetRGB(&u8g, r<<3, g<<4, b<<6);
	u8g_DrawBox(&u8g, g*w + b*w*16, r*h, w, h);
	  
      }
}

void draw_color_box2(void)
{
  u8g_uint_t w,h;
  u8g_uint_t r, g, b;
  
  b = 1;
  
  w = u8g_GetWidth(&u8g)/64;
  h = u8g_GetHeight(&u8g)/32;
    for( g = 0; g < 16; g++ )
      for( r = 0; r < 32; r++ )
      {
	u8g_SetRGB(&u8g, r<<3, g<<4, b<<6);
	u8g_DrawBox(&u8g, g*w + 0*w*16, r*h, w, h);
	u8g_DrawBox(&u8g, (16-1-g)*w + 1*w*16, r*h, w, h);
	u8g_DrawBox(&u8g, g*w + 2*w*16, r*h, w, h);
	u8g_DrawBox(&u8g, (16-1-g)*w + 3*w*16, r*h, w, h);
	  
      }
}

void draw_color_box3(void)
{
    u8g_uint_t r, g, b;
    /* assumes 128x128 display */
    for( b = 0; b < 4; b++ )
    {
      for( g = 0; g < 32; g++ )
      {
	for( r = 0; r < 32; r++ )
	{
	  u8g_SetRGB(&u8g, r<<3, g<<3, b<<4 );
	  u8g_DrawPixel(&u8g, g + b*32, r);
	  u8g_SetRGB(&u8g, r<<3, g<<3, (b<<4)+64 );
	  u8g_DrawPixel(&u8g, g + b*32, r+32);
	  u8g_SetRGB(&u8g, r<<3, g<<3, (b<<4)+128 );
	  u8g_DrawPixel(&u8g, g + b*32, r+32+32);
	  u8g_SetRGB(&u8g, r<<3, g<<3, (b<<4)+128+64 );
	  u8g_DrawPixel(&u8g, g + b*32, r+32+32+32);
	}
      }
    }
}


void draw_logo(uint8_t d)
{
  u8g_SetFont(&u8g, u8g_font_gdr25r);
  u8g_DrawStr(&u8g, 0+d, 30+d, "U");
  u8g_SetFont(&u8g, u8g_font_gdr30n);
  u8g_DrawStr90(&u8g, 23+d,10+d,"8");
  u8g_SetFont(&u8g, u8g_font_gdr25r);
  u8g_DrawStr(&u8g, 53+d,30+d,"g");
  
  u8g_DrawHLine(&u8g, 2+d, 35+d, 47);
  u8g_DrawVLine(&u8g, 45+d, 32+d, 12);
}

void draw_url(void)
{
  u8g_SetFont(&u8g, u8g_font_4x6);
  if ( u8g_GetHeight(&u8g) < 59 )
  {
    u8g_DrawStr(&u8g, 53,9,"code.google.com");
    u8g_DrawStr(&u8g, 77,18,"/p/u8glib");
  }
  else
  {
    u8g_DrawStr(&u8g, 1,54,"code.google.com/p/u8glib");
  }
}


void draw(void) 
{
  if ( u8g_GetMode(&u8g) == U8G_MODE_HICOLOR || u8g_GetMode(&u8g) == U8G_MODE_R3G3B2)
  {
    COLOR_BOX();
  }
  if ( u8g_GetMode(&u8g) == U8G_MODE_HICOLOR || u8g_GetMode(&u8g) == U8G_MODE_R3G3B2)
  {
      u8g_SetRGB(&u8g, 0x080, 0x040, 0);
      draw_logo(2);
      u8g_SetRGB(&u8g, 0x080, 0x080, 0);
      draw_logo(1);
      u8g_SetRGB(&u8g, 0x0ff, 0x0ff, 0);
  }
  else
  {
    u8g_SetColorIndex(&u8g, 1);
    if ( U8G_MODE_GET_BITS_PER_PIXEL(u8g_GetMode(&u8g)) > 1 ) 
    {
      draw_logo(2);
      u8g_SetColorIndex(&u8g, 2);
      draw_logo(1);
      u8g_SetColorIndex(&u8g, 3);
    }
  }
  draw_logo(0);
  draw_url();
}

int main(int argc, const char *argv[])
{
  u8g_linux_Init(&u8g, argc, argv);
  u8g_FirstPage(&u8g);
  do
  {
    draw();
  } while ( u8g_NextPage(&u8g) );
}

