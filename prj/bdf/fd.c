/*
  fd.c
  
  font decode
  
  Font Info:
    offset
    0		number of glyphs in the font (1x byte)
    1		decode algorithm: bits for 0
    2		decode algorithm: bits for 1
    3 		bd_bits_per_char_width
    4		bd_bits_per_char_height
    5		bd_bits_per_char_x
    6		bd_bits_per_char_y
    7		bd_bits_per_delta_x
  
    glyph information 
    offset
    0             encoding                                       unsigned
    1             data size (size of full record)              unsigned	
    
    ~             BBX width                                       unsigned	5
    ~             BBX height                                      unsigned	5
    ~             BBX xoffset                                    signed		2
    ~             BBX yoffset                                    signed		5
    ~             DWIDTH                                          signed		3
  
*/  

#include <stdio.h>

struct _fd_struct
{
  /* font information */
  const unsigned char *font;		/* pointer to the first glyph information */
  
  unsigned glyph_cnt;
  unsigned bits_per_0;
  unsigned bits_per_1;
  unsigned bits_per_char_width;
  unsigned bits_per_char_height;
  unsigned bits_per_char_x;
  unsigned bits_per_char_y;
  unsigned bits_per_delta_x;

  /* glyph information */
  const unsigned char *glyph_data;
  unsigned glyph_width;
  unsigned glyph_height;
  unsigned glyph_delta;
  int x_offset;
  int y_offset;

  /* decode algorithm */
  const unsigned char *decode_ptr;
  unsigned decode_byte_pos;
  unsigned decode_bit_pos;
  
  unsigned x;
  unsigned y;
  
};
typedef struct _fd_struct fd_t;

char screen[40][120];

void init_screen(void)
{
  unsigned x, y;
  for( y = 0; y < 40; y++)
    for( x = 0; x < 120; x++)
      screen[y][x] = '.';  
}

void show_screen(void)
{
  unsigned x, y;
  for( y = 0; y < 40; y++)
  {
    for( x = 0; x < 120; x++)
    {
      printf("%c", screen[y][x]);  
    }
    printf("\n");
  }
}

void set_pixel(unsigned x, unsigned y)
{
  if ( x >= 120 || y >= 40 )
    return;
  screen[y][x] = '#';
}

unsigned char fd_get_bits(fd_t *fd, int cnt)
{
  unsigned val;
  
  val = *(fd->decode_ptr);
  val >>= fd->decode_bit_pos;
  if ( fd->decode_bit_pos + cnt >= 8 )
  {
    fd->decode_ptr++;
    val |= *(fd->decode_ptr) << (8-fd->decode_bit_pos);
    fd->decode_bit_pos -= 8;
  }
  val &= (1<<cnt)-1;
  fd->decode_bit_pos += cnt;
  return val;
}

void fd_inc(fd_t *fd)
{
  fd->x++;
  if ( fd->x == fd->glyph_width )
  {
    fd->x = 0;
    fd->y++;
    printf("\n");
  }
}

void fd_decode(fd_t *fd, unsigned x, unsigned y)
{
  int a, b;
  int i;

  /* init decode algorithm */
  fd->decode_ptr = fd->glyph_data;
  fd->decode_byte_pos = 0;
  fd->decode_bit_pos = 0;

/*  
    ~             BBX width                                       unsigned	5
    ~             BBX height                                      unsigned	5
    ~             BBX xoffset                                    signed		2
    ~             BBX yoffset                                    signed		5
    ~             DWIDTH                                          signed		3
*/
  fd->glyph_width = fd_get_bits(fd, fd->bits_per_char_width);
  fd->glyph_height = fd_get_bits(fd, fd->bits_per_char_height);
  fd->x_offset = fd_get_bits(fd, fd->bits_per_char_x) - ((1<<fd->bits_per_char_x)>>1);
  fd->y_offset = fd_get_bits(fd, fd->bits_per_char_y) - ((1<<fd->bits_per_char_y)>>1);
  fd->glyph_delta = fd_get_bits(fd, fd->bits_per_delta_x);
  
  /* adjust glyph position */
  x += fd->x_offset;
  y -= fd->y_offset;
  y -= fd->glyph_height;
  
  /* reset local x/y position */
  fd->x = 0;
  fd->y = 0;

  
  /* decode glyph */
  for(;;)
  {
    a = fd_get_bits(fd, fd->bits_per_0);
    b = fd_get_bits(fd, fd->bits_per_1);
    do
    {
      for( i = 0; i < a; i++ )
      {
	fd_inc(fd);
      }

      for( i = 0; i < b; i++ )
      {
	set_pixel(fd->x + x, fd->y + y);
	fd_inc(fd);
      }
      
    } while( fd_get_bits(fd, 1) != 0 );
    
    if ( fd->y >= fd->glyph_height )
      break;
  }
}

