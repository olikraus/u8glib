/*
  fd.c
  
  font decode
  
  Font Info:
    offset
    0		number of glyphs in the font (1x byte)
    1		decode algorithm: bits for 0
    2		decode algorithm: bits for 1
  
    glyph information 
    offset
    0             encoding                                       unsigned
    1             BBX width                                       unsigned
    2             BBX height                                      unsigned
    3             data size                                          unsigned
    4             DWIDTH                                          signed
    5             BBX xoffset                                    signed
    6             BBX yoffset                                    signed
  
*/  

struct _fd_struct
{
  /* font information */
  unsigned char *font;		/* pointer to the first glyph information */
  
  unsigned glyph_cnt;
  unsigned bits_per_0;
  unsigned bits_per_1;

  /* glyph information */
  unsigned char *glyph_data;
  unsigned glyph_width;
  unsigned glyph_height;

  /* decode algorithm */
  unsigned decode_byte_pos;
  unsigned decode_bit_pos;
  
  unsigned x;
  unsigned y;
  
};
typedef struct _fd_struct fd_t;


unsigned char fd_get_bits(fd_t *fd, int cnt)
{
  unsigned char val;
  val = fd->glyph_data[fd->decode_byte_pos];
  val >>= fd->decode_bit_pos;
  if ( fd->decode_bit_pos + cnt < 8 )
  {
    val &= (1<<cnt) - 1;
  }
  else
  {
    fd->decode_byte_pos++;
    val |= fd->glyph_data[fd->decode_byte_pos] << 8-fd->decode_bit_pos;
    fd->decode_bit_pos -= 8;
    val &= (1<<cnt) - 1;
  }
  fd->decode_bit_pos += cnt;
  return val;
}

void fd_inc(fd_t *fd)
{
  fd->x++;
  if ( fd->x >= fd->glyph_width )
  {
    fd->x = 0;
    fd->y++;
    printf("\n");
  }
}

void fd_decode(fd_t *fd)
{
  int a, b;
  int i;
  
  fd->decode_byte_pos = 0;
  fd->decode_bit_pos = 0;
  fd->x = 0;
  fd->y = 0;
  
  for(;;)
  {
    a = fd_get_bits(fd, fd->bits_per_0);
    b = fd_get_bits(fd, fd->bits_per_1);
    do
    {
      for( i = 0; i < a; i++ )
      {
	printf(" .");
	fd_inc(fd);
      }

      for( i = 0; i < b; i++ )
      {
	printf(" #");
	fd_inc(fd);
      }
      
    } while( fd_get_bits(fd, 1) != 0 );
    
    if ( fd->y >= fd->glyph_height )
      break;
  }
}

void fd_init(fd_t *fd, unsigned char *font)
{
    fd->glyph_cnt = *font++;
    fd->bits_per_0 = *font++;
    fd->bits_per_1 = *font++;
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
  unsigned char *ptr;
  ptr = fd->font;
  
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
    fd->glyph_data = NULL;
    return 0;
  }
   
  /* setup decoding */
  fd->glyph_data = ptr;
  
  fd->glyph_width = ptr[1];
  fd->glyph_height = ptr[2];
}

