/*
  general font collections
    http://www.smashingmagazine.com/2007/11/08/40-excellent-freefonts-for-professional-design/
    http://techmagazine.ws/most-popular-free-quality-fonts/
    http://openfontlibrary.org/
  bitmap font collections
    http://www.orgdot.com/aliasfonts/ (includes links)
    http://www.04.jp.org/
    http://www.miniml.com
    http://www.fontspace.com/010bus



  fonts
    Gentium
      http://openfontlibrary.org/font/gentium    
      license: OFL
    Old-Standard
      http://openfontlibrary.org/font/old-standard
      license: OFL
    Hanuman
      http://openfontlibrary.org/font/hanumanb      
      license: OFL
    FreeUniversal
      http://openfontlibrary.org/font/freeuniversal
      license: OFL
    FriendShip-Code  <--- nicht so sicher...
      http://openfontlibrary.org/font/friendship-code
      license: CC-BY-SA
    LinuxLibertine
      http://de.wikipedia.org/wiki/Linux_Libertine
      http://sourceforge.net/projects/linuxlibertine/files/linuxlibertine/5.1.3-2/
      license: OFL
    DidactGothic
      source: http://openfontlibrary.org/
    judson
      source: http://openfontlibrary.org/
    unicons
      source: http://openfontlibrary.org/
      license: OFL
      suggested pt: 26, 30
    org_V01, fixed_V0
      source: http://www.orgdot.com/aliasfonts/
      license: open source, individual, cite required
      suggested pt: 8
    04b_03b.zip  04b_03.zip  04b_09.zip  04b_11.zip  04b_19.zip  04b_21.zip  04b_25.zip  04b_30.zip
      source: http://www.04.jp.org/
      license: "Freeware: You may use them as you like"
    7px4bus
      source: http://www.fontspace.com/010bus
      license: Licensed as: Freeware, Commercial use allowed!  
      suggested 7pt
    8pxbus
      source: http://www.fontspace.com/010bus
      license: Licensed as: Freeware, Commercial use allowed!  
      suggested 8pt

*/


/*
  only supports metric set "0"
  assume DWIDTH second arg to be 0 for all glyphs
  assumes that (0,0) of the BBX is placed on the base line
  assumes ISO10646 encoding of the BDF file
  
  font information 
  offset
  0		number of glyphs in the font (1x byte)
  1		decode algorithm: bits for 0
  2		decode algorithm: bits for 1
  3		bits_per_char_width
  4		bits_per_char_height
  5		bits_per_char_x
  6		bits_per_char_y
  7		bits_per_delta_x

    glyph information 
    offset
    0			encoding
    1			block size

ISO-8859-1 was incorporated as the first 256 code points of ISO/IEC 10646 and Unicode.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define BDF2U8G_COMPACT_OUTPUT
#define BDF2U8G_VERSION "1.02"

#define VERBOSE


/*=== forward declaration ===*/

/*=== result data ===*/
#define DATA_BUF_SIZE (1024*64)
unsigned char data_buf[DATA_BUF_SIZE];
int data_pos = 0;

void data_Init(void)
{
  data_pos = 0;
}

void data_Put(unsigned char c)
{
  data_buf[data_pos] = c;
  data_pos++;
}

void data_Write(FILE *out_fp, const char *indent)
{
  int i;
  int bytes_per_line = 16;
  for( i = 0; i < data_pos; i++ )
  {
#ifdef BDF2U8G_COMPACT_OUTPUT
    fprintf(out_fp, "%d", data_buf[i]);
#else
    fprintf(out_fp, "%3d", data_buf[i]);
#endif
    if ( i+1 != data_pos )
      fprintf(out_fp, ",");
    if ( (i+1) % bytes_per_line == 0 )
      fprintf(out_fp, "\n%s", indent);    
  }
}


/*=== low level parser ===*/
#define P_BUF_SIZE (1024*4)
int p_current_char;
const char *p_line;
char p_buf[P_BUF_SIZE];


/* put next char into p_current_char */
static int p_next_char(void)
{
  p_current_char = *p_line;
  if ( p_current_char == '\0' )
    return 0;
  p_line++;
  return 1;
}

int p_first_char(const char *line)
{
  p_line = line;
  return p_next_char();
}

void p_err(const char *msg)
{
}

int p_skip_space(void)
{
  for(;;)
  {
    if ( p_current_char == 0 || p_current_char > 32 )
      break;
    if ( p_next_char() == 0 )
      return 0;
  }
  return 1;
}

/* put identifier into p_buf */
int p_get_identifier(void)
{
  int i = 0;
  if ( p_current_char == '\0' )
    return p_err("unexpected EOF (expected identifier)"), 0;          
  for(;;)
  {
    if (  p_current_char <= 32 )
      break;
    p_buf[i++] =  p_current_char;
    if ( p_next_char() == 0 )
      break;
  }
  p_buf[i++] =  '\0';
  p_skip_space();
  return 1;    
}

/* put identifier into p_buf */
int p_get_identifier_with_blank(void)
{
  int i = 0;
  for(;;)
  {
    if (  p_current_char < 32 )
      break;
    p_buf[i++] =  p_current_char;
    if ( p_next_char() == 0 )
      break;
  }
  p_buf[i++] =  '\0';
  p_skip_space();
  return 1;    
}

int p_get_string(void)
{
  int i = 0;
  if ( p_current_char == '\0' )
    return 0;
  if ( p_current_char != '\"' )
    return p_err("\" expected"), 0;
  if ( p_next_char() == 0 )
    return p_err("unexpected EOF (\")"), 0;    
  for(;;)
  {
    if ( p_current_char == '\\' )
    {
      if ( p_next_char() == 0 )
        return p_err("unexpected EOF (\\)"), 0;    
    }
    else if ( p_current_char == '\"' )
    {
      p_next_char();
      break;
    }
    p_buf[i++] =  p_current_char;
    if ( p_next_char() == 0 )
      return p_err("unexpected EOF (\")"), 0;          
  }
  p_buf[i] =  '\0';
  return 1;
}

