/*

  u8g.h
  
  Universal 8bit Graphics Library
  
  Copyright (c) 2011, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  
*/

#ifndef _U8G_H
#define _U8G_H

#include <stddef.h>
#include <stdint.h>

#if defined(__AVR__)
#include <avr/pgmspace.h>
#endif 

#ifdef __cplusplus
extern "C" {
#endif

  
/*===============================================================*/
#ifdef __GNUC__
#define U8G_NOINLINE __attribute__((noinline))
#define U8G_PURE  __attribute__ ((pure))
#else
#define U8G_NOINLINE
#define U8G_PURE
#endif
  
/*===============================================================*/
/* flash memory access */

#if defined(__AVR__)
typedef uint8_t PROGMEM u8g_pgm_uint8_t;
#define u8g_pgm_read(adr) pgm_read_byte_near(adr)
#define U8G_PSTR(s) PSTR(s)
#else
typedef uint8_t u8g_pgm_uint8_t;
#define u8g_pgm_read(adr) (*(const u8g_pgm_uint8_t *)(adr)) 
#define U8G_PSTR(s) (s)
#endif
  
/*===============================================================*/
/* forward */
typedef struct _u8g_t u8g_t;
typedef struct _u8g_dev_t u8g_dev_t;


/*===============================================================*/
/* generic */
#if defined(U8G_16BIT)
typedef uint16_t u8g_uint_t;
#else
typedef uint8_t u8g_uint_t;
#endif

struct _u8g_box_t
{
  u8g_uint_t x0, y0, x1, y1;  
};
typedef struct _u8g_box_t u8g_box_t;


/*===============================================================*/
/* device list */


/* Size: 128x64 SDL, u8g_dev_sdl.c */
extern u8g_dev_t u8g_dev_sdl_1bit;
extern u8g_dev_t u8g_dev_sdl_2bit;
int u8g_sdl_get_key(void);

/* Size: 70x30 monochrom, stdout */
extern u8g_dev_t u8g_dev_stdout;

/* Size: monochrom, writes "u8g.pbm" */
extern u8g_dev_t u8g_dev_pbm;

/* Size: 128x64 monochrom, no output, used for performance measure */
extern u8g_dev_t u8g_dev_gprof;

/* Display: EA DOGS102, Size: 102x64 monochrom */
extern u8g_dev_t u8g_dev_uc1701_dogs102_sw_spi;
extern u8g_dev_t u8g_dev_uc1701_dogs102_hw_spi;

/* Display: EA DOGM128, Size: 128x64 monochrom */
extern u8g_dev_t u8g_dev_st7565_dogm128_sw_spi;
extern u8g_dev_t u8g_dev_st7565_dogm128_hw_spi;

/* Display: EA DOGXL160, Size: 160x104 monochrom & gray level */
extern u8g_dev_t u8g_dev_uc1610_dogxl160_bw_sw_spi;
extern u8g_dev_t u8g_dev_uc1610_dogxl160_bw_hw_spi;
extern u8g_dev_t u8g_dev_uc1610_dogxl160_gr_sw_spi;
extern u8g_dev_t u8g_dev_uc1610_dogxl160_gr_hw_spi;

/* Display: Generic KS0108b, Size: 128x64 monochrom */
extern u8g_dev_t u8g_dev_ks0108_128x64;         /* official Arduino Library interface */
extern u8g_dev_t u8g_dev_ks0108_128x64_fast;    /* faster, but uses private tables from the Arduino Library */

/* Nokia 84x48 Display with PCD8544 */
extern u8g_dev_t u8g_dev_pcd8544_84x48_sw_spi;
/* Nokia 96x65 Display with PCF8812 */
extern u8g_dev_t u8g_dev_pcf8812_96x65_sw_spi;

/* NHD-2.7-12864UCY3 OLED Display with SSD1325 Controller */
extern u8g_dev_t u8g_dev_ssd1325_nhd27oled_bw_sw_spi;
extern u8g_dev_t u8g_dev_ssd1325_nhd27oled_bw_hw_spi;


/*===============================================================*/
/* device messages */

struct _u8g_dev_arg_pixel_t
{
  u8g_uint_t x, y;              /* will be modified */
  uint8_t pixel;                  /* will be modified */
  uint8_t dir;
  uint8_t color;
};
typedef struct _u8g_dev_arg_pixel_t u8g_dev_arg_pixel_t;

struct _u8g_dev_arg_bbx_t
{
  u8g_uint_t x, y, w, h;
};
typedef struct _u8g_dev_arg_bbx_t u8g_dev_arg_bbx_t;

#define U8G_DEV_MSG_INIT                10
#define U8G_DEV_MSG_STOP                  11

#define U8G_DEV_MSG_PAGE_FIRST                  20
#define U8G_DEV_MSG_PAGE_NEXT                    21

/* arg: u8g_dev_arg_bbx_t * */
#define U8G_DEV_MSG_IS_BBX_INTERSECTION 22

/*
#define U8G_DEV_MSG_PRIMITIVE_START             30
#define U8G_DEV_MSG_PRIMITIVE_END               31
*/

/* arg: u8g_dev_arg_pixel_t * */
#define U8G_DEV_MSG_SET_PIXEL                           50
#define U8G_DEV_MSG_SET_8PIXEL                          59

#define U8G_DEV_MSG_SET_COLOR_INDEX                60

#define U8G_DEV_MSG_SET_XY_CB                           61

#define U8G_DEV_MSG_GET_WIDTH                           70
#define U8G_DEV_MSG_GET_HEIGHT                           71


/*===============================================================*/
/* com messages */

#define U8G_COM_MSG_STOP        0
#define U8G_COM_MSG_INIT        1

#define U8G_COM_MSG_ADDRESS 2

/* CHIP_SELECT argument: number of the chip which needs to be activated, so this is more like high active */
#define U8G_COM_MSG_CHIP_SELECT 3

#define U8G_COM_MSG_RESET 4

#define U8G_COM_MSG_WRITE_BYTE 5
#define U8G_COM_MSG_WRITE_SEQ 6
#define U8G_COM_MSG_WRITE_SEQ_P 7





/* com driver */
uint8_t u8g_com_null_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);               /* u8g_com_null.c */
uint8_t u8g_com_arduino_std_sw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);        /* u8g_com_arduino_std_sw_spi.c */
uint8_t u8g_com_arduino_sw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);        /* u8g_com_arduino_sw_spi.c */
uint8_t u8g_com_arduino_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);          /* u8g_com_arduino_hw_spi.c */
uint8_t u8g_com_arduino_parallel_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);           /* u8g_com_arduino_parallel.c */
uint8_t u8g_com_arduino_fast_parallel_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);      /* u8g_com_arduino_fast_parallel.c */

