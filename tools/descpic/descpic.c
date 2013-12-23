

#include "u8g.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void post_processing(const char *target_pic_name)
{
  char cmd[256];
  sprintf(cmd, "convert u8g.pbm -trim -scale '200%%' %s.png", target_pic_name );
  system(cmd);
}


void create_picture( void (*draw_procedure)(u8g_t *u8g), const char *target_pic_name)
{
  u8g_t u8g;
  u8g_Init(&u8g, &u8g_dev_pbm);
  u8g_FirstPage(&u8g);
  do
  {
    draw_procedure(&u8g);
  }while( u8g_NextPage(&u8g) );
  
  post_processing(target_pic_name);
}

void create_picture_rot90( void (*draw_procedure)(u8g_t *u8g), const char *target_pic_name)
{
  u8g_t u8g;
  u8g_Init(&u8g, &u8g_dev_pbm);
  u8g_FirstPage(&u8g);
  u8g_SetRot90(&u8g);
  do
  {
    draw_procedure(&u8g);
  }while( u8g_NextPage(&u8g) );
  
  post_processing(target_pic_name);
}

void draw_common(u8g_t *u8g, u8g_uint_t ox, u8g_uint_t oy, u8g_uint_t w, u8g_uint_t h)
{
  u8g_SetCursorFont(u8g, u8g_font_cursor);
  
  /* draw the display frame */
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+w-35, oy-2, "128x64");
  u8g_DrawFrame(u8g, ox-1, oy-1, w+2, h+2);
  //u8g_DrawFrame(u8g, ox-2, oy-2, w+4, h+4);

  /* draw upper left corner */
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox-45, oy+4, "(0,0)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox, oy);
  u8g_DrawCursor(u8g);
}

void draw_common_simple(u8g_t *u8g, u8g_uint_t ox, u8g_uint_t oy, u8g_uint_t w, u8g_uint_t h)
{
  u8g_SetCursorFont(u8g, u8g_font_cursor);
  
  /* draw the display frame */
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+w-35, oy-2, "128x64");
  u8g_DrawFrame(u8g, ox-1, oy-1, w+2, h+2);
  //u8g_DrawFrame(u8g, ox-2, oy-2, w+4, h+4);

}

void draw_v_measure(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, int h)
{
  char buf[20];
  sprintf(buf, "%d", h);
  if ( h < 0 )
    h = -h;
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawHLine(u8g, x-1, y, 3);
  u8g_DrawHLine(u8g, x-1, y+h-1, 3);
  u8g_DrawVLine(u8g, x, y, h);
  u8g_DrawStr(u8g, x+2, y+(h-1)/2+4, buf);
}

void draw_h_measure(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t w)
{
  char buf[20];
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawVLine(u8g, x, y-1, 3);
  u8g_DrawVLine(u8g, x+w-1, y-1, 3);
  u8g_DrawHLine(u8g, x, y, w);
  sprintf(buf, "%d", w);
  u8g_DrawStr(u8g, x+(w-1)/2-5, y+9, buf);
}

void draw_dotted_hline(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t w)
{
  u8g_uint_t d = 5;
  while( w >= d )
  {
    u8g_DrawPixel(u8g, x,y);
    w -= d;
    x += d;
  }
}

/*======================================================*/

void draw_display(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);

  draw_h_measure(u8g, ox, oy+45, 128);
  draw_v_measure(u8g, ox+90, oy, 64);

  /* draw lower right corner */
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+w-1+17, oy+h-1+4, "(127,63)");
  u8g_SetCursorStyle(u8g, 142);
  u8g_SetCursorPos(u8g, ox+w-1, oy+h-1);
  u8g_DrawCursor(u8g);
}


void draw_text_abc(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_osb18);
  u8g_DrawStr(u8g, ox+0, oy+20, "ABC");  
  
  draw_v_measure(u8g, ox+56, oy+2, 18);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+0-51, oy+20+4, "(0,20)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+0, oy+20);
  u8g_DrawCursor(u8g);
}

