/*

  2 bit example
  
  Includes Wu Line Draw algorithm
  
  References to the circle draw algorithm:
  http://www.landkey.net/d/antialiased/wu4_RF/
  http://www.landkey.net/d/antialiased/wu4_RF/Content/WU/src/NoSqrt.java.htm
  http://yellowsplash.wordpress.com/2009/10/23/fast-antialiased-circles-and-ellipses-from-xiaolin-wus-concepts/

*/

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>


/*
    Michael Abrash's Graphics Programming Black Book Special Edition, p 780
*/
#define BaseColor 0
#define NumLevels 4
#define IntensityBits 2
#define FractionBits 16

void u8g_DrawWuPixel(u8g_t *u8g, u8g_uint_t x0, u8g_uint_t y0, uint8_t intensity)
{
  u8g_SetColorIndex(u8g, NumLevels-1-intensity);
  u8g_DrawPixel(u8g, x0, y0);
}

void u8g_DrawWuLine2Bit(u8g_t *u8g, u8g_uint_t x0, u8g_uint_t y0, u8g_uint_t x1, u8g_uint_t y1)
{
  uint16_t ErrorAdj, ErrorAcc, ErrorAccTemp;
  uint16_t IntensityShift;
  u8g_uint_t DeltaX, DeltaY;
  u8g_uint_t  XDir;
  uint8_t Weighting, WeightingComplementMask;
  
  if ( y0 > y1 )
  {
    u8g_uint_t temp;
    temp = y0; y0 = y1; y1= temp;
    temp = x0; x0 = x1; x1= temp;
  }
  DeltaY = y1 - y0;
  
  
  if ( x1 >= x0 )
  {
    DeltaX = x1 - x0;
    XDir = 1;
  }
  else
  {
    DeltaX = x0 - x1;
    XDir = 0;
    XDir--;
  }
  
  if ( DeltaX == 0 )
  {
    u8g_SetColorIndex(u8g, NumLevels-1-0);
    u8g_DrawVLine(u8g, x0, y0, DeltaY+1 );
    return;
  }

  if ( DeltaY == 0 )
  {
    u8g_SetColorIndex(u8g, NumLevels-1-0);
    u8g_DrawHLine(u8g, x0, y0, DeltaX+1 );
    return;
  }

  u8g_DrawWuPixel(u8g, x0, y0, BaseColor);
  
  ErrorAcc = 0;
  IntensityShift = FractionBits - IntensityBits;                        // constant
  WeightingComplementMask = NumLevels - 1;                      // constant
  if ( DeltaY > DeltaX )
  {
    ErrorAdj = ((unsigned long)DeltaX << 16) / (unsigned long)DeltaY;
    while( --DeltaY )
    {
      ErrorAccTemp = ErrorAcc;
      ErrorAcc += ErrorAdj;
      if ( ErrorAcc <= ErrorAccTemp )
      {
        x0 += XDir;
      }
      y0++;
      Weighting = ErrorAcc >> IntensityShift;
      u8g_DrawWuPixel(u8g, x0, y0, BaseColor+Weighting);
      Weighting ^= WeightingComplementMask;
      u8g_DrawWuPixel(u8g, x0+XDir, y0, BaseColor+Weighting);
    }
  }
  else
  {
    ErrorAdj = ((unsigned long)DeltaY << 16) / (unsigned long)DeltaX;
    while( --DeltaX )
    {
      ErrorAccTemp = ErrorAcc;
      ErrorAcc += ErrorAdj;
      if ( ErrorAcc <= ErrorAccTemp )
      {
        y0++;
      }
      x0 += XDir;
      Weighting = ErrorAcc >> IntensityShift;
      u8g_DrawWuPixel(u8g, x0, y0, BaseColor+Weighting);
      Weighting ^= WeightingComplementMask;
      u8g_DrawWuPixel(u8g, x0, y0+1, BaseColor+Weighting);
    }
  }
  u8g_DrawWuPixel(u8g, x1, y1, BaseColor);
}



int u8g_sdl_get_key(void);


int main(void)
{
  u8g_uint_t w,h;
  u8g_t u8g;
  
  u8g_Init(&u8g, &u8g_dev_sdl_2bit);
  u8g_FirstPage(&u8g);
  do
  {
    u8g_SetFont(&u8g, u8g_font_10x20);
    u8g_SetFont(&u8g, u8g_font_fur25);
    w = u8g_GetFontBBXWidth(&u8g);
    h = u8g_GetFontBBXHeight(&u8g);
    
    u8g_SetColorIndex(&u8g, 1);
    u8g_DrawStr(&u8g, 30, 35, "gabc");
    u8g_SetColorIndex(&u8g, 2);
    u8g_DrawStr(&u8g, 30+1, 35+1, "gabc");
    u8g_SetColorIndex(&u8g, 3);
    u8g_DrawStr(&u8g, 30+2, 35+2, "gabc");
    
    u8g_DrawWuLine2Bit(&u8g, 0, 63, 100, 63);
    u8g_DrawWuLine2Bit(&u8g, 0, 63-3, 100, 63-5);
    u8g_DrawWuLine2Bit(&u8g, 0, 63-2*3, 100, 63-2*5);

    
  }while( u8g_NextPage(&u8g) );
  
  while( u8g_sdl_get_key() < 0 )
    ;
  
  return 0;
}