/*===============================================================*/
/* common init device structure */

/* device prototype */
typedef uint8_t (*u8g_dev_fnptr)(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);

/* com prototype */
typedef uint8_t (*u8g_com_fnptr)(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);


struct _u8g_dev_t
{
  u8g_dev_fnptr dev_fn;         /* device procedure */
  void *dev_mem;                /* device memory */
  u8g_com_fnptr com_fn;         /* communication procedure */
};


/*===============================================================*/
/* com api */
uint8_t u8g_InitCom(u8g_t *u8g, u8g_dev_t *dev);
void u8g_StopCom(u8g_t *u8g, u8g_dev_t *dev);
void u8g_EnableCom(u8g_t *u8g, u8g_dev_t *dev);         /* obsolete */
void u8g_DisableCom(u8g_t *u8g, u8g_dev_t *dev);        /* obsolete */
void u8g_SetChipSelect(u8g_t *u8g, u8g_dev_t *dev, uint8_t cs);
void u8g_SetResetLow(u8g_t *u8g, u8g_dev_t *dev);
void u8g_SetResetHigh(u8g_t *u8g, u8g_dev_t *dev);
void u8g_SetAddress(u8g_t *u8g, u8g_dev_t *dev, uint8_t address);
uint8_t u8g_WriteByte(u8g_t *u8g, u8g_dev_t *dev, uint8_t val);
uint8_t u8g_WriteSequence(u8g_t *u8g, u8g_dev_t *dev, uint8_t cnt, uint8_t *seq);
uint8_t u8g_WriteSequenceP(u8g_t *u8g, u8g_dev_t *dev, uint8_t cnt, u8g_pgm_uint8_t *seq);

#define U8G_ESC_DLY(x) 255, ((x) & 0x7f)
#define U8G_ESC_CS(x) 255, (0xd0 | ((x)&0x0f))
#define U8G_ESC_ADR(x) 255, (0xe0 | ((x)&0x0f))
#define U8G_ESC_RST(x) 255, (0xc0 | ((x)&0x0f))
#define U8G_ESC_END 255, 254
#define U8G_ESC_255 255, 255
uint8_t u8g_WriteEscSeqP(u8g_t *u8g, u8g_dev_t *dev, u8g_pgm_uint8_t *esc_seq);

/*===============================================================*/
/* u8g_arduino_common.c */
void u8g_com_arduino_digital_write(u8g_t *u8g, uint8_t pin_index, uint8_t value);
void u8g_com_arduino_assign_pin_output_high(u8g_t *u8g);


/*===============================================================*/
/* page */
struct _u8g_page_t
{
  u8g_uint_t page_height;
  u8g_uint_t total_height;
  u8g_uint_t page_y0;
  u8g_uint_t page_y1;
  uint8_t page;
};
typedef struct _u8g_page_t u8g_page_t;