void draw_circle(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_DrawCircle(u8g, ox+20, oy+20, 14, U8G_DRAW_ALL);  
  
  draw_dotted_hline(u8g, ox+20-16, oy+20-14, 70);
  draw_dotted_hline(u8g, ox+20-16, oy+20, 50);
  draw_dotted_hline(u8g, ox+20-16, oy+20+14, 70);
  
  draw_v_measure(u8g, ox+41, oy+20-14, 14);
  draw_v_measure(u8g, ox+60, oy+20-14, 29);
  draw_v_measure(u8g, ox+41, oy+20+1, 14);
  //draw_h_measure(u8g, ox+20, oy+20+4, 14);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+20-62, oy+20+4, "(20,20)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+20, oy+20);
  u8g_DrawCursor(u8g);
}

void draw_circle_ur(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_DrawCircle(u8g, ox+20, oy+20, 14, U8G_DRAW_UPPER_RIGHT);  
  
  draw_dotted_hline(u8g, ox+20-16, oy+20-14, 70);
  draw_dotted_hline(u8g, ox+20-16, oy+20, 50);
  //draw_dotted_hline(u8g, ox+20-16, oy+20+14, 70);
  
  draw_v_measure(u8g, ox+41, oy+20-14, 14);
  //draw_v_measure(u8g, ox+60, oy+20-14, 15);
  //draw_v_measure(u8g, ox+41, oy+20+1, 14);
  draw_h_measure(u8g, ox+20+1, oy+20+4, 14);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+20-62, oy+20+4, "(20,20)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+20, oy+20);
  u8g_DrawCursor(u8g);
}

void draw_text_abc_top(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_osb18);
  u8g_SetFontPosTop(u8g);
  u8g_DrawStr(u8g, ox+0, oy+20, "ABC");  
  u8g_SetFontPosBaseline(u8g);
  
  draw_v_measure(u8g, ox+56, oy+2+18+1, 18);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+0-51, oy+20+4, "(0,20)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+0, oy+20);
  u8g_DrawCursor(u8g);
}

void draw_ascent(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_10x20);
  u8g_DrawStr(u8g, ox+5, oy+20, "ABCdefg");  
  u8g_SetFontRefHeightText(u8g);
  
  draw_v_measure(u8g, ox+80, oy+20-u8g_GetFontAscent(u8g), u8g_GetFontAscent(u8g));
  draw_dotted_hline(u8g, ox+5, oy+20, 75);

  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+5-51, oy+20+4, "(5,20)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+5, oy+20);
  u8g_DrawCursor(u8g);
}


void draw_height_text(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_gdr25);
  u8g_SetFontRefHeightText(u8g);
  
  u8g_DrawStr(u8g, ox+5, oy+40, "(ABC)");  
  
  draw_v_measure(u8g, ox+100, oy+40-u8g_GetFontAscent(u8g), u8g_GetFontAscent(u8g));
  draw_dotted_hline(u8g, ox+5, oy+40, 95);

  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+5-51, oy+40+4, "(5,40)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+5, oy+40);
  u8g_DrawCursor(u8g);
}

void draw_height_extended_text(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_gdr25);
  u8g_SetFontRefHeightExtendedText(u8g);
  u8g_DrawStr(u8g, ox+5, oy+40, "(ABC)");  
  
  draw_v_measure(u8g, ox+100, oy+40-u8g_GetFontAscent(u8g), u8g_GetFontAscent(u8g));
  draw_dotted_hline(u8g, ox+5, oy+40, 95);

  u8g_SetFontRefHeightText(u8g);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+5-51, oy+40+4, "(5,40)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+5, oy+40);
  u8g_DrawCursor(u8g);
}

void draw_top_height_extended_text(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_gdr25);
  u8g_SetFontRefHeightExtendedText(u8g);
  u8g_SetFontPosTop(u8g);
  u8g_DrawStr(u8g, ox+5, oy+20, "(ABC)");  
  u8g_SetFontPosBaseline(u8g);
  
  // draw_v_measure(u8g, ox+100, oy+20, u8g_GetFontAscent(u8g));
  draw_dotted_hline(u8g, ox+5, oy+20, 95);

  u8g_SetFontRefHeightText(u8g);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+5-51, oy+20+4, "(5,20)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+5, oy+20);
  u8g_DrawCursor(u8g);
}

