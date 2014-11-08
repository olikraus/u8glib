

#include <stddef.h>
#include "sys.h"
#include "oled.h"

#define I2C_SLA         (0x3c*2)
//#define I2C_CMD_MODE  0x080
#define I2C_CMD_MODE    0x000
#define I2C_DATA_MODE   0x040




oled_t oled_o;

/* Adobe helvR14, only uppercase */
/* https://code.google.com/p/u8glib/wiki/fontgroupadobex11 */
const unsigned char helvR14[918] = {
  43,4,3,32,0,0,8,5,0,1,0,44,2,5,11,5,
  1,253,64,17,33,1,45,5,1,8,6,0,5,80,46,2,
  2,8,5,1,0,64,47,5,14,16,5,0,0,163,19,25,
  37,50,74,100,180,1,48,8,13,19,10,1,0,66,99,162,
  66,136,31,73,136,136,216,144,0,49,5,13,12,10,2,0,
  115,80,163,255,0,50,8,13,19,10,1,0,66,114,33,36,
  38,53,180,87,98,7,7,2,51,8,13,22,10,1,0,82,
  114,32,68,36,37,52,69,54,70,68,51,97,67,2,52,9,
  13,26,10,0,0,38,54,69,36,33,35,34,35,162,70,66,
  72,226,224,128,76,78,5,0,53,8,13,22,10,1,0,112,
  113,33,38,102,114,33,51,38,70,68,115,48,82,2,54,8,
  13,22,10,1,0,66,115,33,67,166,98,228,66,136,81,141,
  132,13,9,0,55,8,13,20,10,1,0,240,64,76,74,153,
  148,152,148,152,148,152,42,0,56,8,13,24,10,1,0,66,
  99,49,82,68,36,33,34,98,49,82,68,84,50,97,67,2,
  57,8,13,23,10,1,0,66,99,33,83,196,72,226,100,66,
  76,140,70,226,164,4,0,58,2,10,9,5,1,0,64,76,
  59,2,13,12,5,1,253,64,76,17,33,1,65,12,14,29,
  13,0,0,37,42,73,72,39,34,38,34,37,164,209,65,204,
  193,136,152,136,152,132,32,161,0,66,11,14,32,13,1,0,
  112,16,115,32,34,53,33,38,33,38,33,37,114,32,114,48,
  33,86,199,236,192,226,64,4,0,67,12,14,26,14,1,0,
  84,117,32,50,53,33,87,41,170,233,168,156,196,212,200,129,
  84,13,0,68,12,14,26,14,1,0,112,32,115,48,34,54,
  33,39,33,200,239,36,196,38,14,70,14,100,0,69,10,14,
  20,13,2,0,240,65,160,134,7,18,7,18,130,26,30,28,
  24,70,9,14,18,12,2,0,240,192,78,187,131,136,131,8,
  57,189,3,71,13,14,28,15,1,0,100,117,48,50,54,33,
  88,72,171,236,65,160,132,160,196,216,200,1,145,133,0,72,
  11,14,16,14,1,0,32,199,119,7,15,234,248,78,0,73,
  2,14,9,6,2,0,240,3,74,8,14,16,10,0,0,166,
  63,35,34,42,153,176,33,1,75,12,14,33,13,2,0,32,
  54,33,53,34,52,35,51,36,50,37,49,86,103,38,50,37,
  51,36,52,35,53,34,54,33,55,76,9,14,14,11,1,0,
  32,167,255,221,193,1,1,77,14,14,32,16,1,0,32,74,
  90,104,120,118,16,102,33,36,65,33,36,65,162,132,68,9,
  77,72,12,71,66,68,10,78,11,14,28,14,1,0,32,87,
  102,101,69,33,68,34,67,34,67,35,66,35,66,36,65,229,
  172,78,0,79,13,14,28,15,1,0,84,118,32,51,53,34,
  39,49,87,201,101,221,132,156,200,212,204,129,88,17,0,80,
  10,14,22,13,2,0,112,16,114,32,33,85,198,234,160,226,
  32,68,80,15,1,81,13,15,32,15,1,255,84,118,32,51,
  53,34,39,49,87,201,101,145,196,132,144,132,200,16,205,129,
  88,133,172,4,0,82,11,14,26,14,1,0,112,32,114,48,
  33,86,199,236,192,226,64,68,76,66,76,66,142,59,1,83,
  10,14,24,13,1,0,67,116,16,49,84,86,88,87,184,144,
  172,104,226,32,198,4,0,84,10,14,14,12,1,0,240,192,
  72,80,255,35,0,85,11,14,18,14,1,0,32,199,255,78,
  66,74,228,64,168,6,0,86,12,14,29,13,0,0,32,72,
  40,33,38,34,38,34,38,35,164,87,34,98,34,98,34,114,
  132,148,82,0,87,16,14,42,18,1,0,32,37,69,37,69,
  37,69,68,36,33,67,35,34,19,18,35,162,191,145,16,145,
  16,146,16,145,16,146,8,138,144,26,26,211,13,0,88,11,
  14,30,13,1,0,32,71,39,33,37,50,51,163,74,66,110,
  112,78,66,74,70,102,137,148,132,28,157,0,89,12,14,25,
  13,0,0,32,72,40,33,38,34,38,35,36,52,50,37,34,
  71,41,170,87,0,90,10,14,17,12,1,0,240,192,80,78,
  119,115,58,60,56,48};