void u8g_page_First(u8g_page_t *p) U8G_NOINLINE;                                                                                        /* u8g_page.c */
void u8g_page_Init(u8g_page_t *p, u8g_uint_t page_height, u8g_uint_t total_height ) U8G_NOINLINE;            /* u8g_page.c */
uint8_t u8g_page_Next(u8g_page_t *p) U8G_NOINLINE;                                                                                   /* u8g_page.c */

/*===============================================================*/
/* page buffer (pb) */

struct _u8g_pb_t
{
  u8g_page_t p;
  u8g_uint_t width;
  void *buf;
};
typedef struct _u8g_pb_t u8g_pb_t;


/* u8g_pb.c */
void u8g_pb_Clear(u8g_pb_t *b);
uint8_t u8g_pb_IsYIntersection(u8g_pb_t *pb, u8g_uint_t v0, u8g_uint_t v1);
uint8_t u8g_pb_IsXIntersection(u8g_pb_t *b, u8g_uint_t v0, u8g_uint_t v1);
uint8_t u8g_pb_IsIntersection(u8g_pb_t *pb, u8g_dev_arg_bbx_t *bbx);
uint8_t u8g_pb_Is8PixelVisible(u8g_pb_t *b, u8g_dev_arg_pixel_t *arg_pixel);
uint8_t u8g_pb_WriteBuffer(u8g_pb_t *b, u8g_t *u8g, u8g_dev_t *dev);

/*
  note on __attribute__ ((nocommon))
    AVR scripts often use  --gc-sections on the linker to remove unused section.
    This works fine for initialed data and text sections. In principle .bss is also
    handled, but the name##_pb definition is not removed. Reason is, that
    array definitions are placed in the COMMON section, by default
    The attribute "nocommon" removes this automatic assignment to the
    COMMON section and directly puts it into .bss. As a result, if more
    than one buffer is defined in one file, then it will be removed with --gc-sections

    .. not sure if Arduino IDE uses -fno-common... if yes, then the attribute is
    redundant.
*/
#define U8G_PB_DEV(name, width, height, page_height, dev_fn, com_fn) \
uint8_t name##_buf[width] __attribute__ ((nocommon)) ; \
u8g_pb_t name##_pb = { {page_height, height, 0, 0, 0},  width, name##_buf}; \
u8g_dev_t name = { dev_fn, &name##_pb, com_fn }


void u8g_pb8v1_Init(u8g_pb_t *b, void *buf, u8g_uint_t width)   U8G_NOINLINE;
void u8g_pb8v1_Clear(u8g_pb_t *b) U8G_NOINLINE;

uint8_t u8g_pb8v1_IsYIntersection(u8g_pb_t *b, u8g_uint_t v0, u8g_uint_t v1);
uint8_t u8g_pb8v1_IsXIntersection(u8g_pb_t *b, u8g_uint_t v0, u8g_uint_t v1);
uint8_t u8g_pb8v1_WriteBuffer(u8g_pb_t *b, u8g_t *u8g, u8g_dev_t *dev);

uint8_t u8g_dev_pb8v1_base_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);

/* u8g_pb8v2.c */
uint8_t u8g_dev_pb8v2_base_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);


/*===============================================================*/
/* u8g_ll_api.c */

typedef void (*u8g_draw_cursor_fn)(u8g_t *u8g);

/* PI = Pin Index */

/* reset pin, usually optional */
#define U8G_PI_RESET 0

/* address / data or instruction */
#define U8G_PI_A0 1
#define U8G_PI_DI 1

/* chip select line */
#define U8G_PI_CS 2
#define U8G_PI_CS1 2
#define U8G_PI_CS2 3

/* enable / clock signal */
#define U8G_PI_EN 4
#define U8G_PI_SCK 4


/* data pins, shared with SPI pins */
#define U8G_PI_D0 5
#define U8G_PI_MOSI 5
#define U8G_PI_D1 6
#define U8G_PI_MISO 6
#define U8G_PI_D2 7
#define U8G_PI_D3 8
#define U8G_PI_D4 9
#define U8G_PI_D5 10
#define U8G_PI_D6 11
#define U8G_PI_D7 12

/* read/write pin, must be the last pin in the list, this means U8G_PIN_LIST_LEN =  U8G_PI_RW + 1*/
#define U8G_PI_RW 13 

#define U8G_PIN_LIST_LEN 14


#define U8G_PIN_NONE 255

struct _u8g_t
{
  u8g_uint_t width;
  u8g_uint_t height;
  
  
  u8g_dev_t *dev;               /* first device in the device chain */
  const u8g_pgm_uint8_t *font;             /* regular font for all text procedures */
  const u8g_pgm_uint8_t *cursor_font;  /* special font for cursor procedures */
  uint8_t cursor_fg_color, cursor_bg_color;
  uint8_t cursor_encoding;
  u8g_uint_t cursor_x;
  u8g_uint_t cursor_y;
  u8g_draw_cursor_fn cursor_fn;
  
