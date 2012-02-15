/*

  u8g_dev_st7687_c144mvgd.c (1.44" TFT)

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
  
  
*/

#include "u8g.h"

#define WIDTH 128
#define HEIGHT 64
#define PAGE_HEIGHT 8

/* init sequence from https://github.com/adafruit/ST7565-LCD/blob/master/ST7565/ST7565.cpp */
u8g_pgm_uint8_t u8g_dev_st7687_c144mvgd_init_seq[] = {
  U8G_ESC_CS(0),             /* disable chip */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_CS(1),             /* enable chip */
  U8G_ESC_RST(15),           /* do reset low pulse with (15*16)+2 milliseconds (=maximum delay)*/
  
  0x001,                        /* A0=0, SW reset */
  U8G_ESC_DLY(200),         /* delay 200 ms */
  
  0x0d7,                        /* EEPROM data auto re-load control */
  U8G_ESC_ADR(1),           /* data mode */
  0x09f,                             /* ARD = 1 */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_DLY(100),         /* delay 100 ms */
  
  0x0e0,                        /* EEPROM control in */
  U8G_ESC_ADR(1),           /* data mode */
  0x000,                             /*  */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_DLY(100),         /* delay 100 ms */
  
#ifdef NOT_REQUIRED  
  0x0fa,                        /* EEPROM function selection 8.1.66 */
  U8G_ESC_ADR(1),           /* data mode */
  0x000,                             /*  */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_DLY(100),         /* delay 100 ms */
#endif 

  0x0e3,                        /* Read from EEPROM, 8.1.55 */
  U8G_ESC_DLY(100),         /* delay 100 ms */

  0x0e1,                        /* EEPROM control out, 8.1.53 */
  U8G_ESC_DLY(100),         /* delay 100 ms */
  
  //0x028,                        /* display off */
  0x011,                                /* Sleep out & booster on */
  U8G_ESC_DLY(100),         /* delay 100 ms */
  
  0x0c0,                        /* Vop setting, 8.1.42 */
  U8G_ESC_ADR(1),           /* data mode */
  0x000,                             /*  */
  0x001,                             /*  3.6 + 256*0.04 = 13.84 Volt */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_DLY(100),         /* delay 100 ms */
}


uint8_t u8g_st7687_c144mvgd_8h8_buf[WIDTH*8] U8G_NOCOMMON ; 
u8g_pb_t u8g_st7687_c144mvgd_8h8_pb = { {8, HEIGHT, 0, 0, 0},  WIDTH, u8g_st7687_c144mvgd_8h8_buf}; 
u8g_dev_t u8g_dev_st7687_c144mvgd_sw_spi = { u8g_dev_sdl_8bit_fn, &u8g_st7687_c144mvgd_8h8_pb, u8g_com_arduino_sw_spi_fn };