void draw_height_all(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_gdr25);
  u8g_SetFontRefHeightAll(u8g);
  u8g_DrawStr(u8g, ox+5, oy+40, "(ABC)");  
  
  draw_v_measure(u8g, ox+100, oy+40-u8g_GetFontAscent(u8g), u8g_GetFontAscent(u8g));
  draw_dotted_hline(u8g, ox+5, oy+40, 95);

  u8g_SetFontRefHeightText(u8g);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+5-51, oy+40+4, "(5,40)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+5, oy+40);
  u8g_DrawCursor(u8g);
}

void draw_linespacing_text(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  int8_t a, d, ls;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_gdr25);
  u8g_SetFontRefHeightText(u8g);
  
  u8g_DrawStr(u8g, ox+5, oy+40, "(ABg)");  
  a = u8g_GetFontAscent(u8g);
  d = u8g_GetFontDescent(u8g);
  ls = u8g_GetFontLineSpacing(u8g);
  
  draw_v_measure(u8g, ox+100, oy+40-a, a);
  draw_v_measure(u8g, ox+100, oy+40, d);
  draw_v_measure(u8g, ox+114, oy+40-a, ls);
  draw_dotted_hline(u8g, ox+5, oy+40, 95);

  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+5-51, oy+40+4, "(5,40)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+5, oy+40);
  u8g_DrawCursor(u8g);
}

void draw_linespacing_xtext(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  int8_t a, d, ls;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_gdr25);
  u8g_SetFontRefHeightExtendedText(u8g);
  
  u8g_DrawStr(u8g, ox+5, oy+40, "(ABg)");  
  a = u8g_GetFontAscent(u8g);
  d = u8g_GetFontDescent(u8g);
  ls = u8g_GetFontLineSpacing(u8g);
  
  draw_v_measure(u8g, ox+100, oy+40-a, a);
  draw_v_measure(u8g, ox+100, oy+40, d);
  draw_v_measure(u8g, ox+114, oy+40-a, ls);
  draw_dotted_hline(u8g, ox+5, oy+40, 95);
  u8g_SetFontRefHeightText(u8g);

  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+5-51, oy+40+4, "(5,40)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+5, oy+40);
  u8g_DrawCursor(u8g);
}


void draw_descent(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_10x20);
  u8g_SetFontRefHeightText(u8g);
  u8g_DrawStr(u8g, ox+5, oy+20, "ABCdefg");  
  
  draw_v_measure(u8g, ox+80, oy+20, u8g_GetFontDescent(u8g));

  draw_dotted_hline(u8g, ox+5, oy+20, 75);

  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+5-51, oy+20+4, "(5,20)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+5, oy+20);
  u8g_DrawCursor(u8g);
}

void draw_hello_world(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_unifont);
  u8g_DrawStr(u8g, ox+0, oy+20, "Hello World!");  
  
}

void draw_text_abc_rot(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+w-35, oy-2, "128x64");
  u8g_DrawFrame(u8g, ox-1, oy-1, w+2, h+2);
  
  u8g_SetFont(u8g, u8g_font_osb18);
  u8g_DrawStr(u8g, ox+0, oy+20, "ABC");  
  
  draw_v_measure(u8g, ox+56, oy+2, 18);
  
//  u8g_SetFont(u8g, u8g_font_6x10);
//  u8g_DrawStr(u8g, ox+0-51, oy+20+4, "(0,20)");
//  u8g_SetCursorStyle(u8g, 144);
//  u8g_SetCursorPos(u8g, ox+0, oy+20);
//  u8g_DrawCursor(u8g);
}

