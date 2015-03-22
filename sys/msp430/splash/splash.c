/*

  splash.c 
  
  Universal 8bit Graphics Library
  
  Copyright (c) 2015, hugodan3@googlemail.com
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

/* 
 * below header has been generated 
 * from a 8bit BMP file.
 */
#include "arduino.h"

#include <msp430.h>

#define COLOR_128_DISPLAY	1


u8g_t u8g;

void u8g_setup(void)
{  
#if COLOR_128_DISPLAY != 1
  u8g_InitHWSPI(&u8g, &u8g_dev_sh1106_128x64_hw_spi, PN(2, 0) /*CSB*/, PN(2,2)/*CD*/, PN(2,6)/*RS*/);
#else
  u8g_InitHWSPI(&u8g, &u8g_dev_ssd1353_160x128_332_hw_spi, PN(2, 0) /*CSB*/, PN(2,2)/*CD*/, PN(2,6)/*RS*/);
#endif
}


void
sys_init(void)
{
#if defined(__MSP430__)
  UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_5;                      // Select DCO range above 16MHz operation
  UCSCTL2 = FLLD_1 + 750;                   // Set DCO Multiplier for 25Mhz
  __bic_SR_register(SCG0);                  // Enable the FLL control loop
  __delay_cycles(250000);
  P3SEL |= BIT0|BIT2;                       // setup alternative mode
#endif
}


/* void u8g_Draw8Pixel(u8g_t *u8g, u8g_uint_t x, u8g_uint_t y, uint8_t dir, uint8_t pixel); */
void draw_splash(int x0, int y0)
{
	int x,y;
	int xmax = arduino[2], ymax = arduino[1];
	for (y=0; y < ymax; y++)
	{
		for (x=0; x <xmax; x++)
		{
			register uint8_t pix = arduino[2+x+y*xmax];
			if (pix)
			{
				u8g_Draw8ColorPixel(&u8g, x+x0, y+y0, pix);
			}
		}
	}
   	u8g_SetDefaultForegroundColor(&u8g);
    	u8g_SetFont(&u8g, u8g_font_6x10);
	u8g_DrawStr(&u8g, 20, 110, "Hello world!");
}

int main(void)
{
  sys_init();
  u8g_setup();

  u8g_FirstPage(&u8g);
  do
  {
    draw_splash(0,0);
  } while ( u8g_NextPage(&u8g) );
}