void fd_init(fd_t *fd, const unsigned char *font)
{
    fd->glyph_cnt = *font++;
    fd->bits_per_0 = *font++;
    fd->bits_per_1 = *font++;
    fd->bits_per_char_width = *font++;
    fd->bits_per_char_height = *font++;
    fd->bits_per_char_x = *font++;
    fd->bits_per_char_y = *font++;
    fd->bits_per_delta_x = *font++;
    
    fd->font = font;
    fd->glyph_data = NULL;
}

/* 
  prepare for decoding of the provided glyph 
  return 0, if glyph for this encoding is not available
*/
int fd_set_encoding(fd_t *fd, unsigned encoding)
{
  unsigned cnt = fd->glyph_cnt;
  const unsigned char *ptr;
  ptr = fd->font;
  
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
    fd->glyph_data = NULL;
    return 0;
  }
   

  fd->glyph_data = ptr+2;
  
  return 1;
}

unsigned fd_draw_glyph(fd_t *fd, unsigned x, unsigned y, unsigned encoding)
{
  if ( fd_set_encoding(fd, encoding) == 0 )
    return 0;  
  fd_decode(fd, x, y);
  return fd->glyph_delta;
}

unsigned fd_draw_string(fd_t *fd, unsigned x, unsigned y, const char *s)
{
  while( *s != '\0' )
    x += fd_draw_glyph(fd, x, y, *s++);
}

const unsigned char test_0_9[396] = {
  11,5,5,7,7,4,4,7,48,35,15,76,128,132,28,39,
  41,203,104,68,49,138,80,20,85,73,14,250,157,164,168,74,
  17,138,81,136,102,44,37,57,7,1,0,49,16,138,139,128,
  228,12,134,40,197,248,128,97,200,255,31,50,35,16,76,128,
  132,28,103,33,205,112,130,49,140,80,148,197,36,39,57,133,
  50,84,161,140,100,66,39,100,36,51,245,129,15,8,51,43,
  16,76,128,132,28,103,33,205,104,68,81,138,64,152,34,16,
  135,8,196,33,86,161,10,116,36,67,33,203,180,146,147,50,
  75,41,132,35,26,178,156,163,0,52,45,16,76,128,4,21,
  171,80,70,58,33,228,16,129,56,131,32,12,33,8,51,12,
  162,16,131,32,36,50,20,98,16,133,24,131,33,198,7,62,
  32,36,130,145,27,0,53,36,15,76,128,68,48,131,109,12,
  139,92,40,10,51,26,209,8,130,24,170,180,136,133,152,196,
  40,164,16,141,96,136,114,140,2,0,54,44,15,76,128,164,
  24,71,33,204,104,66,65,138,64,24,100,145,68,65,136,128,
  8,39,56,193,24,75,73,14,218,73,74,17,138,81,136,102,
  44,37,65,69,1,0,55,30,16,76,128,4,252,128,176,136,
  85,44,210,42,22,177,138,69,172,98,17,171,180,136,85,166,
  138,85,134,0,56,50,17,12,128,164,28,104,41,13,41,70,
  169,20,130,56,132,32,14,33,136,67,136,162,20,163,84,22,
  179,148,102,20,165,8,197,73,18,42,37,167,8,198,48,132,
  67,154,178,160,163,0,57,44,15,76,128,164,20,40,41,203,
  104,68,49,138,80,148,228,160,157,164,44,195,8,46,129,4,
  162,16,130,88,196,66,12,17,10,82,8,102,48,37,65,69,
  1,0,58,10,133,200,192,2,100,31,32,25};

