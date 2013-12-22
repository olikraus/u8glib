/*
  
  pgtest.c
  
  Polygon test procedures. 

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
 
  See also:
  http://www.angelfire.com/linux/myp/ConvexPolRas/ConvexPolRas.html
  Computer Graphics, Principles and Practice, Foley, van Dam, Feiner, Hughes (pp 92)
  Michael Abrash's Graphics Programming Black Book, Special Edition (Chapter 38 and 39)

  Optimized for embedded systems
  - static memory usage only
  - consistent data types
  - low flash ROM consumption
  

*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "polygon.h"


#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 20
char  screen[SCREEN_HEIGHT][SCREEN_WIDTH];
int screen_color = '*';

void screen_init(void)
{
  int i, j;
  for( i = 0; i < SCREEN_HEIGHT; i++ )
  {
    for( j = 0; j < SCREEN_WIDTH; j++ )
    {
      screen[i][j] = ' ';
    }
  }
}

void screen_set_xy_with_color(int x, int y, int color)
{
  if ( x < 0 || x >= SCREEN_WIDTH )
  {
    printf("range x error '%c' %d %d\n", color, x, y);    
    return;
  }
  if ( y < 0 || y >= SCREEN_HEIGHT )
  {
    printf("range y error '%c' %d %d\n", color, x, y);    
    return;
  }
  if ( screen[y][x] != ' ' )
  {
    printf("overwrite error '%c' %d %d\n", color, x, y);    
  }
  screen[y][x] = color;
}

/* draw line, excluding x2 */
void screen_hline_with_color(int x1, int x2, int y, int color)
{
  while( x1 < x2 )
  {
      screen_set_xy_with_color(x1, y, color);    
      x1++;
  }
}


void screen_set_xy(int x, int y)
{
  screen_set_xy_with_color(x, y, screen_color);
  // printf("'%c' %d %d\n", screen_color, x, y);
}

void screen_hline(int x1, int x2, int y)
{
  screen_hline_with_color(x1, x2, y, screen_color);
}

void screen_print(void)
{
  int i, j;
  for( i = 0; i < SCREEN_HEIGHT; i++ )
  {
    for( j = 0; j < SCREEN_WIDTH; j++ )
    {
      printf("%c", screen[i][j]);
    }
    printf("\n");
  }
}

void screen_check_filled(void)
{
  int i, j;
  int err_cnt = 0;
  for( i = 0; i < SCREEN_HEIGHT; i++ )
  {
    for( j = 0; j < SCREEN_WIDTH; j++ )
    {
      if ( screen[i][j] == ' ' )
	err_cnt++;
      
    }
  }
  if ( err_cnt > 0 )
      printf("not filled error (not filled: %d)\n", err_cnt);
}


void pg_cycle(pg_struct *pg)
{
  pg_word_t x;
  pg_word_t y;
  uint8_t i;
  x = pg->list[0].x;
  y = pg->list[0].y;
  for( i = 0; i+1 < pg->cnt; i++ )
  {
    pg->list[i].x = pg->list[i+1].x;
    pg->list[i].y = pg->list[i+1].y;
  }
  pg->list[pg->cnt-1].x = x;
  pg->list[pg->cnt-1].y = y;
  
}

/* test01: three triangle which fill the screen */
void test01(int cycles, pg_word_t x)
{
  int i;
  pg_struct pg;
  screen_init();
  
  screen_color = '1';
  pg_Clear(&pg);
  pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, 0, SCREEN_HEIGHT);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '2';
  pg_Clear(&pg);
  pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, x, 0);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  pg_Draw(&pg);

  screen_color = '3';
  pg_Clear(&pg);
  pg_AddXY(&pg, SCREEN_WIDTH, 0);
  pg_AddXY(&pg, x, 0);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);
  

  screen_check_filled();
  //screen_print();  
}

