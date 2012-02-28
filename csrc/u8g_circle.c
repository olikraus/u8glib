/*

  u8g_circle.c

  Utility to draw empty and filled circles.
  
  Universal 8bit Graphics Library
  
  Copyright (c) 2011, bjthom@gmail.com
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
  
  Addition to the U8G Library 02/25/12
  
  
*/

#include "u8g.h"

void u8g_DrawEmpCirc(u8g_t *u8g, u8g_uint_t x0, u8g_uint_t y0, u8g_uint_t rad)
{
  int f = 1 - rad;
  int ddF_x = 1;
  int ddF_y = -2*rad;
  uint8_t x = 0;
  uint8_t y = rad;
  
  u8g_DrawPixel(u8g, x0, y0 + rad);
  u8g_DrawPixel(u8g, x0, y0 - rad);
  u8g_DrawPixel(u8g, x0 + rad, y0);
  u8g_DrawPixel(u8g, x0 - rad, y0);


  while( x < y )
  {
    if(f >= 0) 
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;    
    u8g_DrawPixel(u8g, x0 + x, y0 + y);
    u8g_DrawPixel(u8g, x0 - x, y0 + y);
    u8g_DrawPixel(u8g, x0 + x, y0 - y);
    u8g_DrawPixel(u8g, x0 - x, y0 - y);
    u8g_DrawPixel(u8g, x0 + y, y0 + x);
    u8g_DrawPixel(u8g, x0 - y, y0 + x);
    u8g_DrawPixel(u8g, x0 + y, y0 - x);
    u8g_DrawPixel(u8g, x0 - y, y0 - x);
  }
}

void u8g_DrawFillCirc(u8g_t *u8g, u8g_uint_t x0, u8g_uint_t y0, u8g_uint_t rad)
{
  int f = 1 - rad;
  int ddF_x = 1;
  int ddF_y = -2*rad;
  uint8_t x = 0;
  uint8_t y = rad;
  
  // Draw vertical diameter at the horiz. center
  u8g_DrawVLine(u8g, x0, y0 - rad, 2*rad+1);

  while( x < y )
  {
    if(f >= 0) 
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
	//Draw vertical lines from one point to another
    u8g_DrawVLline(u8g, x0+x, y0-y, 2*y+1);
	u8g_DrawVLine(u8g, x0-x, y0-y, 2*y+1);
	u8g_DrawVLine(u8g, x0+y, y0-x, 2*x+1);
	u8g_DrawVLine(u8g, x0-y, y0-x, 2*x+1);
  }
}