  int8_t glyph_dx;
  int8_t glyph_x;
  int8_t glyph_y;
  uint8_t glyph_width;
  uint8_t glyph_height;
  
  u8g_dev_arg_pixel_t arg_pixel;
  /* uint8_t color_index; */

  uint8_t pin_list[U8G_PIN_LIST_LEN];
};

uint8_t u8g_call_dev_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);

uint8_t u8g_InitLL(u8g_t *u8g, u8g_dev_t *dev);
void u8g_FirstPageLL(u8g_t *u8g, u8g_dev_t *dev);
uint8_t u8g_NextPageLL(u8g_t *u8g, u8g_dev_t *dev);
void u8g_DrawPixelLL(u8g_t *u8g, u8g_dev_t *dev, u8g_uint_t x, u8g_uint_t y);
void u8g_Draw8PixelLL(u8g_t *u8g, u8g_dev_t *dev, u8g_uint_t x, u8g_uint_t y, uint8_t dir, uint8_t pixel);
uint8_t u8g_IsBBXIntersectionLL(u8g_t *u8g, u8g_dev_t *dev, u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h);
u8g_uint_t u8g_GetWidthLL(u8g_t *u8g, u8g_dev_t *dev);
u8g_uint_t u8g_GetHeightLL(u8g_t *u8g, u8g_dev_t *dev);

void u8g_UpdateDimension(u8g_t *u8g);
uint8_t u8g_Init(u8g_t *u8g, u8g_dev_t *dev);   /* obsolete */
uint8_t u8g_InitSPI(u8g_t *u8g, u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset);
uint8_t u8g_InitHWSPI(u8g_t *u8g, u8g_dev_t *dev, uint8_t cs, uint8_t a0, uint8_t reset);
uint8_t u8g_Init8Bit(u8g_t *u8g, u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, 
  uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw, uint8_t reset);
void u8g_FirstPage(u8g_t *u8g);
uint8_t u8g_NextPage(u8g_t *u8g);
void u8g_DrawPixel(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y);
void u8g_Draw8Pixel(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t dir, uint8_t pixel);
uint8_t u8g_IsBBXIntersection(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h);

uint8_t u8g_Stop(u8g_t *u8g);
void u8g_SetColorIndex(u8g_t *u8g, uint8_t idx);
uint8_t u8g_GetColorIndex(u8g_t *u8g);

#define u8g_GetWidth(u8g) ((u8g)->width)
#define u8g_GetHeight(u8g) ((u8g)->height)


/* u8g_dev_rot.c */

void u8g_SetRot90(u8g_t *u8g);
void u8g_SetRot180(u8g_t *u8g);
void u8g_SetRot270(u8g_t *u8g);


/* u8g_font.c */

size_t u8g_font_GetSize(const void *font);
uint8_t u8g_font_GetFontStartEncoding(const void *font) U8G_NOINLINE;
uint8_t u8g_font_GetFontEndEncoding(const void *font) U8G_NOINLINE;

void u8g_SetFont(u8g_t *u8g, const u8g_pgm_uint8_t *font);

uint8_t u8g_GetFontBBXWidth(u8g_t *u8g);
uint8_t u8g_GetFontBBXHeight(u8g_t *u8g);
int8_t u8g_GetFontBBXOffX(u8g_t *u8g);
int8_t u8g_GetFontBBXOffY(u8g_t *u8g);
uint8_t u8g_GetFontCapitalAHeight(u8g_t *u8g);

uint8_t u8g_IsGlyph(u8g_t *u8g, uint8_t requested_encoding);


int8_t u8g_DrawGlyphDir(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t dir, uint8_t encoding);
int8_t u8g_DrawGlyph(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t encoding);
int8_t u8g_DrawGlyph90(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t encoding);
int8_t u8g_DrawGlyph180(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t encoding);
int8_t u8g_DrawGlyph270(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t encoding);
int8_t u8g_DrawGlyphFontBBX(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t dir, uint8_t encoding);

u8g_uint_t u8g_DrawStr(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, const char *s);
u8g_uint_t u8g_DrawStr90(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, const char *s);
u8g_uint_t u8g_DrawStr180(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, const char *s);
u8g_uint_t u8g_DrawStr270(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, const char *s);

u8g_uint_t u8g_DrawStrDir(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t dir, const char *s);


u8g_uint_t u8g_DrawStrP(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, const u8g_pgm_uint8_t *s);
u8g_uint_t u8g_DrawStr90P(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, const u8g_pgm_uint8_t *s);
u8g_uint_t u8g_DrawStr180P(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, const u8g_pgm_uint8_t *s);
u8g_uint_t u8g_DrawStr270P(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, const u8g_pgm_uint8_t *s);



