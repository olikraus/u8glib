
#include "u8g2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FACTOR 3
#define XOFFSET (FACTOR*32)
#define YOFFSET (FACTOR*32)
#define DEFAULT_WIDTH (FACTOR*128)
#define DEFAULT_HEIGHT (FACTOR*64)


static uint16_t tga_width;
static uint16_t tga_height;
static uint8_t *tga_data = NULL;
uint8_t tga_r = 0;
uint8_t tga_g = 0;
uint8_t tga_b = 0;

uint8_t tga_desc_r = 0;
uint8_t tga_desc_g = 0;
uint8_t tga_desc_b = 255;

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

void tga_set_pixel(uint16_t x, uint16_t y, uint16_t f)
{
  uint8_t *p;
  uint16_t xx,yy;
  for( yy = y; yy < y+f; yy++ )
  {
    for( xx = x; xx < x+f; xx++ )
    {
      if ( yy < tga_height && xx < tga_width )
      {
	//printf ("(%d %d) ", xx, yy);
	p = tga_data + (tga_height-yy-1)*tga_width*3 + xx*3;
	*p++ = tga_b;
	*p++ = tga_g;
	*p++ = tga_r;
      }
    }
  }
}

void tga_clr_pixel(uint16_t x, uint16_t y, uint16_t f)
{
  uint8_t *p;
  uint16_t xx,yy;
  for( yy = y; yy < y+f; yy++ )
  {
    for( xx = x; xx < x+f; xx++ )
    {
      
      p = tga_data + (tga_height-yy-1)*tga_width*3 + xx*3;
      *p++ = 255;
      *p++ = 255;
      *p++ = 255;
    }
  }
}

void tga_set_8pixel(int x, int y, uint8_t pixel, uint16_t f)
{
  int cnt = 8;
  while( cnt > 0 )
  {
    if ( (pixel & 1) != 0 )
    {
      tga_set_pixel(x,y, f);
    }
    else
    {
      tga_clr_pixel(x,y, f);
    }
    pixel >>= 1;
    y+=f;
    cnt--;
  }
}

void tga_set_multiple_8pixel(int x, int y, int cnt, uint8_t *pixel, uint16_t f)
{
  uint8_t b;
  while( cnt > 0 )
  {
    b = *pixel;
    tga_set_8pixel(x, y, b, f);
    x+=f;
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
  
  printf("tga_save: File %s with %dx%d pixel\n", name, tga_width, tga_height);
  
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

/*==========================================*/
/* tga description procedures */


static const u8x8_display_info_t u8x8_tga_desc_info =
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
  /* tile_width = */ (2*XOFFSET+DEFAULT_WIDTH)/8,
  /* tile_hight = */ (2*YOFFSET+DEFAULT_HEIGHT)/8,
#if U8X8_DEFAULT_FLIP_MODE == 0 
  /* default_x_offset = */ 0,
#else
  /* default_x_offset = */ 0,
#endif
};


uint8_t u8x8_d_tga_desc(u8x8_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  u8g2_uint_t x, y, c;
  uint8_t *ptr;
  switch(msg)
  {
    case U8X8_MSG_DISPLAY_SETUP:
      u8x8_d_helper_display_setup(u8g2, &u8x8_tga_desc_info);
      break;
    case U8X8_MSG_DISPLAY_INIT:
      u8x8_d_helper_display_init(u8g2);
      if ( tga_data == NULL )
	tga_init(2*XOFFSET+DEFAULT_WIDTH, 2*YOFFSET+DEFAULT_HEIGHT);
      break;
    case U8X8_MSG_DISPLAY_SET_POWER_SAVE:
      break;
    case U8X8_MSG_DISPLAY_SET_FLIP_MODE:
      break;
    case U8X8_MSG_DISPLAY_SET_CONTRAST:
      break;
    case U8X8_MSG_DISPLAY_DRAW_TILE:
      
      tga_r = tga_desc_r;
      tga_g = tga_desc_g;
      tga_b = tga_desc_b;
    
      x = ((u8x8_tile_t *)arg_ptr)->x_pos;
      //printf("U8X8_MSG_DISPLAY_DRAW_TILE x=%d, ", x);
      x *= 8;
      x += u8g2->x_offset;	
    
      y = ((u8x8_tile_t *)arg_ptr)->y_pos;
      //printf("y=%d, c=%d\n", y, ((u8x8_tile_t *)arg_ptr)->cnt);
      y *= 8;
    
      do
      {
	c = ((u8x8_tile_t *)arg_ptr)->cnt;
	ptr = ((u8x8_tile_t *)arg_ptr)->tile_ptr;
	tga_set_multiple_8pixel(x, y, c*8, ptr, 1);
	arg_int--;
      } while( arg_int > 0 );

      break;
    default:
      return 0;
  }
  return 1;
}


void u8x8_Setup_TGA_DESC(u8x8_t *u8x8)
{
  /* setup defaults */
  u8x8_SetupDefaults(u8x8);
  
  /* setup specific callbacks */
  u8x8->display_cb = u8x8_d_tga_desc;

  /* setup display info */
  u8x8_display_Setup(u8x8);  
}

void u8g2_Setup_TGA_DESC(u8g2_t *u8g2, const u8g2_cb_t *u8g2_cb)
{
  static uint8_t buf[(XOFFSET+DEFAULT_WIDTH)*8];
  
  u8x8_Setup_TGA_DESC(u8g2_GetU8x8(u8g2));
  u8g2_Setup(u8g2, buf, 1, u8g2_cb);
}

/*==========================================*/
/* tga LCD procedures */


static const u8x8_display_info_t u8x8_tga_lcd_info =
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
  /* tile_width = */ (DEFAULT_WIDTH)/FACTOR/8,
  /* tile_hight = */ (DEFAULT_HEIGHT)/FACTOR/8,
#if U8X8_DEFAULT_FLIP_MODE == 0 
  /* default_x_offset = */ 0,
#else
  /* default_x_offset = */ 0,
#endif
};


