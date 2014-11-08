
#ifndef _OLED_H
#define _OLED_H

#define WIDTH 128
#define HEIGHT 64

struct _oled_struct
{
  /* font information */
  const unsigned char *font;		/* pointer to the first glyph information */
  
  unsigned glyph_cnt;
  unsigned bits_per_0;
  unsigned bits_per_1;

  /* glyph information */
  const unsigned char *glyph_data;
  unsigned glyph_width;
  unsigned glyph_height;
  unsigned glyph_delta;
  int x_offset;
  int y_offset;

  /* glyph decode algorithm */
  const unsigned char *decode_ptr;
  unsigned decode_byte_pos;
  unsigned decode_bit_pos;
  
  unsigned x;
  unsigned y;

  /* oled low level */
  uint32_t page_start;		/* start row of page */
  uint8_t oled_display_page[WIDTH];
  
};

typedef struct _oled_struct oled_t;

extern oled_t oled_o;


extern const unsigned char logisoso46[];
extern const unsigned char helvR14[];

void oled_init(void);
void oled_set_font(oled_t *oled, const unsigned char *font);
unsigned oled_draw_glyph(oled_t *oled, unsigned x, unsigned y, unsigned encoding);
unsigned oled_draw_string(oled_t *oled, unsigned x, unsigned y, const char *s);
void oled_start_page(oled_t *oled);
int oled_next_page(oled_t *oled);


#endif