const unsigned char logisoso46[585] = {
  11,5,5,7,7,7,7,7,48,46,23,215,16,232,65,135,
  91,212,115,162,50,145,105,32,5,17,199,57,194,145,154,197,
  254,255,255,183,154,116,4,35,25,2,41,200,152,200,84,162,
  243,168,197,29,8,0,49,24,12,151,18,232,49,102,229,68,
  144,145,132,15,84,33,25,134,49,255,255,255,255,0,50,63,
  23,215,16,232,65,135,91,150,115,162,50,145,105,32,5,17,
  199,57,194,145,154,197,110,53,233,8,133,50,196,176,142,119,
  192,227,29,240,120,39,120,188,19,60,222,9,30,239,128,6,
  60,222,1,143,119,130,199,59,193,15,252,1,7,51,59,23,
  215,240,231,1,255,128,3,143,119,130,199,59,160,1,143,119,
  64,3,30,239,128,6,68,94,226,22,198,44,230,37,16,137,
  70,60,162,249,143,4,235,16,68,58,194,113,144,160,136,100,
  80,68,50,16,106,88,130,0,52,56,23,215,16,232,65,6,
  52,162,25,52,162,25,52,162,25,52,162,41,22,209,44,22,
  209,108,24,168,32,198,49,136,113,12,98,28,131,24,167,40,
  134,49,138,97,140,98,152,15,252,1,103,25,209,252,25,0,
  53,54,23,215,16,232,1,255,0,21,205,63,113,160,200,76,
  132,26,149,168,68,82,144,112,36,35,28,169,89,172,101,68,
  243,69,102,177,86,147,142,96,36,67,32,5,25,19,153,74,
  116,30,181,184,3,1,54,64,23,215,16,232,65,135,91,212,
  115,162,50,145,105,32,5,17,70,50,194,145,154,197,138,230,
  27,6,138,204,68,168,81,137,74,36,5,9,200,57,194,145,
  154,197,254,91,77,58,194,113,14,129,20,100,76,100,42,209,
  121,212,226,14,4,0,55,55,23,215,16,232,1,255,0,165,
  90,202,8,70,58,130,145,142,96,36,35,26,240,4,141,104,
  192,19,52,162,1,79,208,128,103,208,128,39,104,68,3,158,
  160,17,13,120,130,70,52,224,9,26,240,76,1,56,69,23,
  215,16,232,65,135,91,212,115,162,50,145,105,32,5,17,199,
  57,194,145,154,197,126,171,73,71,56,206,33,144,130,140,137,
  72,38,86,164,50,13,164,32,226,56,71,56,82,179,216,111,
  53,233,8,199,57,4,82,144,49,145,169,68,231,81,139,59,
  16,0,57,66,23,215,16,232,65,135,91,212,115,162,50,145,
  105,32,5,17,199,57,194,145,154,197,254,91,77,58,194,113,
  144,128,148,68,212,6,69,38,19,33,99,24,209,92,92,24,
  179,152,213,164,35,24,201,16,72,65,198,68,166,18,157,71,
  45,238,64,0,58,21,6,141,209,24,9,131,40,66,52,132,
  15,210,130,40,66,36,136,0,0};

int main(void)
{
  fd_t fd;
  init_screen();
  fd_init(&fd, logisoso46);
  fd_draw_string(&fd, 0, 38, "2:3");
  show_screen();
}

