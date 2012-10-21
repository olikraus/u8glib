/*

  main.c 
  
  U8g Logo for ATMEGA Controller

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

#if defined(__AVR__)
#include <avr/interrupt.h>
#include <avr/io.h>
#endif


/* 
  Software SPI:
  uint8_t u8g_InitSPI(u8g_t *u8g, u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset); 

  Hardware SPI:
  uint8_t u8g_InitHWSPI(u8g_t *u8g, u8g_dev_t *dev, uint8_t cs, uint8_t a0, uint8_t reset);

  Parallel Interface:
  uint8_t u8g_Init8Bit(u8g_t *u8g, u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, 
    uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw, uint8_t reset);

  Visit 
    http://code.google.com/p/u8glib/wiki/device 
  for a list of valid devices (second argument of the constructor).

  The following examples will use the dogm132 device: u8g_dev_st7565_dogm132_sw_spi

  Note: The device must match the setup: For example, do not use a sw_spi device with u8g_InitHWSPI().
*/

u8g_t u8g;

void u8g_setup(void)
{  
  /*
    Test Envionment 1, ATMEGA and DOGM132 
    SCK: PORTB, Bit 5
    MOSI: PORTB, Bit 3
    CS: PORTB, Bit 2
    A0: PORTB, Bit 1
  */
  //u8g_InitSPI(&u8g, &u8g_dev_st7565_dogm132_sw_spi, PN(1, 5), PN(1, 3), PN(1, 2), PN(1, 1), U8G_PIN_NONE);

  /*
    Test Envionment 2, ATMEGA and Seeedstudio 96x96 OLED via I2C
    SCL: Port C, Bit 5
    SDA: Port C, Bit 4
  */
  
  /* activate pull-up, set ports to output, init U8glib */  
  /*
  u8g_SetPinInput(PN(2,5)); u8g_SetPinLevel(PN(2,5), 1); u8g_SetPinOutput(PN(2,5));
  u8g_SetPinInput(PN(2,4)); u8g_SetPinLevel(PN(2,4), 1); u8g_SetPinOutput(PN(2,4));
  u8g_InitI2C(&u8g, &u8g_dev_ssd1327_96x96_gr_i2c, U8G_I2C_OPT_NONE);
  */
  
  /*
    Test Envionment 3, ATMEGA and NHD 192x32 ST7920 special SPI
    R/W, MOSI, Red: 	Port C, Bit 5
    RS, CS, Yellow: 	Port C, Bit 4
    EN, SCK, Green:	Port C, Bit 3
    Arguments for u8g_InitSPI are: SCK, MOSI, CS, A0, Reset
      A0 and Reset are not used.
  */
  //u8g_InitSPI(&u8g, &u8g_dev_st7920_192x32_sw_spi, PN(2, 3), PN(2, 5), PN(2, 4), U8G_PIN_NONE, U8G_PIN_NONE);
  
  /*
    Test Envionment 4, ATMEGA and NHD 192x32 ST7920 special SPI
    R/W, MOSI, Red: 	Port B, Bit 3
    RS, CS, Yellow: 	Port C, Bit 4
    EN, SCK, Green:	Port B, Bit 5
    Arguments for u8g_InitHWSPI are: CS, A0, Reset
      A0 and Reset are not used.
  */
  // u8g_SetPinOutput(PN(1,2));
  u8g_InitHWSPI(&u8g, &u8g_dev_st7920_192x32_hw_spi, PN(2, 4), U8G_PIN_NONE, U8G_PIN_NONE);

  
}

void sys_init(void)
{
#if defined(__AVR__)
  /* select minimal prescaler (max system speed) */
  CLKPR = 0x80;
  CLKPR = 0x00;
#endif
}

void draw_color_box(void)
{
  u8g_uint_t w,h;
  u8g_uint_t r, g, b;
  
  w = u8g_GetWidth(&u8g)/32;
  h = u8g_GetHeight(&u8g)/8;
  for( b = 0; b < 4; b++ )
    for( g = 0; g < 8; g++ )
      for( r = 0; r < 8; r++ )
      {
        u8g_SetColorIndex(&u8g, (r<<5) |  (g<<2) | b );
        u8g_DrawBox(&u8g, g*w + b*w*8, r*h, w, h);
      }
}

void draw_logo(uint8_t d)
{
  u8g_SetFont(&u8g, u8g_font_gdr25r);
  u8g_DrawStr(&u8g, 0+d, 30+d, "U");
  u8g_SetFont(&u8g, u8g_font_gdr30n);
  u8g_DrawStr90(&u8g, 23+d,10+d,"8");
  u8g_SetFont(&u8g, u8g_font_gdr25r);
  u8g_DrawStr(&u8g, 53+d,30+d,"g");
  
  u8g_DrawHLine(&u8g, 2+d, 35+d, 47);
  u8g_DrawVLine(&u8g, 45+d, 32+d, 12);
}

void draw_url(void)
{
  u8g_SetFont(&u8g, u8g_font_4x6);
  if ( u8g_GetHeight(&u8g) < 59 )
  {
    u8g_DrawStr(&u8g, 53,9,"code.google.com");
    u8g_DrawStr(&u8g, 77,18,"/p/u8glib");
  }
  else
  {
    u8g_DrawStr(&u8g, 1,54,"code.google.com/p/u8glib");
  }
}


void draw(void) 
{
  if ( u8g_GetMode(&u8g) == U8G_MODE_R3G3B2 ) 
  {
    draw_color_box();
  }
  u8g_SetColorIndex(&u8g, 1);
  if ( U8G_MODE_GET_BITS_PER_PIXEL(u8g_GetMode(&u8g)) > 1 ) 
  {
    draw_logo(2);
    u8g_SetColorIndex(&u8g, 2);
    draw_logo(1);
    u8g_SetColorIndex(&u8g, 3);
  }
  draw_logo(0);
  draw_url();
}

int main(void)
{
  sys_init();
  u8g_setup();
  
  for(;;)
  {  
    u8g_FirstPage(&u8g);
    do
    {
      draw();
    } while ( u8g_NextPage(&u8g) );
    u8g_Delay(10);
  }
}

