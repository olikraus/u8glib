/*

  u8g_dev_ssd1322_nhd31oled_bw.c
  
  1-Bit (BW) Driver for SSD1322 Controller (OLED Display)
  Tested with NHD-3.12-25664

  Universal 8bit Graphics Library
  
  Copyright (c) 2012, olikraus@gmail.com
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
  
  SSD130x       Monochrom OLED Controller
  SSD131x       Character OLED Controller
  SSD132x       Graylevel OLED Controller
  SSD1331       Color OLED Controller       

*/

#include "u8g.h"

#define WIDTH 255
#define HEIGHT 64
#define PAGE_HEIGHT 8

/* 
  http://www.newhavendisplay.com/app_notes/OLED_25664.txt 
  http://www.newhavendisplay.com/forum/viewtopic.php?f=15&t=3758
*/

static const uint8_t u8g_dev_ssd1322_1bit_nhd_312_init_seq[] PROGMEM = {
  U8G_ESC_DLY(10),              /* delay 10 ms */
  U8G_ESC_CS(0),                 /* disable chip */
  U8G_ESC_ADR(0),               /* instruction mode */
  U8G_ESC_RST(1),               /* do reset low pulse with (1*16)+2 milliseconds */
  U8G_ESC_CS(1),                /* enable chip */
  
  U8G_ESC_DLY(100),             /* delay 100 ms */
  U8G_ESC_DLY(100),             /* delay 100 ms */
  
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0fd,					/* lock command */
  U8G_ESC_ADR(1),               	/* data mode */
  0x012,					/* unlock */
  
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0ae,                               	 /* display off, sleep mode */
  
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0b3, 
  U8G_ESC_ADR(1),               	/* data mode */
  0x091,                    /* set display clock divide ratio/oscillator frequency (set clock as 80 frames/sec) */
  
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0ca, 					/* multiplex ratio */
  U8G_ESC_ADR(1),               	/* data mode */
  0x03f,                    		/* 1/64 Duty (0x0F~0x3F) */
  
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0a2, 
  U8G_ESC_ADR(1),               	/* data mode */
  0x000,                     		/* display offset, shift mapping ram counter */

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0a1, 
  U8G_ESC_ADR(1),               	/* data mode */
  0x000,                     		/* display start line */

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0a0, 					/* Set Re-Map / Dual COM Line Mode */
  U8G_ESC_ADR(1),               	/* data mode */
  0x014,                     		
  0x011,                     		

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0ab, 
  U8G_ESC_ADR(1),               	/* data mode */
  0x001,                     		/* Enable Internal VDD Regulator */

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0b4, 					/* Display Enhancement A */
  U8G_ESC_ADR(1),               	/* data mode */
  0x0a0,                     		
  0x005|0x0fd,                     		
  
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0c1,					/* contrast */ 
  U8G_ESC_ADR(1),               	/* data mode */
  0x09f,                     		
  
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0c7,					/* Set Scale Factor of Segment Output Current Control */ 
  U8G_ESC_ADR(1),               	/* data mode */
  0x00f,                     		

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0b9,                               	 /* linear gray scale */

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0b1,					/* Phase 1 (Reset) & Phase 2 (Pre-Charge) Period Adjustment */ 
  U8G_ESC_ADR(1),               	/* data mode */
  0x0e2,                     		

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0d1, 					/* Display Enhancement B */
  U8G_ESC_ADR(1),               	/* data mode */
  0x082|0x020,                     		
  0x020,                     		

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0bb,					/* precharge  voltage */ 
  U8G_ESC_ADR(1),               	/* data mode */
  0x01f,                     		
  
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0b6,					/* precharge period */ 
  U8G_ESC_ADR(1),               	/* data mode */
  0x008,                     		

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0be,					/* vcomh */ 
  U8G_ESC_ADR(1),               	/* data mode */
  0x007,                     		

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0a6,                               	 /* normal display */

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0a9,                               	 /* exit partial display */

  U8G_ESC_ADR(0),               	/* instruction mode */
  0x0af,                               	 /* display on */

  // test sequence *_*_*_******__**_____
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x015,       /* column address... */
  U8G_ESC_ADR(1),               /* data mode */
  0x01c,       /* start at column 0 */
  0x05b,       /* end at column 127 (which is y == 255), because there are two pixel in one column */
  U8G_ESC_ADR(0),               /* instruction mode */
  0x075,       /* row address... */
  U8G_ESC_ADR(1),               /* data mode */
  0x00,
  0x7f,
  U8G_ESC_ADR(0),               /* instruction mode */
  0x05c,       /* write mode */
  U8G_ESC_ADR(1),               /* data mode */
  0x0f0,
  0x0f0,
  0x0f0,
  0x0fe,
  0x0fe,
  0x0fe,
  0x000,
  0x0fe,
  0x000,
  0x000,
  0x000,
  0x000,
  0x000,
  0x000,

  // test sequence *_*_*_******__**_____
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x015,       /* column address... */
  U8G_ESC_ADR(1),               /* data mode */
  0x03c,       /* start at column 0 */
  0x05b,       /* end at column 127 (which is y == 255), because there are two pixel in one column */
  U8G_ESC_ADR(0),               /* instruction mode */
  0x075,       /* row address... */
  U8G_ESC_ADR(1),               /* data mode */
  0x00,
  0x7f,
  U8G_ESC_ADR(0),               /* instruction mode */
  0x05c,       /* write mode */
  U8G_ESC_ADR(1),               /* data mode */
  0x0f0,
  0x0f0,
  0x0f0,
  0x0fe,
  0x0fe,
  0x0fe,
  0x000,
  0x0fe,
  0x000,
  0x000,
  0x000,
  0x0fe,
  0x000,
  0x000,
  0x000,

  // test sequence *_*_*_******__**__**___
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x015,       /* column address... */
  U8G_ESC_ADR(1),               /* data mode */
  0x01c,       /* start at column 0 */
  0x05b,       /* end at column 127 (which is y == 255), because there are two pixel in one column */
  U8G_ESC_ADR(0),               /* instruction mode */
  0x075,       /* row address... */
  U8G_ESC_ADR(1),               /* data mode */
  0x10,
  0x7f,
  U8G_ESC_ADR(0),               /* instruction mode */
  0x05c,       /* write mode */
  U8G_ESC_ADR(1),               /* data mode */
  0x0f0,
  0x0f0,
  0x0f0,
  0x0fe,
  0x0fe,
  0x0fe,
  0x000,
  0x0fe,
  0x000,
  0x0fe,
  0x000,
  0x000,

  // test sequence *_*_*_******__**__**__**__
  U8G_ESC_ADR(0),               	/* instruction mode */
  0x015,       /* column address... */
  U8G_ESC_ADR(1),               /* data mode */
  0x01c,       /* start at column 0 */
  0x05b,       /* end at column 127 (which is y == 255), because there are two pixel in one column */
  U8G_ESC_ADR(0),               /* instruction mode */
  0x075,       /* row address... */
  U8G_ESC_ADR(1),               /* data mode */
  0x20,
  0x7f,
  U8G_ESC_ADR(0),               /* instruction mode */
  0x05c,       /* write mode */
  U8G_ESC_ADR(1),               /* data mode */
  0x0f0,
  0x0f0,
  0x0f0,
  0x0fe,
  0x0fe,
  0x0fe,
  0x000,
  0x0fe,
  0x000,
  0x0fe,
  0x000,
  0x0fe,
  0x000,

  U8G_ESC_CS(0),             /* disable chip */
  U8G_ESC_END                /* end of sequence */
};