void draw_text_abc_rot90(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr270(u8g, ox-2, oy+34, "64x128");
  u8g_DrawFrame(u8g, ox-1, oy-1, w+2, h+2);
  
  u8g_SetFont(u8g, u8g_font_osb18);
  u8g_DrawStr(u8g, ox+0, oy+20, "ABC");  
  
  draw_v_measure(u8g, ox+56, oy+2, 18);
  
//  u8g_SetFont(u8g, u8g_font_6x10);
//  u8g_DrawStr(u8g, ox+0-51, oy+20+4, "(0,20)");
//  u8g_SetCursorStyle(u8g, 144);
//  u8g_SetCursorPos(u8g, ox+0, oy+20);
//  u8g_DrawCursor(u8g);
}

/*
  the lower draw cmd is 
  u8g_DrawStr(u8g, 0-1, 40, "ABC");  
  for 8 bit graphics this is identical to
  u8g_DrawStr(u8g, 256-1, 40, "ABC");  
  It is valid and possible that the reference point for a string is outside the display area.
  
*/
void draw_abc_left(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_osb18);
  u8g_DrawStr(u8g, ox+0, oy+20, "ABC");  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+0-51, oy+20+4, "(0,20)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+0, oy+20);
  u8g_DrawCursor(u8g);
  
  u8g_SetFont(u8g, u8g_font_osb18);
  u8g_DrawStr(u8g, ox+0-1, oy+40, "ABC");  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+0-1-63, oy+40+4, "(255,40)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+0-1, oy+40);
  u8g_DrawCursor(u8g);
  
}

void draw_box(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);

  u8g_DrawBox(u8g, ox+10, oy+12, 20, 30);  
  draw_v_measure(u8g, ox+10+20+3, oy+12, 30);
  draw_h_measure(u8g, ox+10, oy+12+30+3, 20);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+10-57, oy+12+4, "(10,12)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+10, oy+12);
  u8g_DrawCursor(u8g);  
}

void draw_frame(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);

  u8g_DrawFrame(u8g, ox+10, oy+12, 30, 20);  
  draw_v_measure(u8g, ox+10+30+3, oy+12, 20);
  draw_h_measure(u8g, ox+10, oy+12+20+3, 30);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+10-57, oy+12+4, "(10,12)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+10, oy+12);
  u8g_DrawCursor(u8g);  
}

void draw_pixel(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);

  u8g_DrawPixel(u8g, ox+14, oy+23);  
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+14+3, oy+23+4, "(14,23)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+10, oy+23);
  //u8g_DrawCursor(u8g);  
}


const uint8_t rook_bitmap[] = {
  0x00,         // 00000000 
  0x55,         // 01010101
  0x7f,          // 01111111
  0x3e,         // 00111110
  0x3e,         // 00111110 
  0x3e,         // 00111110
  0x3e,         // 00111110 
  0x7f           // 01111111
};

void draw_bitmap(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  u8g_DrawBitmap(u8g, ox, oy, 1, 8, rook_bitmap);
}

void draw_clear_pixel(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);

  u8g_DrawBox(u8g, ox+10, oy+12, 20, 30);  
  draw_v_measure(u8g, ox+10+20+3, oy+12, 30);
  draw_h_measure(u8g, ox+10, oy+12+30+3, 20);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+10-57, oy+12+4, "(10,12)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+10, oy+12);
  u8g_DrawCursor(u8g);  
  
  u8g_SetColorIndex(u8g, 0);
  u8g_DrawPixel(u8g, ox+28, oy+14);  

  u8g_SetColorIndex(u8g, 1);
  u8g_DrawStr(u8g, ox+28+10, oy+14+4, "(28,14)");

}


void draw_rotate_b(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_osb18);
  u8g_DrawStr(u8g, ox+20, oy+30, "B");  
  u8g_DrawStr90(u8g, ox+20, oy+30, "B");  
  u8g_DrawStr180(u8g, ox+20, oy+30, "B");  
  u8g_DrawStr270(u8g, ox+20, oy+30, "B");  
  u8g_SetFont(u8g, u8g_font_6x10);
  
  u8g_DrawStr(u8g, ox+20-63, oy+30+4, "(20,30)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+20, oy+30);
  u8g_DrawCursor(u8g);
  
  
}