/* Logisoso: numbers */
/* https://code.google.com/p/ucglib/wiki/fontgrouplogisoso */
const unsigned char logisoso46[587] = {
  11,5,5,48,23,46,46,30,3,0,232,112,139,122,78,84,
  38,50,13,164,32,226,56,71,56,82,179,216,255,255,255,86,
  147,142,96,36,67,32,5,25,19,153,74,116,30,181,184,3,
  1,49,12,46,24,30,10,0,198,172,156,8,50,146,240,129,
  42,36,195,48,230,255,255,255,31,50,23,46,64,30,3,0,
  232,112,203,114,78,84,38,50,13,164,32,226,56,71,56,82,
  179,216,173,38,29,161,80,134,24,214,241,14,120,188,3,30,
  239,4,143,119,130,199,59,193,227,29,208,128,199,59,224,241,
  78,240,120,39,248,129,63,224,0,51,23,46,60,30,3,255,
  224,31,112,224,241,78,240,120,7,52,224,241,14,104,192,227,
  29,208,128,200,75,220,194,152,197,188,4,34,209,136,71,52,
  255,145,96,29,130,72,71,56,14,18,20,145,12,138,72,6,
  66,13,75,16,0,52,23,46,57,30,3,0,200,128,70,52,
  131,70,52,131,70,52,131,70,52,197,34,154,197,34,154,13,
  3,21,196,56,6,49,142,65,140,99,16,227,20,197,48,70,
  49,140,81,12,243,129,63,224,44,35,154,63,3,0,53,23,
  46,55,30,3,0,224,31,160,162,249,39,14,20,153,137,80,
  163,18,149,72,10,18,142,100,132,35,53,139,181,140,104,190,
  200,44,214,106,210,17,140,100,8,164,32,99,34,83,137,206,
  163,22,119,32,0,54,23,46,64,30,3,0,232,112,139,122,
  78,84,38,50,13,164,32,194,72,70,56,82,179,88,209,124,
  195,64,145,153,8,53,42,81,137,164,32,1,57,71,56,82,
  179,216,127,171,73,71,56,206,33,144,130,140,137,76,37,58,
  143,90,220,129,0,55,23,46,56,30,3,0,224,31,160,84,
  75,25,193,72,71,48,210,17,140,100,68,3,158,160,17,13,
  120,130,70,52,224,9,26,240,12,26,240,4,141,104,192,19,
  52,162,1,79,208,136,6,60,65,3,158,41,0,56,23,46,
  70,30,3,0,232,112,139,122,78,84,38,50,13,164,32,226,
  56,71,56,82,179,216,111,53,233,8,199,57,4,82,144,49,
  17,201,196,138,84,166,129,20,68,28,231,8,71,106,22,251,
  173,38,29,225,56,135,64,10,50,38,50,149,232,60,106,113,
  7,2,0,57,23,46,67,30,3,0,232,112,139,122,78,84,
  38,50,13,164,32,226,56,71,56,82,179,216,127,171,73,71,
  56,14,18,144,146,136,218,160,200,100,34,100,12,35,154,139,
  11,99,22,179,154,116,4,35,25,2,41,200,152,200,84,162,
  243,168,197,29,8,0,58,6,26,21,17,6,6,97,16,69,
  136,134,240,65,90,16,69,136,4,17,0};