/* test02: like test02, but some ponts are permutated */
void test02(int cycles, pg_word_t x)
{
  int i;
  pg_struct pg;
  screen_init();
  
  screen_color = '1';
  pg_Clear(&pg);
  pg_AddXY(&pg, 0, SCREEN_HEIGHT);
  pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '2';
  pg_Clear(&pg);
  pg_AddXY(&pg, x, 0);
  pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  pg_Draw(&pg);

  screen_color = '3';
  pg_Clear(&pg);
  pg_AddXY(&pg, SCREEN_WIDTH, 0);
  pg_AddXY(&pg, x, 0);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);
  
  screen_check_filled();
  //screen_print();  
}

/* test03: four triangles, point in the middle */
void test03(int cycles, int d1, int d2, int d3, pg_word_t x, pg_word_t y)
{
  int i;
  pg_struct pg;
  screen_init();
  
  screen_color = '1';
  pg_Clear(&pg);
  for( i = 0; i < d1; i++ )
    pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, 0, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '2';
  pg_Clear(&pg);
  pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, x, y);
  for( i = 0; i < d2; i++ )
    pg_AddXY(&pg, SCREEN_WIDTH, 0);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '3';
  pg_Clear(&pg);
  pg_AddXY(&pg, SCREEN_WIDTH, 0);
  pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '4';
  pg_Clear(&pg);
  for( i = 0; i < d3; i++ )
    pg_AddXY(&pg, 0, SCREEN_HEIGHT);
  pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);
  
  screen_check_filled();
  //screen_print();  
}

/* test04: four boxes, point in the middle */
void test04(int cycles, int d1, int d2, int d3, pg_word_t x, pg_word_t y)
{
  int i;
  pg_struct pg;
  screen_init();

  screen_color = '1';
  pg_Clear(&pg);
  for( i = 0; i < d1; i++ )
    pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, x, 0);
  pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, 0, y);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '2';
  pg_Clear(&pg);
  pg_AddXY(&pg, SCREEN_WIDTH, 0);
  pg_AddXY(&pg, x, 0);
  for( i = 0; i < d2; i++ )
    pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, SCREEN_WIDTH, y);
  pg_Draw(&pg);

  screen_color = '3';
  pg_Clear(&pg);
  pg_AddXY(&pg, 0, SCREEN_HEIGHT);
  pg_AddXY(&pg, x, SCREEN_HEIGHT);
  for( i = 0; i < d2; i++ )
    pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, 0, y);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);
  
  screen_color = '4';
  pg_Clear(&pg);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  pg_AddXY(&pg, x, SCREEN_HEIGHT);
  pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, SCREEN_WIDTH, y);
  pg_Draw(&pg);

  screen_check_filled();
  //screen_print();  
}

/* test05: horizontal empty polygons */
void test05(int cycles, int d1, int d2)
{
  int i;
  pg_struct pg;
  screen_init();

  screen_color = '1';
  pg_Clear(&pg);
  for( i = 0; i < d1; i++ )
    pg_AddXY(&pg, 0, 0);
  for( i = 0; i < d2; i++ )
    pg_AddXY(&pg, SCREEN_WIDTH, 0);
  pg_AddXY(&pg, SCREEN_WIDTH, 0);
  pg_AddXY(&pg, 0, 0);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '2';
  pg_Clear(&pg);
  pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, SCREEN_WIDTH, 0);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  pg_AddXY(&pg, 0, SCREEN_HEIGHT);
  pg_Draw(&pg);


  screen_check_filled();
  //screen_print();  
}

/* test06: like test03, but modified double points */
void test06(int cycles, int d1, int d2, int d3, pg_word_t x, pg_word_t y)
{
  int i;
  pg_struct pg;
  screen_init();
  
  screen_color = '1';
  pg_Clear(&pg);
  pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, 0, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '2';
  pg_Clear(&pg);
  pg_AddXY(&pg, 0, 0);
  pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, SCREEN_WIDTH, 0);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '3';
  pg_Clear(&pg);
  pg_AddXY(&pg, SCREEN_WIDTH, 0);
  pg_AddXY(&pg, x, y);
  pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);

  screen_color = '4';
  pg_Clear(&pg);
  for( i = 0; i < d1; i++ )
    pg_AddXY(&pg, 0, SCREEN_HEIGHT);
  for( i = 0; i < d2; i++ )
    pg_AddXY(&pg, x, y);
  for( i = 0; i < d3; i++ )
    pg_AddXY(&pg, SCREEN_WIDTH, SCREEN_HEIGHT);
  for( i = 0; i < cycles; i++ )
    pg_cycle(&pg);
  pg_Draw(&pg);
  
  screen_check_filled();
  //screen_print();  
}