void draw_minbox_abcdefg(u8g_t *u8g)
{
  u8g_uint_t tx, ty, tw, th;
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);

  u8g_SetFont(u8g, u8g_font_osb18);
  tx = ox+4;
  ty = oy+26;
  u8g_DrawStr(u8g, tx, ty, "abcdefg");
  u8g_GetStrMinBox(u8g, "abcdefg", &tx, &ty, &tw, &th);

  u8g_DrawFrame(u8g, tx, ty, tw, th);

  tx = ox+4;
  ty = oy+54;
  u8g_DrawStr(u8g, tx, ty, "abcdefg");
  u8g_GetStrMinBox(u8g, "abcdefg", &tx, &ty, &tw, &th);

  u8g_DrawPixel(u8g, tx, ty);
  u8g_DrawPixel(u8g, tx+tw-1, ty);
  u8g_DrawPixel(u8g, tx, ty+th-1);
  u8g_DrawPixel(u8g, tx+tw-1, ty+th-1);  
}

void draw_minbox_ace(u8g_t *u8g)
{
  u8g_uint_t tx, ty, tw, th;
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);

  u8g_SetFont(u8g, u8g_font_osb18);
  
  tx = ox+4;
  ty = oy+26;
  u8g_DrawStr(u8g, tx, ty, "ace");
  u8g_GetStrMinBox(u8g, "ace", &tx, &ty, &tw, &th);

  u8g_DrawFrame(u8g, tx, ty, tw, th);

  tx = ox+4;
  ty = oy+54;
  u8g_DrawStr(u8g, tx, ty, "ace");
  u8g_GetStrMinBox(u8g, "ace", &tx, &ty, &tw, &th);

  u8g_DrawPixel(u8g, tx, ty);
  u8g_DrawPixel(u8g, tx+tw-1, ty);
  u8g_DrawPixel(u8g, tx, ty+th-1);
  u8g_DrawPixel(u8g, tx+tw-1, ty+th-1);


  tx = ox+4+50;
  ty = oy+26;
  u8g_DrawStr(u8g, tx, ty, "ace A");
  u8g_GetStrAMinBox(u8g, "ace", &tx, &ty, &tw, &th);

  u8g_DrawFrame(u8g, tx, ty, tw, th);

  tx = ox+4+50;
  ty = oy+54;
  u8g_DrawStr(u8g, tx, ty, "ace A");
  u8g_GetStrAMinBox(u8g, "ace", &tx, &ty, &tw, &th);

  u8g_DrawPixel(u8g, tx, ty);
  u8g_DrawPixel(u8g, tx+tw-1, ty);
  u8g_DrawPixel(u8g, tx, ty+th-1);
  u8g_DrawPixel(u8g, tx+tw-1, ty+th-1);

}

void draw_pl_full(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  u8g_SetColorIndex(u8g, 1);
  draw_common_simple(u8g, ox, oy, w, h);

  u8g_DrawBox(u8g, ox+10, oy+12, 20, 38);  
  u8g_SetFont(u8g, u8g_font_osb35);
  u8g_DrawStr(u8g, ox+40, oy+50, "A");
  u8g_SetColorIndex(u8g, 0);
  u8g_DrawPixel(u8g, ox+28, oy+14);  
}

void draw_pl_upper(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  u8g_SetColorIndex(u8g, 1);
  draw_common_simple(u8g, ox, oy, w, h);

  u8g_DrawBox(u8g, ox+10, oy+12, 20, 38);  
  u8g_SetFont(u8g, u8g_font_osb35);
  u8g_DrawStr(u8g, ox+40, oy+50, "A");
  u8g_SetColorIndex(u8g, 0);
  u8g_DrawPixel(u8g, ox+28, oy+14);  
  u8g_DrawBox(u8g, ox, oy, w, h/2);  
}

void draw_pl_lower(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  u8g_SetColorIndex(u8g, 1);
  draw_common_simple(u8g, ox, oy, w, h);

  u8g_DrawBox(u8g, ox+10, oy+12, 20, 38);  
  u8g_SetFont(u8g, u8g_font_osb35);
  u8g_DrawStr(u8g, ox+40, oy+50, "A");
  u8g_SetColorIndex(u8g, 0);
  u8g_DrawPixel(u8g, ox+28, oy+14);  
  u8g_DrawBox(u8g, ox, oy+h/2, w, h/2);  
}