/*
  precondition: cnt must be > 0 
  
*/
void __attribute__ ((noinline)) oled_send_seq(uint32_t mode, uint32_t cnt, const uint8_t *cmd)
{
  
  i2c_start();
  i2c_write_byte(I2C_SLA);		// address and 0 for RWn bit    
  i2c_write_byte(mode);		// write mode byte
  do
  {
    i2c_write_byte(*cmd);
    cmd++;
    cnt--;
  }while( cnt > 0 );
  // i2c_stop();
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

uint8_t oled_start_page_seq[] = 
{
 0x010,		/* set upper 4 bit of the col adr to 0 */
  0x000,		/* SSD1306: 0, SH1106. 2, set lower 4 bit of the col adr  */
  0x0b0,		/* select page 0 */
};

static const uint8_t oled_test_seq[] = 
{
  0x0ff,
  0x0ff,
  0x0ff,
  
  0x00f,
  0x00f,
  0x00f,
 };



void __attribute__ ((noinline)) oled_draw_pixel(oled_t *oled, uint32_t x, uint32_t y)
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

void oled_draw_hline(oled_t *oled, uint32_t x, uint32_t y, uint32_t cnt)
{
  while( cnt > 0 )
  {
    oled_draw_pixel(oled, x,y);
    cnt--;
    x++;
  }
}

unsigned __attribute__ ((noinline)) oled_fd_get_bits(oled_t *oled, int cnt)
{
  unsigned val;
  
  val = *(oled->decode_ptr);
  val >>= oled->decode_bit_pos;
  if ( oled->decode_bit_pos + cnt >= 8 )
  {
    oled->decode_ptr++;
    val |= *(oled->decode_ptr) << (8-oled->decode_bit_pos);
    oled->decode_bit_pos -= 8;
  }
  val &= (1<<cnt)-1;
  oled->decode_bit_pos += cnt;
  return val;
}

void __attribute__ ((noinline)) oled_fd_inc(oled_t *oled)
{
  oled->x++;
  if ( oled->x == oled->glyph_width )
  {
    oled->x = 0;
    oled->y++;
  }
}

static void oled_fd_decode(oled_t *oled, unsigned x, unsigned y)
{
  unsigned a, b;
  unsigned i;
  
  /* adjust glyph position */
  x += oled->x_offset;
  y -= oled->y_offset;
  y -= oled->glyph_height;
  
  /* reset local x/y position */
  oled->x = 0;
  oled->y = 0;

  /* init decode algorithm */
  oled->decode_ptr = oled->glyph_data;
  oled->decode_byte_pos = 0;
  oled->decode_bit_pos = 0;
  
  /* decode glyph */
  for(;;)
  {
    a = oled_fd_get_bits(oled, oled->bits_per_0);
    b = oled_fd_get_bits(oled, oled->bits_per_1);
    do
    {
      for( i = 0; i < a; i++ )
      {
	oled_fd_inc(oled);
      }

      for( i = 0; i < b; i++ )
      {	
	oled_draw_pixel(oled, oled->x + x, oled->y + y);
	oled_fd_inc(oled);
      }
      
    } while( oled_fd_get_bits(oled, 1) != 0 );
    
    if ( oled->y >= oled->glyph_height )
      break;
  }
}

void oled_set_font(oled_t *oled, const unsigned char *font)
{
    oled->glyph_cnt = *font++;
    oled->bits_per_0 = *font++;
    oled->bits_per_1 = *font++;
    oled->font = font;
    oled->glyph_data = NULL;
}

/* 
  prepare for decoding of the provided glyph 
  return 0, if glyph for this encoding is not available
*/
static int oled_fd_set_encoding(oled_t *oled, unsigned encoding)
{
  unsigned cnt = oled->glyph_cnt;
  const unsigned char *ptr;
  ptr = oled->font;
  
  /* search for the glyph */
  while( cnt > 0 )
  {
    if ( ptr[0] == encoding )
      break; /* glyph found */
    ptr += ptr[3];
    cnt--;
  }

  /* handle "glyph not found" case */
  if ( cnt == 0 )
  {
    oled->glyph_data = NULL;
    return 0;
  }
   
  /* setup decoding */
  
  oled->glyph_width = ptr[1];
  oled->glyph_height = ptr[2];
  oled->glyph_delta = ptr[4];
  oled->x_offset = ((signed char *)ptr)[5];
  oled->y_offset = ((signed char *)ptr)[6];

  oled->glyph_data = ptr+7;

  /*
  ptr++;
  oled->glyph_width = *ptr++;
  oled->glyph_height = *ptr++;
  ptr++;
  oled->glyph_delta = *ptr++;
  oled->x_offset = *((signed char *)ptr);
  ptr++;
  oled->y_offset = *((signed char *)ptr);
  ptr++;

  oled->glyph_data = ptr;
  */
  
  return 1;
}

unsigned __attribute__ ((noinline)) oled_draw_glyph(oled_t *oled, unsigned x, unsigned y, unsigned encoding)
{
  if ( oled_fd_set_encoding(oled, encoding) == 0 )
    return 0;  
  oled_fd_decode(oled, x, y);
  return oled->glyph_delta;
}

unsigned __attribute__ ((noinline)) oled_draw_string(oled_t *oled, unsigned x, unsigned y, const char *s)
{
  while( *s != '\0' )
    x += oled_draw_glyph(oled, x, y, *s++);
  return x;
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
  
  oled_start_page_seq[2] = 0x0b0 | (oled->page_start>>3);
  delay_micro_seconds(100);
  oled_send_seq(I2C_CMD_MODE, sizeof(oled_start_page_seq), oled_start_page_seq);
  delay_micro_seconds(100);
  oled_send_seq(I2C_DATA_MODE, WIDTH, oled->oled_display_page);
  oled_clear_page(oled);
  
  oled->page_start+=8;
  return oled->page_start < HEIGHT;
}


void __attribute__ ((noinline)) oled_init(void)
{
  i2c_init();
  
  oled_send_seq(I2C_CMD_MODE, sizeof(oled_init_seq), oled_init_seq);
  
  //oled_send_seq(I2C_CMD_MODE, sizeof(oled_start_page_seq), oled_start_page_seq);
  //oled_send_seq(I2C_DATA_MODE, sizeof(oled_test_seq), oled_test_seq);
  
  oled_start_page(&oled_o);
  do
  {
  }
  while( oled_next_page(&oled_o) );
  
}
