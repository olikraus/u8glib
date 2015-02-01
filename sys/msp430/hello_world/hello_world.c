/*

  main.c 
  
  Hello World for MSP430

  Universal 8bit Graphics Library
  
  Copyright (c) 2014, daniel_sittig@yahoo.com
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

#if defined(__MSP430__)
#include <msp430.h>
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

  Note: The device must match the setup: For example, do not use a sw_spi device with u8g_InitHWSPI().
*/

u8g_t u8g;

void u8g_setup(void)
{  
  /* 
    HW SPI on the MSP430F5529 LaunchPad Eval Kit
    u8glib will use UCB0 by default
      P3.2:	D0/CLK
      P3.0:	D1/DATA/MOSI/SIMO
      P2.0:	Chip Select
      P2.2:	Command/Data select (CD/A0)
      P2.6: 	Display Reset
  */
  //P3SEL |= BIT0|BIT2;                       // setup alternative mode
  //u8g_InitHWSPI(&u8g, &u8g_dev_ssd1306_128x64_hw_spi, PN(2, 0) /*CSB*/, PN(2,2)/*CD*/, PN(2,6)/*RS*/);
  
  /* 
    SW SPI on the MSP430F5529 LaunchPad Eval Kit
      P3.2:	D0/CLK
      P3.0:	D1/DATA/MOSI/SIMO
      P2.0:	Chip Select
      P2.2:	Command/Data select (CD/A0)
      P2.6: 	Display Reset
  */
  u8g_InitSPI(&u8g, &u8g_dev_ssd1306_128x64_sw_spi, PN(3, 2) /*CLK*/, PN(3, 0) /*DATA*/, PN(2, 0) /*CSB*/, PN(2,2)/*CD*/, PN(2,6)/*RS*/);
}

/* 
 * Default CPU speed on MSP430 on SMCLK is 1.045M. Use sys_init to change clock and F_CPU to define 
 */
void sys_init(void)
{
}

void draw(int i)
{
  u8g_SetFont(&u8g, u8g_font_04b_03b);
  u8g_DrawStr(&u8g, i, 15, "Hello World!");
}

int main(void)
{
  int i;
  sys_init();
  u8g_setup();

  for(;;)
  {
    for(i=0;i<15;i++)
    {  
      u8g_FirstPage(&u8g);
      do
      {
	draw(i);
      } while ( u8g_NextPage(&u8g) );
      u8g_Delay(100);
    }
  }
  return 0;
}
