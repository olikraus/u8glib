/*

  u8g_dev_ssd1306_128x32.c

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

#include "u8g.h"

#define WIDTH 128
#define HEIGHT 32
#define PAGE_HEIGHT 8

/* init sequence adafruit 128x32 OLED (NOT TESTED), */
static const uint8_t u8g_dev_ssd1306_128x32_init_seq[] PROGMEM = {
  U8G_ESC_CS(0),             /* disable chip */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_RST(1),           /* do reset low pulse with (1*16)+2 milliseconds */
  U8G_ESC_CS(1),             /* enable chip */

  0x0ae,				/* display off, sleep mode */
  0x0d5, 0x080,		/* clock divide ratio (0x00=1) and oscillator frequency (0x8) */
  0x0a8, 0x01f,		/* Feb 23, 2013: 128x32 OLED: 0x01f,  128x64 OLED 0x03f */

  0x0d3, 0x000,		/*  */

  0x040,				/* start line */
  
  0x08d, 0x014,		/* [2] charge pump setting (p62): 0x014 enable, 0x010 disable */

  0x020, 0x002,		/* 2012-05-27: page addressing mode */
  0x0a1,				/* segment remap a0/a1*/
  0x0c8,				/* c0: scan dir normal, c8: reverse */
  0x0da, 0x002,		/* com pin HW config, sequential com pin config (bit 4), disable left/right remap (bit 5), Feb 23, 2013: 128x32 OLED: 0x002,  128x64 OLED 0x012 */
  0x081, 0x0cf,		/* [2] set contrast control */
  0x0d9, 0x0f1,		/* [2] pre-charge period 0x022/f1*/
  0x0db, 0x040,		/* vcomh deselect level */
  
  0x02e,				/* 2012-05-27: Deactivate scroll */ 
  0x0a4,				/* output ram to display */
  0x0a6,				/* none inverted normal display mode */
  0x0af,				/* display on */

  U8G_ESC_CS(0),             /* disable chip */
  U8G_ESC_END                /* end of sequence */
};


#ifdef OBSOLETE
static const uint8_t u8g_dev_ssd1306_128x32_data_start[] PROGMEM = {
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_CS(1),             /* enable chip */
  0x010, 		/* set upper 4 bit of the col adr to 0, page addressing mode */
  0x000, 		/* set lower 4 bit of the col adr to 4, page addressing mode  */
  U8G_ESC_END                /* end of sequence */
};
#endif

uint8_t u8g_dev_ssd1306_128x32_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_InitCom(u8g, dev);
      u8g_WriteEscSeqP(u8g, dev, u8g_dev_ssd1306_128x32_init_seq);
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        uint8_t i;
        uint16_t disp_ram_adr;
        uint8_t *ptr;
	
        disp_ram_adr = WIDTH/8;
        disp_ram_adr *= pb->p.page_y0*2;		/* *2 to skip every 2nd line */
        ptr = pb->buf;
	u8g_SetChipSelect(u8g, dev, 1);
        for( i = 0; i < PAGE_HEIGHT; i ++ )
        {
	  u8g_SetAddress(u8g, dev, 0);           /* command mode */
	  
	  u8g_WriteByte(u8g, dev, 0x021);		/* column range for horizontal addressing mode */ 
	  u8g_WriteByte(u8g, dev, disp_ram_adr & 0x07f);		/* start column for horizontal addressing mode */ 
	  u8g_WriteByte(u8g, dev, 0x07f);		/* end column for horizontal addressing mode */ 
	  
	  u8g_WriteByte(u8g, dev, 0x022);		/* page range for horizontal addressing mode */ 
	  u8g_WriteByte(u8g, dev, disp_ram_adr >> 7);		/* start page for horizontal addressing mode */ 
	  u8g_WriteByte(u8g, dev, disp_ram_adr >> 7);		/* end page for horizontal addressing mode */ 
	  
	  u8g_SetAddress(u8g, dev, 1);           /* data mode */
          u8g_WriteSequence(u8g, dev, WIDTH/8, ptr);	
	  
	  u8g_SetChipSelect(u8g, dev, 0);
  	  
          ptr += WIDTH/8;
          disp_ram_adr += WIDTH/8 * 2;		/* *2 to skip every 2nd line */	  
	}
	u8g_SetChipSelect(u8g, dev, 0);

	
        u8g_WriteByte(u8g, dev, pb->p.page);   /* select start page (SSD1306, horizontal addressing mode) */
        u8g_WriteByte(u8g, dev, pb->p.page);   /* select end page (SSD1306, horizontal addressing mode) */
        /*u8g_WriteByte(u8g, dev, 0x0b0 | pb->p.page); *//* select current page (SSD1306, page addressing mode) */
        u8g_SetAddress(u8g, dev, 1);           /* data mode */
        if ( u8g_pb_WriteBuffer(pb, u8g, dev) == 0 )
          return 0;
        u8g_SetChipSelect(u8g, dev, 0);
      }
      break;
  }
  return u8g_dev_pb8h1_base_fn(u8g, dev, msg, arg);		/* Feb 23, 2013: changed to horizontal mode */
}

U8G_PB_DEV(u8g_dev_ssd1306_128x32_sw_spi, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_ssd1306_128x32_fn, U8G_COM_SW_SPI);
U8G_PB_DEV(u8g_dev_ssd1306_128x32_hw_spi, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_ssd1306_128x32_fn, U8G_COM_HW_SPI);
U8G_PB_DEV(u8g_dev_ssd1306_128x32_i2c, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_ssd1306_128x32_fn, U8G_COM_SSD_I2C);