u8g_uint_t u8g_DrawStrFontBBX(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t dir, const char *s);


void u8g_GetStrMinBox(u8g_t *u8g, const char *s, u8g_uint_t *x, u8g_uint_t *y, u8g_uint_t *width, u8g_uint_t *height);
void u8g_GetStrAMinBox(u8g_t *u8g, const char *s, u8g_uint_t *x, u8g_uint_t *y, u8g_uint_t *width, u8g_uint_t *height);

/* u8g_rect.c */

void u8g_DrawHLine(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t w);
void u8g_DrawVLine(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t w);
void u8g_DrawFrame(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h);
void u8g_DrawBox(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h);

/* u8g_bitmap.c */

void u8g_DrawHBitmap(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t cnt, const uint8_t *bitmap);
void u8g_DrawHBitmapP(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t cnt, const u8g_pgm_uint8_t *bitmap);
void u8g_DrawBitmap(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t cnt, u8g_uint_t h, const uint8_t *bitmap);
void u8g_DrawBitmapP(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t cnt, u8g_uint_t h, const u8g_pgm_uint8_t *bitmap);

/* u8g_cursor.c */
void u8g_SetCursorFont(u8g_t *u8g, const u8g_pgm_uint8_t *cursor_font);
void u8g_SetCursorStyle(u8g_t *u8g, uint8_t encoding);
void u8g_SetCursorPos(u8g_t *u8g, u8g_uint_t cursor_x, u8g_uint_t cursor_y);
void u8g_SetCursorColor(u8g_t *u8g, uint8_t fg, uint8_t bg);
void u8g_EnableCursor(u8g_t *u8g);
void u8g_DisableCursor(u8g_t *u8g);
void u8g_DrawCursor(u8g_t *u8g);



/*===============================================================*/
void st_Draw(uint8_t fps);
void st_Step(uint8_t player_pos, uint8_t is_auto_fire, uint8_t is_fire);

/*===============================================================*/
/* u8g_u8toa.c */

/* v = value, d = number of digits */
const char *u8g_u8toa(uint8_t v, uint8_t d);




/*===============================================================*/
/* u8g_delay.c */

/* delay by the specified number of milliseconds */
void u8g_Delay(uint16_t val);

/*===============================================================*/
/* font definitions */

extern const u8g_pgm_uint8_t u8g_font_10x20_67_75[];
extern const u8g_pgm_uint8_t u8g_font_10x20_78_79[];
extern const u8g_pgm_uint8_t u8g_font_10x20[];
extern const u8g_pgm_uint8_t u8g_font_10x20r[];
extern const u8g_pgm_uint8_t u8g_font_4x6[];
extern const u8g_pgm_uint8_t u8g_font_4x6r[];
//extern const u8g_pgm_uint8_t u8g_font_4x6n[];
extern const u8g_pgm_uint8_t u8g_font_5x7[];
extern const u8g_pgm_uint8_t u8g_font_5x7r[];
extern const u8g_pgm_uint8_t u8g_font_5x8[];
extern const u8g_pgm_uint8_t u8g_font_5x8r[];
extern const u8g_pgm_uint8_t u8g_font_6x10[];
extern const u8g_pgm_uint8_t u8g_font_6x10r[];
extern const u8g_pgm_uint8_t u8g_font_6x12_67_75[];
extern const u8g_pgm_uint8_t u8g_font_6x12_78_79[];
extern const u8g_pgm_uint8_t u8g_font_6x12[];
extern const u8g_pgm_uint8_t u8g_font_6x12r[];
extern const u8g_pgm_uint8_t u8g_font_6x13_67_75[];
extern const u8g_pgm_uint8_t u8g_font_6x13_78_79[];
extern const u8g_pgm_uint8_t u8g_font_6x13B[];
extern const u8g_pgm_uint8_t u8g_font_6x13Br[];
extern const u8g_pgm_uint8_t u8g_font_6x13[];
extern const u8g_pgm_uint8_t u8g_font_6x13r[];
extern const u8g_pgm_uint8_t u8g_font_6x13O[];
extern const u8g_pgm_uint8_t u8g_font_6x13Or[];
extern const u8g_pgm_uint8_t u8g_font_7x13_67_75[];
extern const u8g_pgm_uint8_t u8g_font_7x13_78_79[];
extern const u8g_pgm_uint8_t u8g_font_7x13B[];
extern const u8g_pgm_uint8_t u8g_font_7x13Br[];
extern const u8g_pgm_uint8_t u8g_font_7x13[];
extern const u8g_pgm_uint8_t u8g_font_7x13r[];
extern const u8g_pgm_uint8_t u8g_font_7x13O[];
extern const u8g_pgm_uint8_t u8g_font_7x13Or[];
extern const u8g_pgm_uint8_t u8g_font_7x14B[];
extern const u8g_pgm_uint8_t u8g_font_7x14Br[];
extern const u8g_pgm_uint8_t u8g_font_7x14[];
extern const u8g_pgm_uint8_t u8g_font_7x14r[];
extern const u8g_pgm_uint8_t u8g_font_8x13_67_75[];
extern const u8g_pgm_uint8_t u8g_font_8x13B[];
extern const u8g_pgm_uint8_t u8g_font_8x13Br[];
extern const u8g_pgm_uint8_t u8g_font_8x13[];
extern const u8g_pgm_uint8_t u8g_font_8x13r[];
extern const u8g_pgm_uint8_t u8g_font_8x13O[];
extern const u8g_pgm_uint8_t u8g_font_8x13Or[];