static const uint8_t u8g_dev_ssd1322_1bit_nhd_312_prepare_page_seq[] PROGMEM = {
  U8G_ESC_ADR(0),               /* instruction mode */
  U8G_ESC_CS(1),                /* enable chip */
  0x015,       /* column address... */
  U8G_ESC_ADR(1),               /* data mode */
  0x01c,       /* start at column 0 */
  0x05b,       /* end at column 127 (which is y == 255), because there are two pixel in one column */
  U8G_ESC_ADR(0),               /* instruction mode */
  0x075,       /* row address... */
  U8G_ESC_ADR(1),               /* data mode */
  U8G_ESC_END                /* end of sequence */
};


static void u8g_dev_ssd1322_1bit_prepare_page(u8g_t *u8g, u8g_dev_t *dev)
{
  uint8_t page = ((u8g_pb_t *)(dev->dev_mem))->p.page;
  
  u8g_WriteEscSeqP(u8g, dev, u8g_dev_ssd1322_1bit_nhd_312_prepare_page_seq);
  
  page <<= 3;
  u8g_WriteByte(u8g, dev, page);       /* start at the selected page */
  page += 7;
  u8g_WriteByte(u8g, dev, page);       /* end within the selected page */  
  
  u8g_SetAddress(u8g, dev, 0);          /* instruction mode mode */
  u8g_WriteByte(u8g, dev, 0x05c);       /* write to ram */  
  u8g_SetAddress(u8g, dev, 1);          /* data mode */
}

