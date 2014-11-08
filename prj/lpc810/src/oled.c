

#include <stddef.h>
#include "sys.h"
#include "oled.h"

#define I2C_SLA         (0x3c*2)
//#define I2C_CMD_MODE  0x080
#define I2C_CMD_MODE    0x000
#define I2C_DATA_MODE   0x040




oled_t oled_o;




const unsigned char logisoso62[756] = {
  11,5,5,48,31,62,61,40,4,0,236,168,13,140,218,180,
  170,116,157,172,108,68,57,202,80,146,34,146,149,8,164,33,
  1,121,240,255,255,255,255,61,36,32,13,17,201,74,132,146,
  148,161,28,133,108,37,59,87,170,214,212,34,216,212,131,1,
  49,16,62,30,40,13,0,8,237,164,140,170,44,132,17,31,
  248,1,36,52,99,41,8,66,255,255,255,255,255,7,50,31,
  62,83,40,5,0,236,168,13,140,218,180,170,116,157,172,108,
  100,49,202,80,146,34,146,149,8,164,33,1,113,209,131,239,
  69,45,9,71,75,68,241,18,65,188,132,4,49,169,73,85,
  106,170,42,53,85,149,154,84,165,166,170,82,83,85,169,169,
  170,212,164,42,53,85,149,154,170,74,77,85,165,126,224,255,
  0,51,31,62,71,40,5,255,224,255,213,196,38,53,169,74,
  77,85,165,166,170,82,83,85,169,169,170,170,204,108,228,3,
  161,7,189,168,46,54,185,201,69,97,228,162,255,51,193,75,
  8,209,146,97,180,36,40,73,17,76,97,198,86,180,146,33,
  75,81,44,130,141,45,28,0,52,31,62,69,40,4,0,10,
  185,104,22,185,104,22,185,104,22,185,104,22,185,104,22,185,
  104,22,185,104,22,185,104,4,81,72,65,20,82,16,133,20,
  68,29,6,73,136,65,18,98,144,132,24,36,29,7,65,200,
  65,16,114,16,244,129,255,123,200,69,255,67,0,53,31,62,
  73,40,4,0,224,255,1,228,162,255,43,6,67,66,147,176,
  147,25,173,108,132,27,157,104,202,34,150,164,4,101,37,33,
  105,72,64,92,244,96,15,185,232,223,125,32,244,96,47,106,
  136,72,86,34,148,164,12,229,40,100,43,217,185,146,165,166,
  22,193,166,30,12,0,54,31,62,87,40,4,0,236,168,13,
  140,218,180,170,116,157,172,108,68,57,202,80,146,34,146,149,
  8,164,69,15,238,162,191,98,48,36,52,9,59,153,209,202,
  70,184,209,137,166,44,98,73,74,80,86,18,146,134,132,164,
  69,15,254,191,135,4,164,33,34,89,137,80,146,50,148,163,
  144,173,100,231,74,213,154,90,4,155,122,48,0,55,31,62,
  66,40,4,0,224,255,1,196,197,90,18,144,150,4,164,37,
  1,105,136,64,88,34,142,150,216,196,34,54,173,38,54,173,
  38,54,173,38,54,101,17,155,102,17,155,86,19,155,86,19,
  155,86,19,155,178,136,77,179,136,77,171,137,77,57,0,56,
  31,62,96,40,5,0,236,168,13,140,218,180,170,116,157,172,
  108,68,57,202,80,146,34,146,149,8,164,33,1,121,240,191,
  135,4,164,33,34,89,137,80,146,50,148,163,144,173,100,231,
  74,149,170,210,117,178,178,145,165,44,67,73,138,72,86,34,
  144,134,4,228,193,255,30,18,144,134,136,100,37,66,73,202,
  80,142,66,182,146,157,43,85,107,106,17,108,234,193,0,57,
  31,62,90,40,4,0,236,168,13,140,218,180,170,116,157,172,
  108,68,57,202,80,146,34,146,149,8,164,33,1,121,240,255,
  115,73,64,90,18,146,165,4,37,45,98,41,141,232,6,71,
  182,162,153,236,96,137,17,8,51,10,114,209,119,31,8,61,
  216,139,26,34,146,149,8,37,41,67,57,10,217,74,118,174,
  100,169,169,69,176,169,7,3,0,58,8,35,27,23,8,8,
  130,24,70,248,64,16,140,65,124,240,2,49,140,112,4,44,
  24,131,16,0};

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

unsigned char __attribute__ ((noinline)) oled_fd_get_bits(oled_t *oled, int cnt)
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
  int a, b;
  int i;
  
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
