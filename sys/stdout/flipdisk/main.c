

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>

void writeFlipDiscMatrixRow(uint8_t width, uint8_t *row)
{
  uint8_t i, b;
  for( b = 0; b < 7; b++ )
  {
    for( i = 0; i < width; i++ )
    {
      if ( row[i] & (1<<b) )
      {
	printf("*");
      }
      else
      {
	printf(".");
      }
    }
    printf("\n");
  }
}


/*
  Write data to the flip disc matrix.
  This procedure must be implemented by the user.
  Arguments:
    id:	Id for the matrix. Currently always 0.
    page: 	A page has a height of 14 pixel. For a matrix with HEIGHT == 14 this will be always 0
    width: 	The width of the flip disc matrix. Always equal to WIDTH
    row1: 	first data line (7 pixel per byte)
    row2: 	first data line (7 pixel per byte)
*/
void writeFlipDiscMatrix(uint8_t id, uint8_t page, uint8_t width, uint8_t *row1, uint8_t *row2)
{
  writeFlipDiscMatrixRow(width, row1);
  writeFlipDiscMatrixRow(width, row2);
}


int main(void)
{
  u8g_uint_t h;
  u8g_t u8g;
  
  u8g_Init(&u8g, &u8g_dev_flipdisc_2x7);
  u8g_SetFlipDiscCallback(&u8g, writeFlipDiscMatrix);
  u8g_FirstPage(&u8g);
  u8g_SetColorIndex(&u8g, 1);
  do
  {
    u8g_DrawLine(&u8g, 0,0,13,13);
    u8g_SetFont(&u8g, u8g_font_7x13);
    h = u8g_GetFontAscent(&u8g);
    u8g_DrawStr(&u8g, 10, h, "ABCgdef");
  }while( u8g_NextPage(&u8g) );
  return 0;
}