static void u8g_dev_ssd1322_1bit_2x_prepare_page(u8g_t *u8g, u8g_dev_t *dev, uint8_t is_odd)
{
  uint8_t page = ((u8g_pb_t *)(dev->dev_mem))->p.page;
  
  u8g_WriteEscSeqP(u8g, dev, u8g_dev_ssd1322_1bit_nhd_312_prepare_page_seq);
  
  page <<= 1;
  page += is_odd;
  
  page <<= 3;
  u8g_WriteByte(u8g, dev, page);       /* start at the selected page */
  page += 7;
  u8g_WriteByte(u8g, dev, page);       /* end within the selected page */  
  
  u8g_SetAddress(u8g, dev, 0);          /* instruction mode mode */
  u8g_WriteByte(u8g, dev, 0x05c);       /* write to ram */  
  u8g_SetAddress(u8g, dev, 1);          /* data mode */
  //u8g_WriteByte(u8g, dev, 0x0ff);       /* write to ram */  
  //u8g_WriteByte(u8g, dev, 0x0ff);       /* write to ram */  
  //u8g_WriteByte(u8g, dev, 0x0ff);       /* write to ram */  
}

/* assumes row autoincrement and activated nibble remap */
#ifdef OLD
static  void _OLD_u8g_dev_ssd1322_1bit_write_16_pixel(u8g_t *u8g, u8g_dev_t *dev, uint8_t left, uint8_t right)
{
  uint8_t d, cnt;
  cnt = 8;
  do
  {
    d = 0;
    if ( left & 1 )
      d |= 0x0f0;
    if ( right & 1 )
      d |= 0x00f;
    u8g_WriteByte(u8g, dev, d);
    left >>= 1;
    right >>= 1;
    cnt--;
  }while ( cnt > 0 );
}
#endif

static  void u8g_dev_ssd1322_1bit_write_16_pixel(u8g_t *u8g, u8g_dev_t *dev, uint8_t left, uint8_t right, uint8_t x)
{
  uint8_t d, cnt;
  static uint8_t buf[8];
  cnt = 8;
  do
  {
    d = 0;
    if ( left & 128 )
      d |= 0x0f0;
    if ( right & 128 )
      d |= 0x00f;
    cnt--;
    buf[cnt] = d;
    left <<= 1;
    right <<= 1;
  }while ( cnt > 0 );
  u8g_WriteSequence(u8g, dev, 8, buf);
}

static void u8g_dev_ssd1322_1bit_write_buffer(u8g_t *u8g, u8g_dev_t *dev, uint8_t is_odd)
{
  uint8_t cnt, left, right;
  uint8_t *ptr;
  u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
  
  ptr = pb->buf;
  cnt = pb->width;
  if ( is_odd )
    ptr += cnt;
  cnt >>= 1;
  do
  {
    left = *ptr++;
    right = *ptr++;
    //u8g_dev_ssd1322_1bit_write_16_pixel(u8g, dev, left, right, is_odd ? 0: 255);
    if ( is_odd )
      u8g_dev_ssd1322_1bit_write_16_pixel(u8g, dev, 1, 0, is_odd ? 0: 255);
    else
      u8g_dev_ssd1322_1bit_write_16_pixel(u8g, dev, 0, 0, is_odd ? 0: 255);
      
    cnt--;
  } while( cnt > 0 );
}

