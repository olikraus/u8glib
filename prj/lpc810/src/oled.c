

#include "sys.h"

#define I2C_SLA         (0x3c*2)
//#define I2C_CMD_MODE  0x080
#define I2C_CMD_MODE    0x000
#define I2C_DATA_MODE   0x040


#define WIDTH 128
#define HEIGHT 64

struct _oled_struct
{
  uint32_t page_start;		/* start row of page */

  uint8_t oled_display_page[WIDTH];
};

typedef struct _oled_struct oled_t;

oled_t oled_o;

/*
  precondition: cnt must be > 0 
  
*/
void __attribute__ ((noinline)) oled_send_cmd_seq(uint32_t cnt, const uint8_t *cmd)
{
  
  i2c_start();
  i2c_write_byte(*cmd);
  i2c_write_byte(I2C_SLA);		// address and 0 for RWn bit  
  i2c_write_byte(I2C_CMD_MODE);
  do
  {
    i2c_write_byte(*cmd);
    cmd++;
    cnt--;
  }while( cnt > 0 );
  i2c_stop();
}

/*
  SSD1306 startup
*/
static const uint8_t oled_init_seq[] = 
{
  0x0ae,				/* display off, sleep mode */
  0x0d5, 0x080,		/* clock divide ratio (0x00=1) and oscillator frequency (0x8) */
  0x0a8, 0x03f,		/* */

  0x0d3, 0x000,		/*  */

  0x040,				/* start line */
  
  0x08d, 0x014,		/* [2] charge pump setting (p62): 0x014 enable, 0x010 disable */

  0x020, 0x002,		/* 2012-05-27: page addressing mode */
  0x0a1,				/* segment remap a0/a1*/
  0x0c8,				/* c0: scan dir normal, c8: reverse */
  0x0da, 0x012,		/* com pin HW config, sequential com pin config (bit 4), disable left/right remap (bit 5) */
  0x081, 0x0cf,		/* [2] set contrast control */
  0x0d9, 0x0f1,		/* [2] pre-charge period 0x022/f1*/
  0x0db, 0x040,		/* vcomh deselect level */
  
  0x02e,				/* 2012-05-27: Deactivate scroll */ 
  0x0a4,				/* output ram to display */
  0x0a6,				/* none inverted normal display mode */
  0x0af,				/* display on */
};

/*
  SSD1306 shutdown
*/
static const uint8_t oled_shutdown_seq[] = 
{
  0x0ae,				/* display off, sleep mode */
};



void __attribute__ ((noinline)) oled_set_pixel(oled_t *oled, uint32_t x, uint32_t y)
{
  uint8_t *ptr = oled->oled_display_page;
  uint8_t mask;
  
  if ( y < oled->page_start )
    return;
  
  y-=oled->page_start;
  if ( y >= 8 )
    return;
      
  mask = 1 << y;
  ptr += x;
  *ptr |= mask;
}

void __attribute__ ((noinline)) oled_clear_page(oled_t *oled)
{
  uint32_t i = WIDTH;
  
  do
  {
    i--;
    oled->oled_display_page[i] = 0;
  } while( i != 0 );
  
}

void oled_start_page(oled_t *oled)
{
  oled->page_start = 0;
  oled_clear_page(oled);
}

int oled_next_page(oled_t *oled)
{
  oled->page_start+=8;
  oled_clear_page(oled);
  return oled->page_start >= HEIGHT;
}



void __attribute__ ((noinline)) oled_init(void)
{
  i2c_init();
  
  oled_send_cmd_seq(sizeof(oled_init_seq), oled_init_seq);
  oled_send_cmd_seq(sizeof(oled_shutdown_seq), oled_shutdown_seq);  
  oled_start_page(&oled_o);
  do
  {
    oled_set_pixel(&oled_o, 10, 10);
    oled_set_pixel(&oled_o, 11, 11);
  }
  while( oled_next_page(&oled_o) );
}
