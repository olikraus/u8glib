

#include <stddef.h>
#include "sys.h"
#include "oled.h"

#define I2C_OLED_SLA         (0x3c*2)
//#define I2C_CMD_MODE  0x080
#define I2C_CMD_MODE    0x000
#define I2C_DATA_MODE   0x040




oled_t oled_o;

/* Adobe helvR14, only uppercase */
/* https://code.google.com/p/u8glib/wiki/fontgroupadobex11 */
const unsigned char helvR14small[815] = {
  43,4,3,5,4,3,4,5,32,5,0,152,5,44,9,162,
  90,5,40,34,36,0,45,6,37,216,6,10,46,6,66,138,
  5,8,47,14,197,137,101,116,34,163,68,70,137,140,54,0,
  48,17,168,139,74,104,76,84,8,241,35,9,17,17,27,18,
  0,49,9,165,141,106,14,106,244,31,50,17,168,139,74,72,
  46,132,196,164,134,246,74,236,224,64,0,51,20,168,139,74,
  74,14,132,136,164,132,166,200,198,136,104,38,108,72,0,52,
  23,169,137,202,196,166,136,36,100,68,100,68,212,72,8,73,
  28,28,144,201,169,0,53,20,168,139,10,46,46,196,196,76,
  46,100,198,196,136,104,14,70,74,0,54,19,168,139,74,104,
  46,100,200,84,140,92,8,49,170,145,176,33,1,55,17,168,
  139,10,30,136,73,41,147,18,147,18,147,18,83,5,56,22,
  168,139,74,104,44,70,138,136,36,68,68,44,70,138,136,74,
  38,108,72,0,57,20,168,139,74,104,44,100,138,24,73,156,
  76,136,137,209,72,156,148,0,58,7,66,139,5,136,9,59,
  10,162,91,5,136,41,34,36,0,65,26,204,137,173,68,37,
  9,233,68,196,68,164,132,52,58,136,57,24,17,19,17,147,
  16,36,20,66,29,203,139,13,14,98,14,68,164,38,196,36,
  196,36,164,68,14,68,14,38,196,234,152,29,88,28,136,0,
  67,23,204,139,142,170,14,68,166,38,228,42,69,53,29,149,
  147,152,26,57,144,170,1,68,24,204,139,14,14,100,14,70,
  196,38,228,36,4,249,157,132,216,196,193,200,129,12,0,69,
  18,202,141,13,62,8,212,240,64,226,64,66,80,195,131,3,
  3,70,16,201,141,12,30,216,105,119,16,113,16,33,167,119,
  0,71,25,205,139,143,172,14,70,198,38,4,11,105,149,61,
  8,148,16,148,24,27,57,32,178,16,72,13,203,139,14,228,
  248,238,224,65,29,223,9,73,6,194,141,6,126,74,14,200,
  137,202,244,103,68,68,37,19,54,36,0,75,31,204,141,13,
  196,38,164,70,132,102,100,134,68,166,36,198,234,204,68,166,
  100,134,132,102,164,70,196,38,228,6,76,11,201,139,11,228,
  244,191,59,56,32,77,30,206,139,16,68,73,11,13,207,14,
  194,44,132,36,40,132,36,72,148,144,40,161,9,137,225,72,
  136,72,1,78,25,203,139,14,228,202,172,172,40,132,72,100,
  72,100,104,68,104,68,136,36,168,156,213,9,79,25,205,139,
  143,202,14,100,166,70,228,36,230,42,185,172,155,144,19,153,
  154,57,16,43,2,80,20,202,141,13,14,66,14,36,164,202,
  88,29,84,28,132,8,234,33,0,81,29,237,123,143,202,14,
  100,166,70,228,36,230,42,185,44,146,152,16,146,16,25,162,
  57,16,171,144,149,0,82,23,203,139,14,14,68,14,38,196,
  234,152,29,88,28,136,136,73,136,73,200,113,39,83,21,202,
  139,109,136,14,34,134,202,10,235,10,23,146,21,77,28,196,
  152,0,84,11,202,139,12,30,24,9,234,127,4,85,15,203,
  139,14,228,248,223,73,72,137,28,8,213,0,86,27,204,137,
  13,4,9,37,196,68,196,68,196,100,132,244,74,68,76,68,
  76,68,142,144,82,10,0,87,39,208,139,18,164,164,168,164,
  168,164,136,136,36,100,104,68,100,66,98,68,244,55,18,34,
  18,66,18,34,18,66,18,65,17,82,67,99,186,1,88,27,
  203,139,13,228,232,36,164,68,102,102,84,73,200,13,206,73,
  72,201,200,44,145,146,144,163,19,89,23,204,137,13,4,9,
  37,196,68,196,100,132,132,70,166,68,228,40,69,245,10,0,
  90,15,202,139,12,30,24,202,233,110,78,135,7,7,6};