int p_get_any(void)
{
  if ( p_current_char == '\"' )
    return p_get_string();
  return p_get_identifier();  
}

int p_get_val(void)
{
  p_get_any();
  return atoi(p_buf);
}

int p_get_hex(void)
{
  int value = 0;
  if ( p_current_char >= '0' && p_current_char <= '9' )
    value = p_current_char - '0';
  else if ( p_current_char >= 'a' && p_current_char <= 'f' )
    value = p_current_char - 'a' + 10;
  else if ( p_current_char >= 'A' && p_current_char <= 'F' )
    value = p_current_char - 'A' + 10;
  p_next_char();
  return value;
}

int p_get_hex_byte(void)
{
  int v;
  v = p_get_hex();
  v *= 16;
  v+= p_get_hex();
  return v;
}

/*=== encoding mapping ===*/
/* the internal u8g index number (0..255) is mapped to the unicode number */
/* for the conversion we need the reverse search */
/* 0 is special and means not found */
int map_u8g_to_unicode[256];

int map_UnicodeToU8G(int unicode)
{
  int i;
  for( i = 0; i < 256; i++ )
    if ( map_u8g_to_unicode[i] == unicode )
      return i;
  return 0;
}

void map_Init(void)
{
  int i;
  map_u8g_to_unicode[0] = 0;
  for( i = 0; i < 256; i++ )
    map_u8g_to_unicode[i] = i;
}

void map_UpperLowerPage(int lower_page, int upper_page, int shift, int upper_shift)
{
  int i;
  int encoding;
  int tmp[256];
  //map_u8g_to_unicode[0] = 0;
  for( i = 0; i < 128; i++ )
  {
    encoding = i + lower_page * 128;
    map_u8g_to_unicode[i] = encoding;
  }

  for( i = 128; i < 256; i++ )
  {
    encoding = i - 128 + upper_page * 128;
    if ( i+upper_shift < 256 )
      map_u8g_to_unicode[i+upper_shift] = encoding;
  }

  for( i = 0; i < 256; i++ )
  {
    tmp[i] = map_u8g_to_unicode[i];
  }

  for( i = 0; i < shift; i++ )
  {
    map_u8g_to_unicode[i] = -1;
  }
  
  for( i = shift; i < 256; i++ )
  {
    map_u8g_to_unicode[ i ] = tmp[(i + 256 - shift) % 256];
  }
  /*
  printf("map_u8g_to_unicode[ 32 ] = %d\n", map_u8g_to_unicode[ 32 ]);
  printf("map_u8g_to_unicode[ 33 ] = %d\n", map_u8g_to_unicode[ 33 ]);
  */
}

/*=== store bdf file positions ===*/

long bdf_last_line_start_pos;
long bdf_encoding_pos[256];

void bdf_InitFilePos(void)
{
  int i;
  for( i = 0; i < 256; i++ )
    bdf_encoding_pos[i] = 0;
}

void bdf_SetFilePos(FILE *fp, int encoding)
{
  if ( encoding < 0 )
    return;
  if ( bdf_encoding_pos[encoding] == 0L )
    return;
  fseek(fp, bdf_encoding_pos[encoding], SEEK_SET);
  //fprintf(stderr, "setting file for encoding %d to pos %ld\n", encoding, bdf_encoding_pos[encoding]);
}

int bdf_IsEncodingAvailable(int encoding)
{
  if ( bdf_encoding_pos[encoding] == 0L )
  {
    //printf("encoding %d not availabe\n", encoding);
    return 0;
  }
  return 1;
}


void bdf_StoreFilePos(int encoding, long pos)
{
  //if ( encoding == 33 )
    //printf("encoding %d at pos %ld\n", encoding, pos);
  if ( bdf_encoding_pos[encoding] != 0L )
    return;
  bdf_encoding_pos[encoding] = pos;
}


/*=== bdf file read ===*/

int bdf_font_format = 0;


#define BDF_STATE_FONT_DATA 0
#define BDF_STATE_ENCODING 1

int bdf_state = BDF_STATE_FONT_DATA;
int bdf_requested_encoding = 0;

#define BDF_LINE_MAX (1024*4)
#define BDF_LINE_STATE_KEYWORDS 0
#define BDF_LINE_STATE_BITMAP 1
#define BDF_MAX_HEIGHT 200
#define BDF_AA_OFFSET 1


char bdf_copyright[BDF_LINE_MAX];
char bdf_font[BDF_LINE_MAX];
unsigned char bdf_bitmap_line[BDF_MAX_HEIGHT][20];


int bdf_line_state = BDF_LINE_STATE_KEYWORDS;
int bdf_line_bm_line = 0;

int bdf_font_size;      /* point font size */

int bdf_font_width;     /* FONTBOUNDINGBOX arg 1 */
int bdf_font_height;    /* FONTBOUNDINGBOX arg 2 */
int bdf_font_x;            /* FONTBOUNDINGBOX arg 3 */
int bdf_font_y;            /* FONTBOUNDINGBOX arg 4 */

int bdf_capital_A_height;
int bdf_capital_1_height;
int bdf_lower_g_descent;

int bdf_char_width;     /* BBX arg 1 */
int bdf_char_max_width;
int bdf_char_height;    /* BBX arg 2 */
int bdf_char_ascent;    /* defined as BBX arg 2 + BBX arg 4 */
int bdf_char_xascent;
int bdf_char_xdescent;
int bdf_char_max_ascent;
int bdf_char_max_height;
int bdf_char_x;            /* BBX arg 3 */
int bdf_char_max_x;
int bdf_char_min_x;
int bdf_char_y;            /* BBX arg 4 */
int bdf_char_max_y;
int bdf_char_min_y;