uint8_t u8x8_d_tga_lcd(u8x8_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  u8g2_uint_t x, y, c;
  uint8_t *ptr;
  switch(msg)
  {
    case U8X8_MSG_DISPLAY_SETUP:
      u8x8_d_helper_display_setup(u8g2, &u8x8_tga_lcd_info);
      break;
    case U8X8_MSG_DISPLAY_INIT:
      u8x8_d_helper_display_init(u8g2);
      if ( tga_data == NULL )
	tga_init(2*XOFFSET+DEFAULT_WIDTH, 2*YOFFSET+DEFAULT_HEIGHT);
      break;
    case U8X8_MSG_DISPLAY_SET_POWER_SAVE:
      break;
    case U8X8_MSG_DISPLAY_SET_FLIP_MODE:
      break;
    case U8X8_MSG_DISPLAY_SET_CONTRAST:
      break;
    case U8X8_MSG_DISPLAY_DRAW_TILE:

      tga_r = 0;
      tga_g = 0;
      tga_b = 0;
    
      x = ((u8x8_tile_t *)arg_ptr)->x_pos;
      //printf("U8X8_MSG_DISPLAY_DRAW_TILE x=%d, ", x);
      x *= 8;
      x += u8g2->x_offset;
      x *= FACTOR;
      x += XOFFSET;
    
      y = ((u8x8_tile_t *)arg_ptr)->y_pos;
      //printf("y=%d, c=%d\n", y, ((u8x8_tile_t *)arg_ptr)->cnt);
      y *= 8;
      y *= FACTOR;
      y += YOFFSET;
    
      do
      {
	c = ((u8x8_tile_t *)arg_ptr)->cnt;
	ptr = ((u8x8_tile_t *)arg_ptr)->tile_ptr;
	tga_set_multiple_8pixel(x, y, c*8, ptr, FACTOR);
	arg_int--;
      } while( arg_int > 0 );

      break;
    default:
      return 0;
  }
  return 1;
}


void u8x8_Setup_TGA_LCD(u8x8_t *u8x8)
{
  /* setup defaults */
  u8x8_SetupDefaults(u8x8);
  
  /* setup specific callbacks */
  u8x8->display_cb = u8x8_d_tga_lcd;

  /* setup display info */
  u8x8_display_Setup(u8x8);  
}

void u8g2_Setup_TGA_LCD(u8g2_t *u8g2, const u8g2_cb_t *u8g2_cb)
{
  static uint8_t buf[(DEFAULT_WIDTH/FACTOR)*8];
  
  u8x8_Setup_TGA_LCD(u8g2_GetU8x8(u8g2));
  u8g2_Setup(u8g2, buf, 1, u8g2_cb);
}