void draw_str_pixel_width(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_osb26);
  u8g_DrawStr(u8g, ox+3, oy+30, "!AgI");
  
  draw_h_measure(u8g, ox+3+2, oy+39, u8g_GetStrPixelWidth(u8g, "!AgI"));
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+3-51, oy+30+4, "(3,30)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+3, oy+30);
  u8g_DrawCursor(u8g);
}

void draw_str_width(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_osb26);
  u8g_DrawStr(u8g, ox+3, oy+30, "!AgI");
  
  draw_h_measure(u8g, ox+3, oy+39, u8g_GetStrWidth(u8g, "!AgI"));
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+3-51, oy+30+4, "(3,30)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+3, oy+30);
  u8g_DrawCursor(u8g);
}

void draw_str_bbx(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  int m;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_SetFont(u8g, u8g_font_osb26);
  u8g_DrawStr(u8g, ox+3, oy+30, "!AgI");
  /* x-1, because the reference point is one pixel to the left */
  u8g_DrawFrame(u8g, ox+3-1, oy+30-u8g_GetFontAscent(u8g)-1, u8g_GetStrWidth(u8g, "!AgI")+2, u8g_GetFontAscent(u8g)-u8g_GetFontDescent(u8g)+2) ;
  
  draw_h_measure(u8g, ox+3, oy+43, u8g_GetStrWidth(u8g, "!AgI"));

  u8g_SetFont(u8g, u8g_font_osb26);
  m = u8g_GetFontAscent(u8g)-u8g_GetFontDescent(u8g);
  draw_v_measure(u8g, ox+77, oy+30-u8g_GetFontAscent(u8g), m);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+3-51, oy+30+4, "(3,30)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+3, oy+30);
  u8g_DrawCursor(u8g);
}

void draw_str_bbx_top(u8g_t *u8g)
{
  char s[] = "AgI";
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  

  draw_common(u8g, ox, oy, w, 64);
  
  u8g_SetFont(u8g, u8g_font_osb26);
  u8g_SetFontRefHeightText(u8g);
  u8g_SetFontPosTop(u8g);
  
  h = u8g_GetFontAscent(u8g)-u8g_GetFontDescent(u8g);

  u8g_DrawStr(u8g, ox+3, oy+10, s);
  /* x-1, because the reference point is one pixel to the left */
  u8g_DrawFrame(u8g, ox+3-1, oy+10, u8g_GetStrWidth(u8g, s)+2, h+2) ;
  
  draw_h_measure(u8g, ox+3, oy+50, u8g_GetStrWidth(u8g, s));

  u8g_SetFont(u8g, u8g_font_osb26);
  draw_v_measure(u8g, ox+u8g_GetStrWidth(u8g, s)+8, oy+10+1, h);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+3-51, oy+10+4, "(3,10)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+3, oy+10);
  u8g_DrawCursor(u8g);
}

void draw_str_bbx_top2(u8g_t *u8g)
{
  char s[] = "(AgI)";
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  

  draw_common(u8g, ox, oy, w, 64);
  
  u8g_SetFont(u8g, u8g_font_gdr25);
  u8g_SetFontRefHeightExtendedText(u8g);
  //u8g_SetFontRefHeightText(u8g);
  u8g_SetFontPosTop(u8g);
  
  h = u8g_GetFontAscent(u8g)-u8g_GetFontDescent(u8g);

  u8g_DrawStr(u8g, ox+3, oy+10, s);
  /* x-1, because the reference point is one pixel to the left */
  u8g_DrawFrame(u8g, ox+3-1, oy+10, u8g_GetStrWidth(u8g, s)+2, h+2) ;
  
  draw_h_measure(u8g, ox+3, oy+10+h+4, u8g_GetStrWidth(u8g, s));

  u8g_SetFont(u8g, u8g_font_osb26);
  draw_v_measure(u8g, ox+u8g_GetStrWidth(u8g, s)+6, oy+10+1, h);
  
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+3-51, oy+10+4, "(3,10)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+3, oy+10);
  u8g_DrawCursor(u8g);
}