int bdf_delta_x;           /* DWIDTH arg 1 */
int bdf_delta_max_x;
int bdf_delta_min_x;
int bdf_delta_y;           /* DWIDTH arg 2 */
int bdf_delta_max_y;
int bdf_delta_min_y;

int bdf_glyph_data_len;
int bdf_glyph_data_max_len;
int bdf_glyph_cnt = 0;

int bdf_encoding;

int bdf_encoding_65_pos;
int bdf_encoding_97_pos;
int bdf_is_encoding_successfully_done;

char bdf_info[32000*2];

int bdf_is_put_glyph_completed = 0; /* indicator, when the glyph has been processed */

void bdf_ResetMax(void)
{
  bdf_char_max_width = 0;
  bdf_char_max_height = 0;
  bdf_char_max_x = 0;
  bdf_char_max_y = 0;
  bdf_delta_max_x = 0;
  bdf_delta_max_y = 0;
  bdf_char_min_x = 0;
  bdf_char_min_y = 0;
  bdf_delta_min_x = 0;
  bdf_delta_min_y = 0;
  bdf_glyph_data_max_len = 0;
  bdf_char_max_ascent = 0;
  bdf_char_xascent = 0;
  bdf_char_xdescent = 0;
}

void bdf_UpdateMax(void)
{
  if ( bdf_char_max_width < bdf_char_width )
    bdf_char_max_width = bdf_char_width;
  if ( bdf_char_max_height < bdf_char_height )
    bdf_char_max_height = bdf_char_height;
  
  if ( bdf_char_max_x < bdf_char_x )
    bdf_char_max_x = bdf_char_x;
  
  if ( bdf_char_max_y < bdf_char_y )
    bdf_char_max_y = bdf_char_y;
  
  if ( bdf_delta_max_x < bdf_delta_x )
    bdf_delta_max_x = bdf_delta_x;
  if ( bdf_delta_max_y < bdf_delta_y )
    bdf_delta_max_y = bdf_delta_y;
  
  if ( bdf_char_min_x > bdf_char_x )
    bdf_char_min_x = bdf_char_x;
  
  if ( bdf_char_min_y > bdf_char_y )
    bdf_char_min_y = bdf_char_y;
  
  if ( bdf_delta_min_x > bdf_delta_x )
    bdf_delta_min_x = bdf_delta_x;
  if ( bdf_delta_min_y > bdf_delta_y )
    bdf_delta_min_y = bdf_delta_y;
  
  if ( bdf_glyph_data_max_len < bdf_glyph_data_len )
    bdf_glyph_data_max_len = bdf_glyph_data_len;
  
  if ( bdf_char_max_ascent < bdf_char_ascent )
    bdf_char_max_ascent = bdf_char_ascent;
}

int bd_bits_per_0 = 5;
int bd_bits_per_1 = 5;
int bd_bits_per_char_width = 7;
int bd_bits_per_char_height = 7;
int bd_bits_per_char_x = 7;
int bd_bits_per_char_y = 7;
int bd_bits_per_delta_x = 7;



int bd_bitcnt;
int bd_last_0 = 0;
int bd_last_1 = 0;
int bd_is_first = 1;

int bd_out_byte_pos;
int bd_out_bit_pos;
#define BD_OUT_BUF_LEN 1024
unsigned char bd_out_buf[BD_OUT_BUF_LEN];

/* font decode */
struct _fd_struct
{
  unsigned char *ptr;
  unsigned bits_per_0;
  unsigned bits_per_1;
  
  unsigned decode_byte_pos;
  unsigned decode_bit_pos;
  unsigned glyph_width;
  unsigned glyph_height;
  
  unsigned x;
  unsigned y;
  
};
typedef struct _fd_struct fd_t;