/* Adobe helvR12, only uppercase */
/* https://code.google.com/p/u8glib/wiki/fontgroupadobex11 */
const unsigned char helvR12small[822] = {
  50,4,2,4,4,3,4,4,32,5,0,204,2,35,25,184,
  196,156,72,40,18,138,68,6,131,72,81,36,20,137,12,6,
  145,162,72,40,146,1,42,10,85,124,147,138,138,73,162,38,
  43,12,153,68,165,96,163,193,81,176,17,0,44,8,66,53,
  138,10,5,0,45,7,20,228,130,65,0,46,6,33,70,2,
  1,47,12,196,196,154,146,76,147,76,73,166,6,48,17,199,
  197,148,77,73,38,145,242,85,34,19,201,100,38,0,49,9,
  195,199,148,138,69,164,63,50,17,199,197,148,77,69,74,21,
  75,21,137,82,177,216,96,16,51,17,199,197,148,77,69,74,
  85,179,203,169,84,137,76,102,2,52,21,200,196,36,85,34,
  149,8,69,66,145,76,39,161,200,96,160,202,149,0,53,19,
  199,197,148,129,36,150,138,13,50,117,177,152,42,145,201,76,
  0,54,19,199,197,148,65,36,164,146,37,38,154,68,202,85,
  34,147,153,0,55,16,200,196,132,3,93,172,46,150,139,229,
  202,114,41,0,56,19,199,197,148,77,69,74,149,200,100,54,
  21,41,171,68,38,51,1,57,18,199,197,148,77,69,202,85,
  34,35,89,196,84,162,200,32,2,58,7,145,70,2,149,0,
  59,9,178,53,138,218,68,66,1,60,9,153,68,61,149,179,
  164,7,61,10,72,84,133,3,61,98,48,16,62,11,153,69,
  5,165,203,152,202,29,0,63,15,199,197,148,77,69,74,21,
  75,53,75,199,50,0,65,23,202,196,37,161,46,18,139,196,
  34,169,80,155,193,64,18,139,196,18,65,97,0,66,24,201,
  197,133,155,84,36,150,136,37,82,145,193,32,18,75,228,156,
  37,6,131,8,0,67,20,202,69,166,65,72,20,201,37,130,
  201,166,201,92,68,148,26,68,0,68,20,202,69,134,163,148,
  36,151,200,37,130,222,37,114,137,148,100,48,2,69,13,200,
  197,133,119,237,6,119,221,13,6,2,70,13,199,69,133,3,
  89,179,193,64,214,51,0,71,22,202,197,166,149,70,146,75,
  4,147,69,131,97,34,151,136,73,52,137,208,36,72,12,201,
  69,134,156,119,131,3,157,239,2,73,6,193,69,130,15,74,
  12,198,68,172,126,37,50,74,12,18,0,75,23,200,197,133,
  152,42,17,138,100,74,66,9,145,36,211,40,146,74,164,18,
  177,0,76,10,199,197,132,88,255,217,96,16,77,31,203,197,
  134,228,110,144,91,164,18,138,84,66,145,74,72,50,17,73,
  38,34,201,68,52,137,140,38,145,17,21,78,23,201,69,134,
  220,76,145,82,164,36,33,77,70,147,17,69,84,9,85,66,
  182,11,79,20,203,197,166,153,70,147,139,228,18,73,151,137,
  92,36,151,49,27,1,80,15,200,198,133,147,84,34,102,149,
  24,76,114,189,3,81,23,219,189,166,153,70,147,139,228,18,
  73,151,137,92,36,20,201,152,45,178,9,0,82,25,201,70,
  134,155,84,36,150,136,37,82,145,193,38,21,137,37,98,137,
  88,34,150,200,5,83,21,201,197,149,129,38,149,200,233,18,
  73,229,50,145,211,37,82,153,129,4,84,10,201,68,133,71,
  193,254,35,0,85,13,201,69,134,156,255,46,145,202,12,36,
  0,86,23,202,196,133,160,48,17,139,196,34,177,76,168,85,
  36,22,137,69,114,66,17,0,87,36,205,197,135,84,74,149,
  82,85,100,18,153,72,38,145,137,100,18,153,138,76,34,148,
  200,36,66,137,76,34,85,150,138,165,50,0,88,24,200,197,
  133,88,34,20,9,101,34,161,72,74,166,138,132,34,153,80,
  36,148,136,5,89,18,201,197,133,92,34,21,73,101,138,50,
  169,68,108,23,236,8,90,16,201,68,141,193,64,151,211,213,
  233,234,116,117,131,3};
  
  