#define u8g_logo_width 38
#define u8g_logo_height 24
static unsigned char u8g_logo_bits[] = {
   0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0xe0,
   0xff, 0xff, 0x3f, 0xe3, 0xe1, 0xff, 0xff, 0x3f, 0xf3, 0xf1, 0xff, 0xff,
   0x3f, 0xf3, 0xf1, 0xfe, 0xbf, 0x37, 0xf3, 0x11, 0x1c, 0x1f, 0x30, 0xf3,
   0x01, 0x08, 0x8c, 0x20, 0xf3, 0x01, 0x00, 0xc0, 0x39, 0xf3, 0x81, 0xc7,
   0xc1, 0x39, 0xf3, 0xc1, 0xc7, 0xc9, 0x38, 0xf3, 0xc1, 0xc3, 0x19, 0x3c,
   0xe3, 0x89, 0x01, 0x98, 0x3f, 0xc7, 0x18, 0x00, 0x08, 0x3e, 0x0f, 0x3c,
   0x70, 0x1c, 0x30, 0x3f, 0xff, 0xfc, 0x87, 0x31, 0xff, 0xff, 0xbf, 0xc7,
   0x23, 0x01, 0x00, 0x00, 0xc6, 0x23, 0x03, 0x00, 0x00, 0x0e, 0x30, 0xff,
   0xff, 0x3f, 0x1f, 0x3c, 0xff, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0x3f,
   0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f };

void draw_xbm(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  draw_common(u8g, ox, oy, w, h);
  
  u8g_DrawXBM(u8g, ox+0, oy+0, u8g_logo_width, u8g_logo_height, u8g_logo_bits);  
  
}

void draw_menu(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  uint8_t i;
  u8g_uint_t d;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  char *menu_strings[4] = { "First Line", "Second Item", "3333333", "abcdefg" };

  u8g_SetDefaultForegroundColor(u8g);
  draw_common(u8g, ox, oy, w, h);
  
  

  u8g_SetFont(u8g, u8g_font_6x13);
  u8g_SetFontRefHeightText(u8g);
  u8g_SetFontPosTop(u8g);
  
  h = u8g_GetFontAscent(u8g)-u8g_GetFontDescent(u8g);
  for( i = 0; i < 4; i++ )
  {
    d = (w-u8g_GetStrWidth(u8g, menu_strings[i]))/2;
    u8g_SetDefaultForegroundColor(u8g);
    if ( i == 3 )
    {
      u8g_DrawBox(u8g, 0+ox, i*h+1+oy, w, h);
      u8g_SetDefaultBackgroundColor(u8g);
    }
    u8g_DrawStr(u8g, d+ox, i*h+oy, menu_strings[i]);
  }
}

void draw_line(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  u8g_SetDefaultForegroundColor(u8g);
  draw_common(u8g, ox, oy, w, h);
  
  u8g_DrawLine(u8g, ox+7,oy+10, ox+40, oy+55);
  
  u8g_SetFont(u8g, u8g_font_6x13);
  u8g_SetFontRefHeightText(u8g);
  u8g_SetFontPosTop(u8g);

  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawStr(u8g, ox+7-51, oy+10+4, "(7,10)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+7, oy+10);
  u8g_DrawCursor(u8g);
  
  u8g_DrawStr(u8g, ox+40-57, oy+55+4, "(40,55)");
  u8g_SetCursorPos(u8g, ox+40, oy+55);
  u8g_DrawCursor(u8g);
}

void draw_scale(u8g_t *u8g) 
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  u8g_SetDefaultForegroundColor(u8g);
  draw_common(u8g, ox, oy, w, h);
  
  // graphic commands to redraw the complete screen should be placed here  
  u8g_SetFont(u8g, u8g_font_unifont);
  u8g_SetFontPosTop(u8g);
  u8g_DrawStr(u8g, ox+0, oy+1, "Hello");
  u8g_DrawHLine(u8g, ox+0, oy+1+14, 40);
  u8g_SetScale2x2(u8g);					// Scale up all draw procedures
  u8g_DrawStr(u8g, ox/2+0, oy/2+12, "Hello");			// actual display position is (0,24)
  u8g_DrawHLine(u8g, ox/2+0, oy/2+12+14, 40);		// All other procedures are also affected
  u8g_UndoScale(u8g);					// IMPORTANT: Switch back to normal mode
}