extern const u8g_pgm_uint8_t u8g_font_9x15_67_75[];
extern const u8g_pgm_uint8_t u8g_font_9x15_78_79[];
extern const u8g_pgm_uint8_t u8g_font_9x15B[];
extern const u8g_pgm_uint8_t u8g_font_9x15Br[];
extern const u8g_pgm_uint8_t u8g_font_9x15[];
extern const u8g_pgm_uint8_t u8g_font_9x15r[];

extern const u8g_pgm_uint8_t u8g_font_9x18_67_75[];
extern const u8g_pgm_uint8_t u8g_font_9x18_78_79[];
extern const u8g_pgm_uint8_t u8g_font_9x18B[];
extern const u8g_pgm_uint8_t u8g_font_9x18[];
extern const u8g_pgm_uint8_t u8g_font_9x18Br[];
extern const u8g_pgm_uint8_t u8g_font_9x18r[];

extern const u8g_pgm_uint8_t u8g_font_cursor[];
extern const u8g_pgm_uint8_t u8g_font_cursorr[];
extern const u8g_pgm_uint8_t u8g_font_micro[];

extern const u8g_pgm_uint8_t u8g_font_cu12_67_75[];
extern const u8g_pgm_uint8_t u8g_font_cu12_78_79[];
extern const u8g_pgm_uint8_t u8g_font_cu12[];

/* 
  Free-Universal Bold 
  r: Reduced char set (codes 32 - 128)
  n: Numbers (codes 42 - 57)
  no char: Full set (codes 32 - 255)
*/

extern const u8g_pgm_uint8_t u8g_font_fub11[];
extern const u8g_pgm_uint8_t u8g_font_fub11r[];
extern const u8g_pgm_uint8_t u8g_font_fub11n[];
extern const u8g_pgm_uint8_t u8g_font_fub14[];
extern const u8g_pgm_uint8_t u8g_font_fub14r[];
extern const u8g_pgm_uint8_t u8g_font_fub14n[];
extern const u8g_pgm_uint8_t u8g_font_fub17[];
extern const u8g_pgm_uint8_t u8g_font_fub17r[];
extern const u8g_pgm_uint8_t u8g_font_fub17n[];
extern const u8g_pgm_uint8_t u8g_font_fub20[];
extern const u8g_pgm_uint8_t u8g_font_fub20r[];
extern const u8g_pgm_uint8_t u8g_font_fub20n[];
extern const u8g_pgm_uint8_t u8g_font_fub25[];
extern const u8g_pgm_uint8_t u8g_font_fub25r[];
extern const u8g_pgm_uint8_t u8g_font_fub25n[];
extern const u8g_pgm_uint8_t u8g_font_fub30[];
extern const u8g_pgm_uint8_t u8g_font_fub30r[];
extern const u8g_pgm_uint8_t u8g_font_fub30n[];
extern const u8g_pgm_uint8_t u8g_font_fub35n[];
extern const u8g_pgm_uint8_t u8g_font_fub42n[];
extern const u8g_pgm_uint8_t u8g_font_fub49n[];

/* 
  Free-Universal Regular
  r: Reduced char set (codes 32 - 128)
  n: Numbers (codes 42 - 57)
  no char: Full set (codes 32 - 255)
*/

extern const u8g_pgm_uint8_t u8g_font_fur11[];
extern const u8g_pgm_uint8_t u8g_font_fur11r[];
extern const u8g_pgm_uint8_t u8g_font_fur11n[];
extern const u8g_pgm_uint8_t u8g_font_fur14[];
extern const u8g_pgm_uint8_t u8g_font_fur14r[];
extern const u8g_pgm_uint8_t u8g_font_fur14n[];
extern const u8g_pgm_uint8_t u8g_font_fur17[];
extern const u8g_pgm_uint8_t u8g_font_fur17r[];
extern const u8g_pgm_uint8_t u8g_font_fur17n[];
extern const u8g_pgm_uint8_t u8g_font_fur20[];
extern const u8g_pgm_uint8_t u8g_font_fur20r[];
extern const u8g_pgm_uint8_t u8g_font_fur20n[];
extern const u8g_pgm_uint8_t u8g_font_fur25[];
extern const u8g_pgm_uint8_t u8g_font_fur25r[];
extern const u8g_pgm_uint8_t u8g_font_fur25n[];
extern const u8g_pgm_uint8_t u8g_font_fur30[];
extern const u8g_pgm_uint8_t u8g_font_fur30r[];
extern const u8g_pgm_uint8_t u8g_font_fur30n[];
extern const u8g_pgm_uint8_t u8g_font_fur35n[];
extern const u8g_pgm_uint8_t u8g_font_fur42n[];
extern const u8g_pgm_uint8_t u8g_font_fur49n[];