/* Logisoso: numbers */
/* https://code.google.com/p/ucglib/wiki/fontgrouplogisoso */
const unsigned char logisoso46[571] = {
  11,5,5,5,6,5,4,5,48,45,215,157,232,209,225,22,
  245,156,168,76,100,26,72,65,196,113,142,112,164,102,177,255,
  255,255,173,38,29,193,72,134,64,10,50,38,50,149,232,60,
  106,113,7,2,0,49,22,204,213,232,141,89,57,17,100,36,
  225,3,85,72,134,97,204,255,255,255,63,50,62,215,157,232,
  209,225,150,229,156,168,76,100,26,72,65,196,113,142,112,164,
  102,177,91,77,58,66,161,12,49,172,227,29,240,120,7,60,
  222,9,30,239,4,143,119,130,199,59,160,1,143,119,192,227,
  157,224,241,78,240,3,127,192,1,51,58,215,157,231,193,63,
  224,192,227,157,224,241,14,104,192,227,29,208,128,199,59,160,
  1,145,151,184,133,49,139,121,9,68,162,17,143,104,254,35,
  193,58,4,145,142,112,28,36,40,34,25,20,145,12,132,26,
  150,32,0,52,55,215,157,232,145,1,141,104,6,141,104,6,
  141,104,6,141,104,138,69,52,139,69,52,27,6,42,136,113,
  12,98,28,131,24,199,32,198,41,138,97,140,98,24,163,24,
  230,3,127,192,89,70,52,127,6,0,53,53,215,157,232,193,
  63,64,69,243,79,28,40,50,19,161,70,37,42,145,20,36,
  28,201,8,71,106,22,107,25,209,124,145,89,172,213,164,35,
  24,201,16,72,65,198,68,166,18,157,71,45,238,64,0,54,
  62,215,157,232,209,225,22,245,156,168,76,100,26,72,65,132,
  145,140,112,164,102,177,162,249,134,129,34,51,17,106,84,162,
  18,73,65,2,114,142,112,164,102,177,255,86,147,142,112,156,
  67,32,5,25,19,153,74,116,30,181,184,3,1,55,54,215,
  157,232,193,63,64,169,150,50,130,145,142,96,164,35,24,201,
  136,6,60,65,35,26,240,4,141,104,192,19,52,224,25,52,
  224,9,26,209,128,39,104,68,3,158,160,17,13,120,130,6,
  60,83,0,56,68,215,157,232,209,225,22,245,156,168,76,100,
  26,72,65,196,113,142,112,164,102,177,223,106,210,17,142,115,
  8,164,32,99,34,146,137,21,169,76,3,41,136,56,206,17,
  142,212,44,246,91,77,58,194,113,14,129,20,100,76,100,42,
  209,121,212,226,14,4,0,57,65,215,157,232,209,225,22,245,
  156,168,76,100,26,72,65,196,113,142,112,164,102,177,255,86,
  147,142,112,28,36,32,37,17,181,65,145,201,68,200,24,70,
  52,23,23,198,44,102,53,233,8,70,50,4,82,144,49,145,
  169,68,231,81,139,59,16,0,58,19,70,179,30,195,32,138,
  16,13,225,131,180,32,138,16,9,34,0};


