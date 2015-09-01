/*
  
  u8g2_display.c
  
  Abstraction layer for the graphics controller.
  Main goal is the placement of a 8x8 pixel block on the display.
  
*/

/*
template

uint8_t u8g2_d_xyz(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8G2_MSG_DISPLAY_INIT:
      break;
    case U8G2_MSG_DISPLAY_POWER_DOWN:
      break;
    case U8G2_MSG_DISPLAY_POWER_UP:
      break;
    case U8G2_MSG_DISPLAY_SET_CONTRAST:
      break;
    case U8G2_MSG_DISPLAY_DRAW_TILE:
      break;
    case U8G2_MSG_DISPLAY_GET_LAYOUT:
      break;
    default:
      break;
  }
  return 1;
}
*/

#include "u8g2.h"

uint8_t u8g2_display_DrawTile(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t cnt, uint8_t *tile_ptr)
{
  u8g2_tile_t tile;
  tile.x_pos = x;
  tile.y_pos = y;
  tile.cnt = cnt;
  tile.tile_ptr = tile_ptr;
  return u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_DRAW_TILE, 0, (void *)&tile);
}

void u8g2_display_Init(u8g2_t *u8g2)
{
  u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_INIT, 0, NULL);  
}