/* 
  Gentium Bold
  r: Reduced char set (codes 32 - 128)
  n: Numbers (codes 42 - 57)
  no char: Full set (codes 32 - 255)
*/

extern const u8g_pgm_uint8_t u8g_font_gdb11[];
extern const u8g_pgm_uint8_t u8g_font_gdb12[];
extern const u8g_pgm_uint8_t u8g_font_gdb14[];
extern const u8g_pgm_uint8_t u8g_font_gdb17[];
extern const u8g_pgm_uint8_t u8g_font_gdb20[];
extern const u8g_pgm_uint8_t u8g_font_gdb25[];
extern const u8g_pgm_uint8_t u8g_font_gdb30[];

extern const u8g_pgm_uint8_t u8g_font_gdb11r[];
extern const u8g_pgm_uint8_t u8g_font_gdb12r[];
extern const u8g_pgm_uint8_t u8g_font_gdb14r[];
extern const u8g_pgm_uint8_t u8g_font_gdb17r[];
extern const u8g_pgm_uint8_t u8g_font_gdb20r[];
extern const u8g_pgm_uint8_t u8g_font_gdb25r[];
extern const u8g_pgm_uint8_t u8g_font_gdb30r[];

extern const u8g_pgm_uint8_t u8g_font_gdb11n[];
extern const u8g_pgm_uint8_t u8g_font_gdb12n[];
extern const u8g_pgm_uint8_t u8g_font_gdb14n[];
extern const u8g_pgm_uint8_t u8g_font_gdb17n[];
extern const u8g_pgm_uint8_t u8g_font_gdb20n[];
extern const u8g_pgm_uint8_t u8g_font_gdb25n[];
extern const u8g_pgm_uint8_t u8g_font_gdb30n[];

/* 
  Gentium Regular
  r: Reduced char set (codes 32 - 128)
  n: Numbers (codes 42 - 57)
  no char: Full set (codes 32 - 255)
*/

extern const u8g_pgm_uint8_t u8g_font_gdr9[];
extern const u8g_pgm_uint8_t u8g_font_gdr10[];
extern const u8g_pgm_uint8_t u8g_font_gdr11[];
extern const u8g_pgm_uint8_t u8g_font_gdr12[];
extern const u8g_pgm_uint8_t u8g_font_gdr14[];
extern const u8g_pgm_uint8_t u8g_font_gdr17[];
extern const u8g_pgm_uint8_t u8g_font_gdr20[];
extern const u8g_pgm_uint8_t u8g_font_gdr25[];
extern const u8g_pgm_uint8_t u8g_font_gdr30[];

extern const u8g_pgm_uint8_t u8g_font_gdr9r[];
extern const u8g_pgm_uint8_t u8g_font_gdr10r[];
extern const u8g_pgm_uint8_t u8g_font_gdr11r[];
extern const u8g_pgm_uint8_t u8g_font_gdr12r[];
extern const u8g_pgm_uint8_t u8g_font_gdr14r[];
extern const u8g_pgm_uint8_t u8g_font_gdr17r[];
extern const u8g_pgm_uint8_t u8g_font_gdr20r[];
extern const u8g_pgm_uint8_t u8g_font_gdr25r[];
extern const u8g_pgm_uint8_t u8g_font_gdr30r[];

extern const u8g_pgm_uint8_t u8g_font_gdr9n[];
extern const u8g_pgm_uint8_t u8g_font_gdr10n[];
extern const u8g_pgm_uint8_t u8g_font_gdr11n[];
extern const u8g_pgm_uint8_t u8g_font_gdr12n[];
extern const u8g_pgm_uint8_t u8g_font_gdr14n[];
extern const u8g_pgm_uint8_t u8g_font_gdr17n[];
extern const u8g_pgm_uint8_t u8g_font_gdr20n[];
extern const u8g_pgm_uint8_t u8g_font_gdr25n[];
extern const u8g_pgm_uint8_t u8g_font_gdr30n[];

/* 
  Old-Standard Bold
  r: Reduced char set (codes 32 - 128)
  n: Numbers (codes 42 - 57)
  no char: Full set (codes 32 - 255)
*/