/*
  precondition: cnt must be > 0 
  
*/
void __attribute__ ((noinline)) oled_send_seq(uint32_t mode, uint32_t cnt, const uint8_t *cmd)
{
  
  i2c_start();
  i2c_write_byte(I2C_OLED_SLA);		// address and 0 for RWn bit    
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

/* this is place in the data section (RAM) to allow changing the page */
uint8_t oled_start_page_seq[] = 
{
 0x010,		/* set upper 4 bit of the col adr to 0 */
  0x000,		/* SSD1306: 0, SH1106. 2, set lower 4 bit of the col adr  */
  0x0b0,		/* select page 0 */
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

static unsigned __attribute__ ((noinline)) oled_fd_get_bits(oled_t *oled, int cnt)
{
  unsigned val;
  unsigned bit_pos = oled->decode_bit_pos;
  
  val = *(oled->decode_ptr);
  
  val >>= bit_pos;
  if ( bit_pos + cnt >= 8 )
  {
    oled->decode_ptr++;
    val |= *(oled->decode_ptr) << (8-bit_pos);
    bit_pos -= 8;
  }
  val &= (1<<cnt)-1;
  bit_pos += cnt;
  
  oled->decode_bit_pos = bit_pos;
  return val;
}

static int __attribute__ ((noinline)) oled_fd_get_signed_bits(oled_t *oled, int cnt)
{
  return (int)oled_fd_get_bits(oled, cnt) - ((1<<cnt)>>1);
}

static void __attribute__ ((noinline)) oled_fd_inc(oled_t *oled)
{
  unsigned x = oled->x;
  x++;
  if ( x == oled->glyph_width )
  {
    x = 0;
    oled->y++;
  }
  oled->x = x;
}

static void oled_fd_decode(oled_t *oled, unsigned x, unsigned y)
{
  unsigned a, b;
  unsigned i;
  
  
  /* init decode algorithm */
  oled->decode_ptr = oled->glyph_data;
  oled->decode_byte_pos = 0;
  oled->decode_bit_pos = 0;

  /* reset local x/y position */
  oled->x = 0;
  oled->y = 0;

  /* apply glyph information */
  /*  
    ~             BBX width                                       unsigned	5
    ~             BBX height                                      unsigned	5
    ~             BBX xoffset                                    signed		2
    ~             BBX yoffset                                    signed		5
    ~             DWIDTH                                          signed		3
*/
  oled->glyph_width = oled_fd_get_bits(oled, oled->bits_per_char_width);
  oled->glyph_height = oled_fd_get_bits(oled, oled->bits_per_char_height);
  x += oled_fd_get_signed_bits(oled, oled->bits_per_char_x);			// x offset
  y -= oled_fd_get_signed_bits(oled, oled->bits_per_char_y);			// y offset
  oled->glyph_delta = oled_fd_get_bits(oled, oled->bits_per_delta_x);
  
  /* adjust glyph position */
  y -= oled->glyph_height;
  
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

void __attribute__ ((noinline)) oled_set_font(oled_t *oled, const unsigned char *font)
{
    oled->glyph_cnt = *font++;
    oled->bits_per_0 = *font++;
    oled->bits_per_1 = *font++;
    oled->bits_per_char_width = *font++;
    oled->bits_per_char_height = *font++;
    oled->bits_per_char_x = *font++;
    oled->bits_per_char_y = *font++;
    oled->bits_per_delta_x = *font++;
  
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
    ptr += ptr[1];
    cnt--;
  }

  /* handle "glyph not found" case */
  if ( cnt == 0 )
  {
    oled->glyph_data = NULL;
    return 0;
  }
   
  oled->glyph_data = ptr+2;

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
  while( *s != '\0' && *s <'\xf0')
    x += oled_draw_glyph(oled, x, y, *s++);
  return x;
}

unsigned __attribute__ ((noinline)) oled_draw_num(oled_t *oled, unsigned x, unsigned y, unsigned d, unsigned is_leading_zero, unsigned val)
{
  unsigned t = 0;
  while( val >= 10 )
  {
    t++;
    val-=10;
  }
  if ( t != 0 || is_leading_zero != 0)
  {
    t += '0';
    oled_draw_glyph(oled, x, y, t);
  }
  x+=d;
  val += '0';
  oled_draw_glyph(oled, x, y, val);
  x+=d;
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
  //delay_micro_seconds(100);
  oled_send_seq(I2C_CMD_MODE, sizeof(oled_start_page_seq), oled_start_page_seq);
  //delay_micro_seconds(100);
  oled_send_seq(I2C_DATA_MODE, WIDTH, oled->oled_display_page);
  oled_clear_page(oled);
  
  i2c_stop();	/* finally send a stop. this is not done by oled_send_seq, so it is done here */
  
  oled->page_start+=8;
  return oled->page_start < HEIGHT;
}


void __attribute__ ((noinline)) oled_init(void)
{
  i2c_init();
  
  oled_send_seq(I2C_CMD_MODE, sizeof(oled_init_seq), oled_init_seq);
  
  oled_start_page(&oled_o);
  do
  {
  }
  while( oled_next_page(&oled_o) );
  
}
