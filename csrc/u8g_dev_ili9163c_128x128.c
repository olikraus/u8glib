/*

  u8g_dev_ili9163c_128x128.c

  Universal 8bit Graphics Library

  Copyright (c) 2011, olikraus@gmail.com
  Copyright (c) 2015, jens@4k2.de
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

  Color format
    Red: 5 Bit
    Green: 6 Bit
    Blue: 5 Bit


*/

#include "u8g.h"

#define WIDTH 128
#define HEIGHT 128
#define OFFSET 32

#define PAGE_HEIGHT 8


/*
  datasheet
    http://www.orientdisplay.com/pdf/ILI9163C.pdf
    https://github.com/sumotoy/TFT_ILI9163C/blob/master/_utility/ILI9163C.pdf
  other libs
    https://github.com/sumotoy/TFT_ILI9163C
  based on u8g_dev_ili9325d_320x240.c
*/

#define CMD(cmd) U8G_ESC_ADR(0), cmd, U8G_ESC_ADR(1)

static const uint8_t u8g_dev_ili9163c_128x128_init_seq[] PROGMEM = {
  U8G_ESC_CS(1),             /* enable chip */
  CMD(0x01 /* SOFTWARE_RESET */),
  U8G_ESC_DLY(100),       /* delay 100 ms */
  U8G_ESC_DLY(100),       /* delay 100 ms */
  U8G_ESC_DLY(100),       /* delay 100 ms */
  U8G_ESC_DLY(100),       /* delay 100 ms */
  U8G_ESC_DLY(100),       /* delay 100 ms */
  CMD(0x11 /* SLEEP_OUT */),
  U8G_ESC_DLY(5),         /* delay 5 ms */

  CMD(0x0C /* PIXEL_FMT */), 0x05, // 16bit Color format
  CMD(0x26 /* GAMMA_SET */), 0x02, // Gamma Curve 2 (0x01, 0x02, 0x04 or 0x08)
  CMD(0x13 /* NORMAL_DISPLAY_MODE_ON */),
  CMD(0xB6 /* DISPLAY_FUNCTION_SET */), 0xff, 0x06,
  CMD(0xB1 /* FRAME_RATE_CTRL1 */), 0x08, 0x02,
  CMD(0xB4 /* DISPLAY_INVERSION */), 0x07,
  CMD(0xC0 /* POWER_CTRL1 */), 0x0A, 0x02,
  CMD(0xC1 /* POWER_CTRL2 */), 0x02,
  CMD(0xC5 /* VCOM_CTRL1 */), 0x50, 0x63,
  CMD(0xC7 /* VCOM_OFFSET */), 0,
  CMD(0x29 /* DISPLAY_ON */),
  CMD(0x36 /* MEMORY_ACCESS_CTRL */), 0x08, //MY=0,MX=0,MV=0,ML=0 (No rotation),RGB=1 (BGR space),MH=0
#if 0
  CMD(0x2A /* COLUMN_ADDR */), 0, 0, 0, WIDTH - 1,
  CMD(0x2B /* PAGE_ADDR */), 0, 0, 0, (HEIGHT + OFFSET) - 1,
  CMD(0x2C /* MEM_WRITE */),
#endif
  U8G_ESC_CS(0),             /* disable chip */
  U8G_ESC_END                /* end of sequence */
};


static const uint8_t u8g_dev_ili9163c_128x128_page_seq[] PROGMEM = {
  U8G_ESC_CS(1),             /* enable chip */
  CMD(0x2A /* COLUMN_ADDR */), 0, 0, 0, WIDTH - 1,
  CMD(0x2B /* PAGE_ADDR */), 0,
  U8G_ESC_END                /* end of sequence */
};


/* convert the internal RGB 332 to 65K high byte */
static uint8_t u8g_dev_ili9163c_get_65K_high_byte(uint8_t color)
{
  uint8_t h;
  h = color;
  h &= 0x0e0;
  h |= h>>3;
  h &= 0x0f8;
  color>>=2;
  color &= 7;
  h |= color;
  return h;
}

/* convert the internal RGB 332 to 65K high byte */
static uint8_t u8g_dev_ili9163c_get_65K_low_byte(uint8_t color)
{
  uint8_t l;
  l = color;
  l <<= 3;
  color &= 3;
  color <<= 1;
  l |= color;
  return l;
}


uint8_t u8g_dev_ili9163c_128x128_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{

  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_InitCom(u8g, dev, U8G_SPI_CLK_CYCLE_50NS);
      //for(;;)
	u8g_WriteEscSeqP(u8g, dev, u8g_dev_ili9163c_128x128_init_seq);

      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
	uint8_t i;
	uint16_t y, j;
	uint8_t *ptr;
	u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);

	y = pb->p.page_y0;

	u8g_WriteEscSeqP(u8g, dev, u8g_dev_ili9163c_128x128_page_seq);
	u8g_WriteByte(u8g, dev, (y + OFFSET) & 0xff);
	u8g_WriteByte(u8g, dev, 0);
	u8g_WriteByte(u8g, dev, (HEIGHT + OFFSET) - 1);

	u8g_SetAddress(u8g, dev, 0);           /* cmd mode */
	u8g_WriteByte(u8g, dev, 0x2C /* MEM_WRITE*/);
	u8g_SetAddress(u8g, dev, 1);           /* data mode */

	ptr = pb->buf;
	for( i = 0; i < pb->p.page_height; i ++ )
	{
	  for( j = 0; j < pb->width; j++ )
	  {
	    u8g_WriteByte(u8g, dev, u8g_dev_ili9163c_get_65K_high_byte(*ptr) );
	    u8g_WriteByte(u8g, dev, u8g_dev_ili9163c_get_65K_low_byte(*ptr) );

	    ptr++;
	  }
	}
	u8g_SetChipSelect(u8g, dev, 0);
      }
      break;
  }
  return u8g_dev_pb8h8_base_fn(u8g, dev, msg, arg);
}


/* Can not use U8G_PB_DEV()! It calculates u8g_dev*_buf only with WIDTH instead of (WIDTH*PAGE_HEIGHT)! */
uint8_t u8g_dev_ili9163c_128x128_buf[WIDTH * PAGE_HEIGHT] U8G_NOCOMMON ;
u8g_pb_t u8g_dev_ili9163c_128x128_pb = { {PAGE_HEIGHT, HEIGHT, 0, 0, 0},  WIDTH, u8g_dev_ili9163c_128x128_buf};
u8g_dev_t u8g_dev_ili9163c_128x128_sw_spi = { &u8g_dev_ili9163c_128x128_fn, &u8g_dev_ili9163c_128x128_pb, U8G_COM_SW_SPI};
u8g_dev_t u8g_dev_ili9163c_128x128_hw_spi = { &u8g_dev_ili9163c_128x128_fn, &u8g_dev_ili9163c_128x128_pb, U8G_COM_HW_SPI};