unsigned char fd_get_bits(fd_t *fd, int cnt)
{
  unsigned char val;
  val = fd->ptr[fd->decode_byte_pos];
  val >>= fd->decode_bit_pos;
  if ( fd->decode_bit_pos + cnt < 8 )
  {
    val &= (1<<cnt) - 1;
  }
  /*
  else if ( fd->decode_bit_pos + cnt == 8 )
  {
    fd->decode_bit_pos = 0;
    fd->decode_byte_pos++;
  }
  */
  else
  {
    fd->decode_byte_pos++;
    val |= fd->ptr[fd->decode_byte_pos] << 8-fd->decode_bit_pos;
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

  fd->glyph_width = fd_get_bits(fd, bd_bits_per_char_width);
  fd->glyph_height = fd_get_bits(fd, bd_bits_per_char_height);

  fd_get_bits(fd, bd_bits_per_char_x);
  fd_get_bits(fd, bd_bits_per_char_y);
  fd_get_bits(fd, bd_bits_per_delta_x);

  
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

/*
  Desc:
    Output a field to the bitstream. The field size in bits is given by "cnt" and
    the value of the field is "val".
  Args:
    cnt:	Fieldsize in bits
    val:	The value (content) of the field. Sidecondition: val < (1<<cnt) && val >= 0
*/
void bd_out_bits(int cnt, int val)
{
  int i;
  
  assert( val < (1<<cnt) );
  assert(val >= 0 );
  
/*  
  printf("|");
  for( i = 0; i < cnt; i++)
  {
    printf("%c", ((val>>(cnt-1-i))&1) ? '1' : '0' );
  }
  printf("|");
*/
  
  bd_out_buf[bd_out_byte_pos] |= (val << bd_out_bit_pos);
  
  if ( bd_out_bit_pos+cnt >= 8 )
  {
/*    
    printf(" {%02x ", bd_out_buf[bd_out_byte_pos]);
    for( i = 0; i < 8; i++ )
    {
      printf("%c", ((bd_out_buf[bd_out_byte_pos]>>(8-1-i))&1) ? '1' : '0' );
    }
    printf("}");
*/
    
    val >>= 8-bd_out_bit_pos;
    bd_out_byte_pos++;
    bd_out_buf[bd_out_byte_pos] |= val;
    
    bd_out_bit_pos+=cnt;
    bd_out_bit_pos-=8;
    
  }
  else
  {
    bd_out_bit_pos+=cnt;
  }
}

/*
  Desc:
    Output a and b to the stream.
    a and b must fit to the target size in bits.
    Additionally a repeat code r (one bit) is generated:
    It may look like this:
      r = 0: 0aaaabb
    or 
      r = 1: 1
    If r is 0, then the number of zeros (a) and ones (b) will follow and both
    values must be stored as in the decoder.
    If r os 1, then the number of zeros and ones is repeated once
  Args:
    a: number of 0 bits, log2(a) must be smaller or equal to the fieldsize
    b: number of 1 bits, log2(b) must be smaller or equal to the fieldsize
    is_expand: obsolete?
*/
  
void bd_rle(int a, int b, int is_expand)
{
  if ( bd_is_first == 0 && bd_last_0 == a && bd_last_1 == b )
  {
    bd_bitcnt++;
    bd_out_bits(1, 1);
/*
    printf("*");
*/
  }
  else
  {   
/*
    if ( is_expand )
      printf(" [%02x, %02x]", a, b);
    else
      printf(" (%02x, %02x)", a, b);
*/
    if ( bd_is_first == 0 )
    {
      bd_out_bits(1, 0);
      bd_bitcnt++;
    }
    bd_out_bits(bd_bits_per_0, a);
    bd_out_bits(bd_bits_per_1, b);
    
    bd_is_first = 0;
    bd_bitcnt +=bd_bits_per_0;
    bd_bitcnt +=bd_bits_per_1;
    bd_last_0 = a;
    bd_last_1 = b;
  }
}

/*
  Desc:
    Write the number of zeros and ones to the bit stream.
    There is no restriction on the size of a and b.
  Args:
    a: number of 0 bits
    b: number of 1 bits
  
*/
void bd_expand(int a, int b)
{
  while( a >= (1<<bd_bits_per_0) -1 )
  {
    bd_rle((1<<bd_bits_per_0) -1, 0, 1);
    a -= (1<<bd_bits_per_0) -1;
  }
  while( b >= (1<<bd_bits_per_1) -1 )
  {
    bd_rle(a, (1<<bd_bits_per_1) -1, 1);
    a = 0;
    b -= (1<<bd_bits_per_1) -1;
  }
  if ( a != 0 || b != 0 )
    bd_rle(a, b, 0);
  
}

int bd_compress(void)
{
  int x,y, byte, bit, i;
  int gx, gy;
  char *p;
  int delta_pos;
  int delta_cnt[32];
  int bd_is_one;	/* bit delta */
  int bd_curr_len;
  int bd_max_len;
  int bd_chg_cnt;
  int bd_list[1024];
  
  gy = bdf_char_height - 1 + bdf_char_y; 
  
  bd_is_one = 0;
  bd_curr_len = 0;
  bd_max_len = 0;
  bd_chg_cnt = 0;
  bd_bitcnt = 0;
  bd_is_first = 1;

  bd_out_byte_pos = 0;
  bd_out_bit_pos = 0;


  for( i = 0; i < BD_OUT_BUF_LEN; i++ )
    bd_out_buf[i] = 0;

  bd_out_bits(bd_bits_per_char_width, bdf_char_width);
  bd_out_bits(bd_bits_per_char_height, bdf_char_height);

  bd_out_bits(bd_bits_per_char_x, bdf_char_x+(1<<(bd_bits_per_char_x-1)));
  bd_out_bits(bd_bits_per_char_y, bdf_char_y+(1<<(bd_bits_per_char_y-1)));
  bd_out_bits(bd_bits_per_delta_x, bdf_delta_x);

  for( y = 0; y < bdf_line_bm_line; y++ )
  {
    gx = bdf_char_x;
    delta_pos = 0;
    for( i = 0; i < 32; i++ )
      delta_cnt[i] = 0;
    for( x = 0; x < bdf_char_width; x++ )
    {
      byte = x >> 3;
      bit = 7-(x & 7);
            
      if ( (bdf_bitmap_line[y][byte] & (1<<bit)) == 0 )
      {
	if ( (delta_pos & 1 ) != 0 )
	  delta_pos++;
	delta_cnt[delta_pos]++;
	
	if ( bd_is_one != 0 )
	{
	  bd_list[bd_chg_cnt] = bd_curr_len;
	  bd_is_one = 0;
	  bd_chg_cnt++;
	  bd_curr_len = 0;
	}
	bd_curr_len++;
	
      }
      else
      {
	if ( (delta_pos & 1 ) == 0 )
	  delta_pos++;
	delta_cnt[delta_pos]++;

	if ( bd_is_one == 0 )
	{
	  bd_list[bd_chg_cnt] = bd_curr_len;
	  bd_is_one = 1;
	  bd_chg_cnt++;
	  bd_curr_len = 0;
	}
	bd_curr_len++;
	
      }
      
      if ( bd_max_len < bd_curr_len )
	bd_max_len = bd_curr_len;
      
      gx++;
    }
    gy--;
  }
  
  bd_list[bd_chg_cnt] = bd_curr_len;
  bd_chg_cnt++;
  if ( (bd_chg_cnt & 1) == 1 )
  {
    bd_list[bd_chg_cnt] = 0;
    bd_chg_cnt++;
  }
  for( i = 0; i < bd_chg_cnt; i+=2 )
  {
    //printf( " (%02x %02x)", bd_list[i], bd_list[i+1]);
    bd_expand(bd_list[i], bd_list[i+1]);
  }
  bd_out_bits(1, 0);		// ensure that there is a 0 bit at the end.
#ifdef VERBOSE
  printf("bd_max_len = %d, bd_chg_cnt = %d, (bdf_char_width+7)/8*bdf_line_bm_line = %d, bytes = %d, bytepos = %d bitpos=%d\n", 
    bd_max_len, bd_chg_cnt, (bdf_char_width+7)/8*bdf_line_bm_line, (bd_bitcnt+7)/8, bd_out_byte_pos, bd_out_bit_pos);
  printf("\n");
  //printf("%02x %02x %02x\n", bd_out_buf[0], bd_out_buf[1], bd_out_buf[2]);
  {
    fd_t fd;
    fd.ptr = bd_out_buf;
    fd.bits_per_0 = bd_bits_per_0;
    fd.bits_per_1 = bd_bits_per_1;
    fd.glyph_width = bdf_char_width;
    fd.glyph_height = bdf_char_height;
    fd_decode(&fd);
  }
  
  printf("\n");
#endif /* VERBOSE */
  /* return the size of the compressed data stream (bd_out_buf) */
  return bd_out_byte_pos + (bd_out_bit_pos==0?0:1);
}

void bdf_ShowGlyph(void)
{
  int x,y, byte, bit, i;
  int gx, gy;
  char *p;
  int delta_pos;
  int delta_cnt[32];
  int bd_is_one;	/* bit delta */
  int bd_curr_len;
  int bd_max_len;
  int bd_chg_cnt;
  int bd_list[1024];
  
  gy = bdf_char_height - 1 + bdf_char_y; 
  
#ifdef VERBOSE  
  printf("bbx %d %d %d %d encoding %d\n", bdf_char_width, bdf_char_height, bdf_char_x, bdf_char_y, bdf_encoding);
  bd_is_one = 0;
  bd_curr_len = 0;
  bd_max_len = 0;
  bd_chg_cnt = 0;
  bd_bitcnt = 0;
  bd_is_first = 1;
  for( y = 0; y < bdf_line_bm_line; y++ )
  {
    printf("%02d ", gy);
    gx = bdf_char_x;
    delta_pos = 0;
    for( i = 0; i < 32; i++ )
      delta_cnt[i] = 0;
    for( x = 0; x < bdf_char_width; x++ )
    {
      byte = x >> 3;
      bit = 7-(x & 7);
      
      
      if ( (bdf_bitmap_line[y][byte] & (1<<bit)) == 0 )
      {
	if ( (delta_pos & 1 ) != 0 )
	  delta_pos++;
	delta_cnt[delta_pos]++;
	
	if ( bd_is_one != 0 )
	{
	  bd_list[bd_chg_cnt] = bd_curr_len;
	  bd_is_one = 0;
	  bd_chg_cnt++;
	  bd_curr_len = 0;
	}
	bd_curr_len++;
	
        p = " .";
      }
      else
      {
	if ( (delta_pos & 1 ) == 0 )
	  delta_pos++;
	delta_cnt[delta_pos]++;

	if ( bd_is_one == 0 )
	{
	  bd_list[bd_chg_cnt] = bd_curr_len;
	  bd_is_one = 1;
	  bd_chg_cnt++;
	  bd_curr_len = 0;
	}
	bd_curr_len++;
	
        p = " *";
      }
      
      if ( bd_max_len < bd_curr_len )
	bd_max_len = bd_curr_len;
      
      if ( gy == 0 && gx == 0 )
        p = " o";
      printf("%s", p);
      gx++;
    }
    printf(" ");
    
    for( x = 0; x < ((bdf_char_width+7)/8); x++ )
    {
      printf( "%02x", bdf_bitmap_line[y][x]);
    }
    
    for( i = 0; i <= delta_pos; i++ )
    {
      printf( " %02x", delta_cnt[i]);
    }
    
    
    gy--;
    printf("\n");
  }
  
  /*
  bd_list[bd_chg_cnt] = bd_curr_len;
  bd_chg_cnt++;
  if ( (bd_chg_cnt & 1) == 1 )
  {
    bd_list[bd_chg_cnt] = 0;
    bd_chg_cnt++;
  }
  for( i = 0; i < bd_chg_cnt; i+=2 )
  {
    bd_expand(bd_list[i], bd_list[i+1]);
  }
  */
  
#else
  printf("bbx %d %d %d %d encoding %d\n", bdf_char_width, bdf_char_height, bdf_char_x, bdf_char_y, bdf_encoding);
  fflush(stdout);
#endif
}

void bdf_ClearGlyphBuffer(void)
{
  int x,y;
  for( y = 0; y < BDF_MAX_HEIGHT; y++ )
    for( x = 0; x < 20; x++ )
      bdf_bitmap_line[y][x] = 0;
}

void bdf_PutGlyph(void)
{
  int len, i;
  int y, x;
  
  
  if ( bdf_state == BDF_STATE_ENCODING )
  {
    /*
    if ( bdf_char_width == 0 && bdf_char_height == 0 )
      bdf_char_y = 0;
    */

    bdf_char_ascent = bdf_char_height + bdf_char_y;
    //printf("h:%d w:%d ascent: %d\n", bdf_char_height, bdf_char_width, bdf_char_ascent);

    if ( bdf_encoding == 'A' )
      bdf_capital_A_height = bdf_char_height;
    if ( bdf_encoding == '1' )
      bdf_capital_1_height = bdf_char_height;
    
    if ( bdf_encoding == 'g' )
      bdf_lower_g_descent = bdf_char_y;

    if ( bdf_char_xascent < bdf_capital_A_height )
      bdf_char_xascent = bdf_capital_A_height;
    if ( bdf_char_xascent < bdf_capital_1_height )
      bdf_char_xascent = bdf_capital_1_height;
    if ( bdf_encoding == '(' )
      if ( bdf_char_xascent < bdf_char_ascent )
        bdf_char_xascent = bdf_char_ascent;
    if ( bdf_encoding == '[' )
      if ( bdf_char_xascent < bdf_char_ascent )
        bdf_char_xascent = bdf_char_ascent;

    if ( bdf_char_xdescent > bdf_lower_g_descent )
      bdf_char_xdescent = bdf_lower_g_descent;
    if ( bdf_encoding == '(' )
      if ( bdf_char_xdescent > bdf_char_y )
        bdf_char_xdescent = bdf_char_y;
    if ( bdf_encoding == '[' )
      if ( bdf_char_xdescent > bdf_char_y )
        bdf_char_xdescent = bdf_char_y;

    if ( bdf_requested_encoding != bdf_encoding )
      return;

    assert( bdf_line_bm_line == bdf_char_height);

    bdf_ShowGlyph();
    
    len = bd_compress();
    
    bdf_UpdateMax();
    
    if ( len > 255 )
    {
      fprintf(stderr, "Glyph with encoding %d is too large (%d > 255)\n", bdf_encoding, len);
      exit(1);
    }
    
    
    bdf_glyph_data_len = len;

  /*
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
    
      data_Put(bdf_encoding);    
      data_Put(bdf_glyph_data_len+2);
      //data_Put(bdf_char_width);
      //data_Put(bdf_char_height);
      //data_Put(bdf_delta_x);
      //data_Put(bdf_char_x);
      //data_Put(bdf_char_y);
      bdf_is_encoding_successfully_done = 1;

    printf("encoding %d %c, bbx w=%d h=%d x=%d y=%d dx=%d dx-w=%d bdf_glyph_data_len=%d\n", 
      bdf_encoding,
      bdf_encoding > 32 && bdf_encoding <= 'z' ? bdf_encoding : ' ',
      bdf_char_width,
      bdf_char_height,
      bdf_char_x,
      bdf_char_y,
      bdf_delta_x,
      bdf_delta_x - bdf_char_width, bdf_glyph_data_len);

    sprintf(bdf_info+strlen(bdf_info), "/* encoding %d %c, bbx %d %d %d %d  asc %d dx %d*/\n", 
      bdf_encoding,
      bdf_encoding > 32 && bdf_encoding <= 'z' ? bdf_encoding : ' ',
      bdf_char_width,
      bdf_char_height,
      bdf_char_x,
      bdf_char_y,
      bdf_char_ascent,
      bdf_delta_x);

    for( i = 0; i < bdf_glyph_data_len; i++ )
    {
      data_Put(bd_out_buf[i]);
    }
    

    bdf_glyph_cnt++;

    bdf_is_put_glyph_completed = 1;
  }
}

/*=========================================================================*/
/* Glyph Clipping */

int bdf_IsColZero(int x)
{
  int y, byte, bit;
  for( y = 0; y < bdf_char_height; y++ )
  {
    byte = x >> 3;
    bit = 7-(x & 7);
    if ( (bdf_bitmap_line[y][byte] & (1<<bit)) != 0 )
      return 0;
  }
  return 1;
}

int bdf_IsRowZero(int y)
{
  int x, byte, bit;
  for( x = 0; x < bdf_char_width; x++ )
  {
    byte = x >> 3;
    bit = 7-(x & 7);
    if ( (bdf_bitmap_line[y][byte] & (1<<bit)) != 0 )
      return 0;
  }
  return 1;
}

void bdf_DeleteFirstCol(void)
{
  int m = (bdf_char_width+7)/8;
  int x,y;
  for( y = 0; y < bdf_char_height; y++ )
    for( x = 0; x < m; x++ )
    {
      bdf_bitmap_line[y][x] <<= 1;
      bdf_bitmap_line[y][x] |= bdf_bitmap_line[y][x+1] >> 7;
    }
}

void bdf_DeleteFirstRow(void)
{
  int m = (bdf_char_width+7)/8;
  int x,y;
  for( y = 0; y+1 < bdf_char_height; y++ )
    for( x = 0; x < m; x++ )
    {
      bdf_bitmap_line[y][x] = bdf_bitmap_line[y+1][x];
    }
}

void bdf_ReduceGlyph(void)
{
  while( bdf_char_width > 0 )
  {
    if ( bdf_IsColZero(bdf_char_width-1) == 0 )
      break;
    bdf_char_width--;
  }

  while( bdf_char_height > 0 )
  {
    if ( bdf_IsRowZero(bdf_char_height-1) == 0 )
      break;
    bdf_line_bm_line--;
    bdf_char_height--;
    bdf_char_y++;
  }
  
  while( bdf_IsColZero(0) != 0 && bdf_char_width > 0)
  {
    bdf_DeleteFirstCol();
    bdf_char_x++;
    bdf_char_width--;
  }
  
  while( bdf_char_height > 0 )
  {
    if ( bdf_IsRowZero(0) == 0 )
      break;
    bdf_DeleteFirstRow();
    bdf_line_bm_line--;
    bdf_char_height--;
  }
}


/*=========================================================================*/
/* Parser */

void bdf_ReadLine(const char *s)
{
  /*
  if ( bdf_line_state == BDF_LINE_STATE_BITMAP && bdf_requested_encoding != bdf_encoding && *s != 'E' )
    return;
  */
  
  if ( p_first_char(s) == 0 )
    return;
  
  if ( p_skip_space() == 0 )
    return;
  
  if ( bdf_line_state == BDF_LINE_STATE_KEYWORDS )
  {
    p_get_identifier();
    if ( strcmp(p_buf, "COPYRIGHT") == 0 )
    {
      p_get_any();
      strcpy(bdf_copyright, p_buf);
    }
    else if ( strcmp(p_buf, "FONT") == 0 )
    {
      /* p_get_any(); */
      p_get_identifier_with_blank();
      strcpy(bdf_font, p_buf);
    }
    else if ( strcmp(p_buf, "SIZE") == 0 )
    {
      bdf_font_size = p_get_val();
    }
    else if ( strcmp(p_buf, "ENCODING") == 0 )
    {
      bdf_encoding = map_UnicodeToU8G(p_get_val());      
      bdf_StoreFilePos(bdf_encoding, bdf_last_line_start_pos);
    }
    else if ( strcmp(p_buf, "DWIDTH") == 0 )
    {
      bdf_delta_x = p_get_val();
      bdf_delta_y = p_get_val();
    }
    else if ( strcmp(p_buf, "FONTBOUNDINGBOX") == 0 )
    {
      bdf_font_width = p_get_val();
      bdf_font_height = p_get_val();
      bdf_font_x = p_get_val();
      bdf_font_y = p_get_val();
    }
    else if ( strcmp(p_buf, "BBX") == 0 )
    {
      bdf_char_width = p_get_val();
      bdf_char_height = p_get_val();
      bdf_char_x = p_get_val();
      bdf_char_y = p_get_val();
      bdf_char_ascent = bdf_char_height + bdf_char_y;
      //printf("h:%d w:%d ascent: %d\n", bdf_char_height, bdf_char_width, bdf_char_ascent);
    }
    else if ( strcmp(p_buf, "BITMAP") == 0 )
    {
      bdf_line_state = BDF_LINE_STATE_BITMAP;
      bdf_line_bm_line = 0;
    }
  }
  else if ( bdf_line_state == BDF_LINE_STATE_BITMAP )
  {
    if ( strncmp(s, "ENDCHAR", 7) == 0 )
    {
      bdf_ReduceGlyph();
      bdf_PutGlyph();
      bdf_line_state = BDF_LINE_STATE_KEYWORDS;
      bdf_line_bm_line = 0;
    }
    else
    {
      if ( bdf_requested_encoding == bdf_encoding )
      {

        int i = 0;
        for(;;)
        {
          if ( p_current_char < '0' )
            break;
          bdf_bitmap_line[bdf_line_bm_line][i] = p_get_hex_byte();
          i++;
        }
        bdf_line_bm_line++;
        assert(bdf_line_bm_line < BDF_MAX_HEIGHT);
      }
    }
  }
}


int bdf_ReadFP(FILE *fp)
{
  static char bdf_line[BDF_LINE_MAX];
  bdf_is_put_glyph_completed = 0;
  for(;;)
  {
    bdf_last_line_start_pos = ftell(fp);
    if ( fgets(bdf_line, BDF_LINE_MAX-1, fp) == NULL )
      break;
    bdf_ReadLine(bdf_line);
    if ( bdf_is_put_glyph_completed != 0 )
      break;
  }
  return 1;
}

int bdf_ReadFile(const char *filename, int encoding)
{
  int r;
  FILE *fp;
  fp = fopen(filename, "rb");
  if ( fp != NULL )
  {
    bdf_SetFilePos(fp, encoding);
    r = bdf_ReadFP(fp);
    fclose(fp);
    return r;
  }
  return 0; /* open error */
}

void bdf_GenerateFontData(const char *filename, int begin, int end)
{
  bdf_state = BDF_STATE_FONT_DATA;
  bdf_ReadFile(filename, -1);
  /*
  font information 
  offset
  0		number of glyphs in the font (1x byte)
  1		decode algorithm: bits for 0
  2		decode algorithm: bits for 1
  3		bits_per_char_width
  4		bits_per_char_height
  5		bits_per_char_x
  6		bits_per_char_y
  7		bits_per_delta_x
  
  */
  data_Put(0);                  
  data_Put(bd_bits_per_0);                  
  data_Put(bd_bits_per_1);

  data_Put(bd_bits_per_char_width);
  data_Put(bd_bits_per_char_height);
  data_Put(bd_bits_per_char_x);
  data_Put(bd_bits_per_char_y);
  data_Put(bd_bits_per_delta_x);

}

void bdf_GenerateGlyph(const char *filename, int encoding)
{
  bdf_ClearGlyphBuffer();
  bdf_requested_encoding = encoding;
  bdf_state = BDF_STATE_ENCODING;
  bdf_ReadFile(filename, encoding);
}

void bdf_Generate(const char *filename, int begin, int end)
{
  int i;
  int last_valid_encoding;

  bdf_encoding_65_pos = 0;
  bdf_encoding_97_pos = 0;
  bdf_glyph_cnt = 0;

  bdf_InitFilePos();
  bdf_ResetMax();
  bdf_info[0] = '\0'; 
  bdf_font[0] = '\0';
  bdf_copyright[0] = '\0';
  
  bdf_GenerateFontData(filename, begin, end);
  for( i = begin; i <= end; i++ )
  {
    
    if ( i == 65 )
      bdf_encoding_65_pos = data_pos;
    if ( i == 97 )
      bdf_encoding_97_pos = data_pos;
    
    bdf_is_encoding_successfully_done = 0;
    if ( bdf_IsEncodingAvailable(i) )
    {
      bdf_GenerateGlyph(filename, i);
    }
    /*
    if ( bdf_is_encoding_successfully_done == 0 )
      data_Put(255);
    */
    if ( bdf_is_encoding_successfully_done != 0 )
      last_valid_encoding = i;
  }
  /* data_Put(255); obsolete, not required any more for format 0 */         /* encoding 255, end of font data (format 0) */
  data_buf[0] = bdf_glyph_cnt;
  
  // data_buf[11] = last_valid_encoding;
  
}

void bdf_WriteC(const char *outname, const char *fontname)
{
  int capital_ascent;
  FILE *out_fp;
  out_fp = fopen(outname, "wb");
  assert( out_fp != NULL );

  if ( bdf_capital_A_height > 0 )
    capital_ascent = bdf_capital_A_height;
  else
    capital_ascent = bdf_capital_1_height;

  fprintf(out_fp, "/*\n");
  fprintf(out_fp, "  Fontname: %s\n", bdf_font);
  fprintf(out_fp, "  Copyright: %s\n", bdf_copyright);
  fprintf(out_fp, "  Capital A Height: %d, '1' Height: %d\n", bdf_capital_A_height, bdf_capital_1_height);
  fprintf(out_fp, "  Calculated Max Values w=%2d h=%2d x=%2d y=%2d dx=%2d dy=%2d ascent=%2d len=%2d\n", 
    bdf_char_max_width, bdf_char_max_height, bdf_char_max_x, bdf_char_max_y, bdf_delta_max_x, bdf_delta_max_y, 
    bdf_char_max_ascent, bdf_glyph_data_max_len);
  fprintf(out_fp, "  Font Bounding box     w=%2d h=%2d x=%2d y=%2d\n", 
    bdf_font_width, bdf_font_height, bdf_font_x, bdf_font_y);
  fprintf(out_fp, "  Calculated Min Values           x=%2d y=%2d dx=%2d dy=%2d\n", 
    bdf_char_min_x, bdf_char_min_y, bdf_delta_min_x, bdf_delta_min_y);

  fprintf(out_fp, "  Pure Font   ascent =%2d descent=%2d\n", capital_ascent, bdf_lower_g_descent);
  fprintf(out_fp, "  X Font      ascent =%2d descent=%2d\n", bdf_char_xascent, bdf_char_xdescent);
  fprintf(out_fp, "  Max Font    ascent =%2d descent=%2d\n", bdf_char_max_ascent, bdf_char_min_y);

  fprintf(out_fp, "*/\n");
  //fprintf(out_fp, "#include \"u8g.h\"\n");  
  fprintf(out_fp, "const unsigned char %s[%d] = {\n", fontname, data_pos);
  fprintf(out_fp, "  ");
  data_Write(out_fp, "  ");
  fprintf(out_fp, "};\n");
  
  printf("font size: %d bytes\n", data_pos);
#ifdef BDF2U8G_COMPACT_OUTPUT
#else
  fprintf(out_fp, "%s\n", bdf_info);
#endif

  fclose(out_fp);
}



int ga_argc;
char **ga_argv;


void ga_remove_arg(void)
{
  if ( ga_argc == 0 )
    return;
  ga_argc--;
  ga_argv++;
}

int ga_is_arg(char opt)
{
  if ( ga_argc == 0 )
    return 0;
  if ( ga_argv[0] == NULL )
    return 0;
  if ( ga_argv[0][0] != '-' )
    return 0;
  if ( ga_argv[0][1] != opt )
    return 0;
  ga_remove_arg();
  return 1;
}


int main(int argc, char **argv)
{
  int lower_page = 0;
  int upper_page = 1;
  int mapping_shift = 0;
  int upper_mapping_shift = 0;
  int begin = 32;
  int end = 255;
  
  if ( argc < 4 )
  {
    printf("bdf to bin font format converter v" BDF2U8G_VERSION "\n");
    printf("%s [-l page] [-u page] [-s shift] [-S upper-shift] [-b begin] [-e end] [-0 bits per 0] [-1 bits per 1] [-w bits per width] [-h bits per height] [-x bits per xoff] [-y bits per yofft] [-d bits per xdelta] fontfile fontname outputfile\n", argv[0]);
    return 1;
  }
  
  ga_argc = argc;
  ga_argv = argv;
  ga_remove_arg();              /* remove program name */
  
  for(;;)
  {
    if ( ga_is_arg('l') )
    {
      lower_page = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('u') )
    {
      upper_page = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('s') )
    {
      mapping_shift = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('S') )
    {
      upper_mapping_shift = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('b') )
    {
      begin = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('e') )
    {
      end = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    /*
    else if ( ga_is_arg('f') )
    {
      bdf_font_format = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    */
    else if ( ga_is_arg('0') )
    {
      bd_bits_per_0 = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('1') )
    {
      bd_bits_per_1 = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('w') )
    {
      bd_bits_per_char_width = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('h') )
    {
      bd_bits_per_char_height = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('x') )
    {
      bd_bits_per_char_x = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('y') )
    {
      bd_bits_per_char_y = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    else if ( ga_is_arg('d') )
    {
      bd_bits_per_delta_x = atoi(ga_argv[0]);
      ga_remove_arg();      
    }
    
    
    else 
      break;
  }
  
  printf("encoding range %d..%d\n", begin, end);
  
  data_Init();
  map_Init();
  map_UpperLowerPage(lower_page, upper_page, mapping_shift, upper_mapping_shift);
  
  /*
  puts(bdf_font);
  puts(bdf_copyright);
  if ( ga_argc < 3 )
  {
    printf("from page %d to page %d\n", lower_page, upper_page);
    return 1;
  }  
  */
  
  bdf_Generate(ga_argv[0], begin, end);
  bdf_WriteC(ga_argv[2], ga_argv[1]);

  printf("input file '%s'\n", ga_argv[0]);
  printf("u8g font name '%s'\n", ga_argv[1]);  
  printf("output file '%s'\n", ga_argv[2]);
  
  return 0;
}