int main(void)
{
  int i, j, k, l;
  puts("test01+02");
  for( i = 1; i < 7; i++ )
  {
    test01(0, SCREEN_WIDTH/i);
    test01(1, SCREEN_WIDTH/i);
    test01(2, SCREEN_WIDTH/i);
    test02(0, SCREEN_WIDTH/i);
    test02(1, SCREEN_WIDTH/i);
    test02(2, SCREEN_WIDTH/i);
  }
  
  test01(0, SCREEN_WIDTH-4);
  test01(1, SCREEN_WIDTH-5);
  test01(2, SCREEN_WIDTH-6);
  
  test02(0, SCREEN_WIDTH-4);
  test02(1, SCREEN_WIDTH-5);
  test02(2, SCREEN_WIDTH-6);
  //screen_print();  

  puts("test03");
  for( i = 0; i < 6; i++ )
  {
    for( j = 1; j < 3; j++ )
      for( k = 1; k < 3; k++ )
	for( l = 1; l < 3; l++ )
	{
	  test03(i, j, k, l, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	  test03(i, j, k, l, SCREEN_WIDTH/7, SCREEN_HEIGHT/7);
	  test03(i, j, k, l, SCREEN_WIDTH-3, SCREEN_HEIGHT/7);
	  test03(i, j, k, l, SCREEN_WIDTH-3, SCREEN_HEIGHT-3);
	}
  }

  test03(0, 1, 1, 1, SCREEN_WIDTH/7, SCREEN_HEIGHT/7);
  test03(1, 1, 1, 1, SCREEN_WIDTH/7, SCREEN_HEIGHT/7);
  test03(2, 1, 1, 1, SCREEN_WIDTH/7, SCREEN_HEIGHT/7);
  test03(0, 1, 1, 1, 10, 10);
  test03(0, 2, 2, 2, 10, SCREEN_HEIGHT-1);
  
  puts("test04");
  for( i = 0; i < 6; i++ )
  {
    for( j = 1; j < 3; j++ )
      for( k = 1; k < 3; k++ )
	for( l = 1; l < 3; l++ )
	{
	    test04(i, j, k, l, SCREEN_WIDTH/7, SCREEN_HEIGHT/7);
	}
  }
  
  puts("test05");
  for( i = 0; i < 6; i++ )
  {
    for( j = 1; j < 3; j++ )
      for( k = 1; k < 3; k++ )
	    test05(i, j, k);
  }
  
  puts("test06");
  test06(0, 2, 2, 2, 10, SCREEN_HEIGHT-2);
  screen_print();  
  return 0;
}

#ifdef EXAMPLECODE
int main2()
{
  pg_struct pg;
  screen_init();
  
  screen_color = '1';
  pg_Clear(&pg);
  pg_AddXY(&pg, 5, 1);
  pg_AddXY(&pg, 10, 10);
  pg_AddXY(&pg, 2, 8);
  pg_Draw(&pg);
  
  // screen_set_xy_with_color(5,1,'+');
  // screen_set_xy_with_color(10,10,'+');
  // screen_set_xy_with_color(2,8,'+');
  
  screen_color = '2';
  pg_Clear(&pg);
  pg_AddXY(&pg, 5, 1);
  pg_AddXY(&pg, 10, 10);
  pg_AddXY(&pg, 22, 8);
  pg_Draw(&pg);

  screen_color = '3';
  pg_Clear(&pg);
  pg_AddXY(&pg, 22, 8);
  pg_AddXY(&pg, 10, 10);
  pg_AddXY(&pg, 18, 12);
  pg_Draw(&pg);

  screen_set_xy_with_color(22,8,'+');
  screen_set_xy_with_color(10,10,'+');
  // screen_set_xy_with_color(18,12,'+');

  //printf("total_scan_line_cnt = %d\n", pg.total_scan_line_cnt);
  screen_check_filled();
  screen_print();
}

#endif