extern const u8g_pgm_uint8_t u8g_font_osb18[];
extern const u8g_pgm_uint8_t u8g_font_osb21[];
extern const u8g_pgm_uint8_t u8g_font_osb26[];
extern const u8g_pgm_uint8_t u8g_font_osb29[];
extern const u8g_pgm_uint8_t u8g_font_osb35[];

extern const u8g_pgm_uint8_t u8g_font_osb18r[];
extern const u8g_pgm_uint8_t u8g_font_osb21r[];
extern const u8g_pgm_uint8_t u8g_font_osb26r[];
extern const u8g_pgm_uint8_t u8g_font_osb29r[];
extern const u8g_pgm_uint8_t u8g_font_osb35r[];

extern const u8g_pgm_uint8_t u8g_font_osb18n[];
extern const u8g_pgm_uint8_t u8g_font_osb21n[];
extern const u8g_pgm_uint8_t u8g_font_osb26n[];
extern const u8g_pgm_uint8_t u8g_font_osb29n[];
extern const u8g_pgm_uint8_t u8g_font_osb35n[];

/* 
  Old-Standard Regular
  r: Reduced char set (codes 32 - 128)
  n: Numbers (codes 42 - 57)
  no char: Full set (codes 32 - 255)
*/

extern const u8g_pgm_uint8_t u8g_font_osr18[];
extern const u8g_pgm_uint8_t u8g_font_osr21[];
extern const u8g_pgm_uint8_t u8g_font_osr26[];
extern const u8g_pgm_uint8_t u8g_font_osr29[];
extern const u8g_pgm_uint8_t u8g_font_osr35[];

extern const u8g_pgm_uint8_t u8g_font_osr18r[];
extern const u8g_pgm_uint8_t u8g_font_osr21r[];
extern const u8g_pgm_uint8_t u8g_font_osr26r[];
extern const u8g_pgm_uint8_t u8g_font_osr29r[];
extern const u8g_pgm_uint8_t u8g_font_osr35r[];

extern const u8g_pgm_uint8_t u8g_font_osr18n[];
extern const u8g_pgm_uint8_t u8g_font_osr21n[];
extern const u8g_pgm_uint8_t u8g_font_osr26n[];
extern const u8g_pgm_uint8_t u8g_font_osr29n[];
extern const u8g_pgm_uint8_t u8g_font_osr35n[];

//extern const u8g_pgm_uint8_t u8g_font_osr41[];

/* GNU unifont */

extern const u8g_pgm_uint8_t u8g_font_unifont_18_19[];
extern const u8g_pgm_uint8_t u8g_font_unifont_72_73[];
extern const u8g_pgm_uint8_t u8g_font_unifont_67_75[];
extern const u8g_pgm_uint8_t u8g_font_unifont_76[];
extern const u8g_pgm_uint8_t u8g_font_unifont_77[];
extern const u8g_pgm_uint8_t u8g_font_unifont_78_79[];
extern const u8g_pgm_uint8_t u8g_font_unifont_86[];
extern const u8g_pgm_uint8_t u8g_font_unifont[];
extern const u8g_pgm_uint8_t u8g_font_unifontr[];

/* 04b fonts */

extern const u8g_pgm_uint8_t u8g_font_04b_03b[]; 
extern const u8g_pgm_uint8_t u8g_font_04b_03bn[];
extern const u8g_pgm_uint8_t u8g_font_04b_03br[];
extern const u8g_pgm_uint8_t u8g_font_04b_03[];
extern const u8g_pgm_uint8_t u8g_font_04b_03n[];
extern const u8g_pgm_uint8_t u8g_font_04b_03r[];
extern const u8g_pgm_uint8_t u8g_font_04b_24[];
extern const u8g_pgm_uint8_t u8g_font_04b_24n[];
extern const u8g_pgm_uint8_t u8g_font_04b_24r[];

/* orgdot fonts */

extern const u8g_pgm_uint8_t u8g_font_orgv01[];
extern const u8g_pgm_uint8_t u8g_font_orgv01r[];
extern const u8g_pgm_uint8_t u8g_font_orgv01n[];

extern const u8g_pgm_uint8_t u8g_font_fixed_v0[];
extern const u8g_pgm_uint8_t u8g_font_fixed_v0r[];
extern const u8g_pgm_uint8_t u8g_font_fixed_v0n[];

extern const u8g_pgm_uint8_t u8g_font_tpssb[];
extern const u8g_pgm_uint8_t u8g_font_tpssbr[];
extern const u8g_pgm_uint8_t u8g_font_tpssbn[];

extern const u8g_pgm_uint8_t u8g_font_tpss[];
extern const u8g_pgm_uint8_t u8g_font_tpssr[];
extern const u8g_pgm_uint8_t u8g_font_tpssn[];

#ifdef __cplusplus
}
#endif

#endif /* _U8G_H */