uint8_t u8g_dev_ssd1322_nhd31oled_bw_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_InitCom(u8g, dev);
      u8g_WriteEscSeqP(u8g, dev, u8g_dev_ssd1322_1bit_nhd_312_init_seq);
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_dev_ssd1322_1bit_prepare_page(u8g, dev);
        u8g_dev_ssd1322_1bit_write_buffer(u8g, dev, 0);
        u8g_SetChipSelect(u8g, dev, 0);        
      }
      break;
    case U8G_DEV_MSG_CONTRAST:
      u8g_SetChipSelect(u8g, dev, 1);
      u8g_SetAddress(u8g, dev, 0);          /* instruction mode */
      u8g_WriteByte(u8g, dev, 0x081);
      u8g_WriteByte(u8g, dev, (*(uint8_t *)arg) >> 1);
      u8g_SetChipSelect(u8g, dev, 0);      
      break;
  }
  return u8g_dev_pb8v1_base_fn(u8g, dev, msg, arg);
}

uint8_t u8g_dev_ssd1322_nhd31oled_2x_bw_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_InitCom(u8g, dev);
      u8g_WriteEscSeqP(u8g, dev, u8g_dev_ssd1322_1bit_nhd_312_init_seq);
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_dev_ssd1322_1bit_2x_prepare_page(u8g, dev, 0);
        u8g_dev_ssd1322_1bit_write_buffer(u8g, dev, 0);
        u8g_dev_ssd1322_1bit_2x_prepare_page(u8g, dev, 1);
        u8g_dev_ssd1322_1bit_write_buffer(u8g, dev, 1);
        u8g_SetChipSelect(u8g, dev, 0);        
      }
      break;
    case U8G_DEV_MSG_CONTRAST:
      u8g_SetChipSelect(u8g, dev, 1);
      u8g_SetAddress(u8g, dev, 0);          /* instruction mode */
      u8g_WriteByte(u8g, dev, 0x081);
      u8g_WriteByte(u8g, dev, (*(uint8_t *)arg) >> 1);
      u8g_SetChipSelect(u8g, dev, 0);      
      break;
  }
  return u8g_dev_pb16v1_base_fn(u8g, dev, msg, arg);
}


U8G_PB_DEV(u8g_dev_ssd1322_nhd31oled_bw_sw_spi , WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_ssd1322_nhd31oled_bw_fn, U8G_COM_SW_SPI);
U8G_PB_DEV(u8g_dev_ssd1322_nhd31oled_bw_hw_spi , WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_ssd1322_nhd31oled_bw_fn, U8G_COM_HW_SPI);

#define DWIDTH (WIDTH*2)
uint8_t u8g_dev_ssd1322_nhd31oled_2x_bw_buf[DWIDTH] U8G_NOCOMMON ; 
u8g_pb_t u8g_dev_ssd1322_nhd31oled_2x_bw_pb = { {16, HEIGHT, 0, 0, 0},  WIDTH, u8g_dev_ssd1322_nhd31oled_2x_bw_buf}; 
u8g_dev_t u8g_dev_ssd1322_nhd31oled_2x_bw_sw_spi = { u8g_dev_ssd1322_nhd31oled_2x_bw_fn, &u8g_dev_ssd1322_nhd31oled_2x_bw_pb, U8G_COM_SW_SPI };
u8g_dev_t u8g_dev_ssd1322_nhd31oled_2x_bw_hw_spi = { u8g_dev_ssd1322_nhd31oled_2x_bw_fn, &u8g_dev_ssd1322_nhd31oled_2x_bw_pb, U8G_COM_HW_SPI };

