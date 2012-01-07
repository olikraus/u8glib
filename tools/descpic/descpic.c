

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

void draw_v_measure(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t h)
{
  char buf[20];
  u8g_SetFont(u8g, u8g_font_6x10);
  u8g_DrawHLine(u8g, x-1, y, 3);
  u8g_DrawHLine(u8g, x-1, y+h-1, 3);
  u8g_DrawVLine(u8g, x, y, h);
  sprintf(buf, "%d", h);
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


int main(void)
{
  create_picture(draw_display, "display");
  create_picture(draw_text_abc, "text_abc");
  create_picture(draw_abc_left, "abc_left");
  create_picture(draw_rotate_b, "rotate_b");
  create_picture(draw_box, "box");
  create_picture(draw_frame, "frame");
  create_picture(draw_pixel, "pixel");
  create_picture(draw_bitmap, "bitmap");
  create_picture(draw_clear_pixel, "clear_pixel");  
  create_picture(draw_minbox_abcdefg, "minbox_abcdefg");
  create_picture(draw_minbox_ace, "minbox_ace");
  
  create_picture(draw_text_abc_rot, "rot0");
  create_picture_rot90(draw_text_abc_rot90, "rot90");
  return 0;
}