void draw_triangle(u8g_t *u8g)
{
  u8g_uint_t ox, oy, w, h;
  ox = 80;
  oy = 80;
  w = 128;
  h = 64;

  u8g_SetDefaultForegroundColor(u8g);
  draw_common(u8g, ox, oy, w, h);

  u8g_DrawTriangle(u8g, ox+14,oy+9, ox+45,oy+32, ox+9,oy+42);

  u8g_DrawTriangle(u8g, ox+14,oy+55, ox+45,oy+32+1, ox+9,oy+42+1);
  
  
  u8g_SetFont(u8g, u8g_font_6x13);
  u8g_SetFontRefHeightText(u8g);
  u8g_SetFontPosTop(u8g);

  u8g_SetFont(u8g, u8g_font_6x10);
  
  u8g_DrawStr(u8g, ox+14-51, oy+9+4, "(14,9)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+14-1, oy+9);
  u8g_DrawCursor(u8g);

  u8g_DrawStr(u8g, ox+9-51, oy+43+4, "(9,43)");
  u8g_SetCursorStyle(u8g, 144);
  u8g_SetCursorPos(u8g, ox+9-1, oy+43);
  u8g_DrawCursor(u8g);

  u8g_DrawStr(u8g, ox+45+17, oy+32+4, "(45,32)");
  u8g_SetCursorStyle(u8g, 142);
  u8g_SetCursorPos(u8g, ox+45+1, oy+32);
  u8g_DrawCursor(u8g);

}


int main(void)
{

  create_picture(draw_hello_world, "hello_world");
  create_picture(draw_display, "display");
  create_picture(draw_text_abc, "text_abc");
  create_picture(draw_circle, "circle");
  create_picture(draw_circle_ur, "circle_ur");
  
  create_picture(draw_abc_left, "abc_left");
  create_picture(draw_text_abc_top, "abc_top");
  
  
  create_picture(draw_height_text, "height_text");
  create_picture(draw_linespacing_text, "linespacing_text");
  
  create_picture(draw_height_extended_text, "height_ex_text");
  create_picture(draw_top_height_extended_text, "top_height_ex_text");
  create_picture(draw_linespacing_xtext, "linespacing_ex_text");
  create_picture(draw_height_all, "height_all");
  
  create_picture(draw_rotate_b, "rotate_b");
  create_picture(draw_box, "box");
  create_picture(draw_frame, "frame");
  create_picture(draw_pixel, "pixel");
  create_picture(draw_bitmap, "bitmap");
  create_picture(draw_clear_pixel, "clear_pixel");  
  
  create_picture(draw_ascent, "ascent");  
  create_picture(draw_descent, "descent");  
  
  create_picture(draw_minbox_abcdefg, "minbox_abcdefg");
  create_picture(draw_minbox_ace, "minbox_ace");

  create_picture(draw_pl_full, "pl_full");
  create_picture(draw_pl_lower, "pl_lower");
  create_picture(draw_pl_upper, "pl_upper");
  
  create_picture(draw_text_abc_rot, "rot0");
  
  create_picture(draw_str_pixel_width, "str_pixel_width");
  create_picture(draw_str_width, "str_width");
  create_picture(draw_str_bbx, "str_bbx");
  create_picture(draw_str_bbx_top, "str_bbx_top");
  create_picture(draw_str_bbx_top2, "str_bbx_top2");
  
  create_picture(draw_xbm, "xbm");
  create_picture(draw_menu, "menu");
  create_picture(draw_line, "line");
  
  create_picture(draw_scale, "scale2x2");
  
  
  create_picture_rot90(draw_text_abc_rot90, "rot90");
  create_picture(draw_triangle, "triangle");
  
  return 0;
}

