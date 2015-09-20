/*
  
  u8g2_display.c
  
  Abstraction layer for the graphics controller.
  Main goal is the placement of a 8x8 pixel block on the display.
  
*/


#include "u8g2.h"


/*==========================================*/
/* internal library function */
/*
  this is a helper function for the U8G2_MSG_DISPLAY_INIT function.
  It can be called within the display callback function to carry out the usual standard tasks.
  
*/
void u8g2_d_helper_display_init(u8g2_t *u8g2, const u8g2_display_info_t *display_info)
{
      /* 1) set display info struct */
      u8g2->display_info = display_info;
      u8g2->x_offset = u8g2->display_info->default_x_offset;
    
      /* 2) apply port directions to the GPIO lines and apply default values for the IO lines*/
      u8g2_gpio_Init(u8g2);
      u8g2_cad_Init(u8g2);

      /* 3) do reset */
      u8g2_gpio_SetReset(u8g2, 1);
      u8g2_gpio_Delay(u8g2, U8G2_MSG_DELAY_MILLI, u8g2->display_info->reset_pulse_width_ms);
      u8g2_gpio_SetReset(u8g2, 0);
      u8g2_gpio_Delay(u8g2, U8G2_MSG_DELAY_MILLI, u8g2->display_info->reset_pulse_width_ms);
      u8g2_gpio_SetReset(u8g2, 1);
      u8g2_gpio_Delay(u8g2, U8G2_MSG_DELAY_MILLI, u8g2->display_info->post_reset_wait_ms);
}    

/*==========================================*/
/* official functions */

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

void u8g2_display_SetPowerSave(u8g2_t *u8g2, uint8_t is_enable)
{
  u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_SET_POWER_SAVE, is_enable, NULL);  
}

void u8g2_display_SetFlipMode(u8g2_t *u8g2, uint8_t mode)
{
  u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_SET_FLIP_MODE, mode, NULL);  
}

void u8g2_display_SetContrast(u8g2_t *u8g2, uint8_t value)
{
  u8g2->display_cb(u8g2, U8G2_MSG_DISPLAY_SET_CONTRAST, value, NULL);  
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

