
#include "u8g2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FACTOR 3
#define DEFAULT_WIDTH (FACTOR*128)
#define DEFAULT_HEIGHT (FACTOR*64)


static uint16_t tga_width;
static uint16_t tga_height;
static uint8_t *tga_data = NULL;
uint8_t tga_r = 0;
uint8_t tga_g = 0;
uint8_t tga_b = 0;

int tga_init(uint16_t w, uint16_t h)
{
  tga_width = 0;
  tga_height = 0;
  if ( tga_data != NULL )
    free(tga_data);
  tga_data = (uint8_t *)malloc(w*h*3);
  if ( tga_data == NULL )
    return 0;
  tga_width = w;
  tga_height = h;
  memset(tga_data, 255, tga_width*tga_height*3);
  return 1;
}

void tga_set_pixel(uint16_t x, uint16_t y)
{
  uint8_t *p;
  p = tga_data + (tga_height-y-1)*tga_width*3 + x*3;
  *p++ = tga_b;
  *p++ = tga_g;
  *p++ = tga_r;
}

void tga_clr_pixel(uint16_t x, uint16_t y)
{
  uint8_t *p;
  p = tga_data + (tga_height-y-1)*tga_width*3 + x*3;
  *p++ = 255;
  *p++ = 255;
  *p++ = 255;
}

void tga_set_8pixel(int x, int y, uint8_t pixel)
{
  int cnt = 8;
  while( cnt > 0 )
  {
    if ( (pixel & 1) != 0 )
    {
      tga_set_pixel(x,y);
    }
    else
    {
      tga_clr_pixel(x,y);
    }
    pixel >>= 1;
    y++;
    cnt--;
  }
}

void tga_set_multiple_8pixel(int x, int y, int cnt, uint8_t *pixel)
{
  uint8_t b;
  while( cnt > 0 )
  {
    b = *pixel;
    tga_set_8pixel(x, y, b);
    x++;
    pixel++;
    cnt--;
  }
}



void tga_write_byte(FILE *fp, uint8_t byte)
{
  fputc(byte, fp);
}

void tga_write_word(FILE *fp, uint16_t word)
{
  tga_write_byte(fp, word&255);
  tga_write_byte(fp, word>>8);
}

void tga_save(const char *name)
{
  FILE *fp;
  if ( tga_data == NULL )
    return;
  
  fp = fopen(name, "wb");
  if ( fp != NULL )
  {
    tga_write_byte(fp, 0);		/* no ID */
    tga_write_byte(fp, 0);		/* no color map */
    tga_write_byte(fp, 2);		/* uncompressed true color */
    tga_write_word(fp, 0);		
    tga_write_word(fp, 0);		
    tga_write_byte(fp, 0);		
    tga_write_word(fp, 0);		/* x origin */
    tga_write_word(fp, 0);		/* y origin */
    tga_write_word(fp, tga_width);		/* width */
    tga_write_word(fp, tga_height);		/* height */
    tga_write_byte(fp, 24);		/* color depth */
    tga_write_byte(fp, 0);		
    fwrite(tga_data, tga_width*tga_height*3, 1, fp);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    fwrite("TRUEVISION-XFILE.", 18, 1, fp);
    fclose(fp);
  }
}


static const u8x8_display_info_t u8x8_tga_128x64_info =
{
  /* chip_enable_level = */ 0,
  /* chip_disable_level = */ 1,
  
  /* post_chip_enable_wait_ns = */ 0,
  /* pre_chip_disable_wait_ns = */ 0,
  /* reset_pulse_width_ms = */ 0, 
  /* post_reset_wait_ms = */ 0, 
  /* sda_setup_time_ns = */ 0,		
  /* sck_pulse_width_ns = */ 0,
  /* sck_takeover_edge = */ 1,		
  /* i2c_bus_clock_100kHz = */ 0,
  /* data_setup_time_ns = */ 0,
  /* write_pulse_width_ns = */ 0,
  /* tile_width = */ 16,
  /* tile_hight = */ 8,
#if U8X8_DEFAULT_FLIP_MODE == 0 
  /* default_x_offset = */ 0,
#else
  /* default_x_offset = */ 0,
#endif
};


uint8_t u8x8_d_tga(u8x8_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  uint8_t x, y, c;
  uint8_t *ptr;
  switch(msg)
  {
    case U8X8_MSG_DISPLAY_SETUP:
      u8x8_d_helper_display_setup(u8g2, &u8x8_tga_128x64_info);
      break;
    case U8X8_MSG_DISPLAY_INIT:
      u8x8_d_helper_display_init(u8g2);
      if ( tga_data == NULL )
	tga_init(DEFAULT_WIDTH, DEFAULT_HEIGHT);
      break;
    case U8X8_MSG_DISPLAY_SET_POWER_SAVE:
      break;
    case U8X8_MSG_DISPLAY_SET_FLIP_MODE:
      break;
    case U8X8_MSG_DISPLAY_SET_CONTRAST:
      break;
    case U8X8_MSG_DISPLAY_DRAW_TILE:
      x = ((u8x8_tile_t *)arg_ptr)->x_pos;
      x *= 8;
      x += u8g2->x_offset;	
    
      y = ((u8x8_tile_t *)arg_ptr)->y_pos;
      y *= 8;
    
      do
      {
	c = ((u8x8_tile_t *)arg_ptr)->cnt;
	ptr = ((u8x8_tile_t *)arg_ptr)->tile_ptr;
	tga_set_multiple_8pixel(x, y, c*8, ptr);
	arg_int--;
      } while( arg_int > 0 );

      break;
    default:
      return 0;
  }
  return 1;
}


void u8x8_Setup_TGA(u8x8_t *u8x8)
{
  /* setup defaults */
  u8x8_SetupDefaults(u8x8);
  
  /* setup specific callbacks */
  u8x8->display_cb = u8x8_d_tga;

  /* setup display info */
  u8x8_display_Setup(u8x8);  
}

void u8g2_Setup_TGA(u8g2_t *u8g2, const u8g2_cb_t *u8g2_cb)
{
  
  static uint8_t buf[128*8];
  
  u8x8_Setup_TGA(u8g2_GetU8x8(u8g2));
  u8g2_Setup(u8g2, buf, 8, u8g2_cb);
}
