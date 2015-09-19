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

/*
  Prototype:
    uint8_t u8g2_display_DrawTile(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t cnt, uint8_t *tile_ptr)
  Description:
    Send U8G2_MSG_DISPLAY_DRAW_TILE to the display callback. 
    A tile is a sequence of 8 bytes (64 bits) and represents a 8x8 monochrome bitmap.
    The lowest bit of the first byte is the upper left corner
    The highest bit of the first byte is the lower left corner
    The lowest bit of the last byte is the upper right corner
    The highest bit of the last byte is the lower left corner
    
  Arguments:
    u8g2		Pointer to the u8g2 object
    x			X position of the tile
    y			Y position of the tile
    cnt		Number of tiles
    tile_ptr		Pointer to "cnt" tiles. 
  Returns:
    0, if not successful or not supported
  See also:
  Example:

*/

uint8_t u8g2_display_DrawTile(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t cnt, uint8_t *tile_ptr)
{
  u8g2_tile_t tile;
  tile.x_pos = x;
  tile.y_pos = y;
  tile.cnt = cnt;
  tile.tile_ptr = tile_ptr;
  return u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_DRAW_TILE, 1, (void *)&tile);
}

void u8g2_display_Init(u8g2_t *u8g2)
{
  u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_INIT, 0, NULL);  
}

void u8g2_display_PowerUp(u8g2_t *u8g2)
{
  u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_POWER_UP, 0, NULL);  
}

void u8g2_display_PowerDown(u8g2_t *u8g2)
{
  u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_POWER_DOWN, 0, NULL);  
}

void u8g2_display_SetFlipMode(u8g2_t *u8g2, uint8_t mode)
{
  u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_SET_FLIP_MODE, mode, NULL);  
}


void u8g2_display_ClearScreen(u8g2_t *u8g2)
{
  uint8_t buf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  u8g2_tile_t tile;
  uint8_t h;

  tile.x_pos = 0;
  tile.cnt = 1;
  tile.tile_ptr = buf;
  
  h = u8g2->display_info->tile_height;
  tile.y_pos = 0;
  do
  {
    u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_DRAW_TILE, u8g2->display_info->tile_width, (void *)&tile);
    tile.y_pos++;
  } while( tile.y_pos < h );
}

