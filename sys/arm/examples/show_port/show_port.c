/*
  
  show_port.c
  
  >>> PLEASE UNCOMMENT DISPLAY TYPE IN THE MAIN PROCEDURE <<<
  
  ARM U8glib Example

  Universal 8bit Graphics Library
  
  Copyright (c) 2013, olikraus@gmail.com
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

#include "u8g_arm.h"


/*========================================================================*/
/* SystemInit & SysTick Interrupt */

#define SYS_TICK_PERIOD_IN_MS 10

void SystemInit()
{    
  init_system_clock();		/* SystemCoreClock will be set here */
  
  /* SysTick is defined in core_cm0.h */
  SysTick->LOAD = (SystemCoreClock/1000UL*(unsigned long)SYS_TICK_PERIOD_IN_MS) - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = 7;   /* enable, generate interrupt (SysTick_Handler), do not divide by 2 */
}

void __attribute__ ((interrupt)) SysTick_Handler(void)
{
}

/*========================================================================*/
/* main */

u8g_t u8g;

void draw_bin(u8g_uint_t x, u8g_uint_t y, uint8_t cnt, uint32_t bits)
{
  char s[34];
  uint8_t i;
  for( i = 0; i < cnt; i++ )
  {
    if ( (bits & (1<<i)) == 0 )
    {
      s[cnt-1-i] = '0';
    }
    else
    {
      s[cnt-1-i] = '1';
    }
  }
  s[cnt] = '\0';
  u8g_DrawStr(&u8g,  x, y, s);
}

void draw(uint8_t cnt, uint32_t dir, uint32_t port)
{
  u8g_SetFont(&u8g, u8g_font_unifont);
  u8g_DrawStr(&u8g,  0, 1*12, "DIR");
  draw_bin(0,2*12, cnt, dir);
  u8g_DrawStr(&u8g,  0, 3*12, "PORT");
  draw_bin(0,4*12, cnt, port);
}

void main()
{
  /*
    Please uncomment one of the displays below
    Notes:
      - "2x", "4x": high speed version, which uses more RAM
      - "hw_spi": All hardware SPI devices can be used with software SPI also.
	Access type is defined by u8g_com_hw_spi_fn
  */

  // u8g_InitComFn(&u8g, &u8g_dev_uc1701_dogs102_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1701_dogs102_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1701_mini12864_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1701_mini12864_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_dogm132_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_dogm128_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_dogm128_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_lm6059_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_lm6059_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_lm6063_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_lm6063_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_nhd_c12864_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_nhd_c12864_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_nhd_c12832_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_64128n_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_64128n_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1601_c128032_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1601_c128032_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1610_dogxl160_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1610_dogxl160_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1610_dogxl160_2x_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1610_dogxl160_2x_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_pcd8544_84x48_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_pcf8812_96x65_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_2x_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_2x_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1327_96x96_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1327_96x96_2x_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1322_nhd31oled_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1322_nhd31oled_2x_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1322_nhd31oled_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1322_nhd31oled_2x_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1309_128x64_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x32_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x32_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_332_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_4x_332_hw_spi, u8g_com_hw_spi_fn);
   u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_hicolor_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_4x_hicolor_hw_spi, u8g_com_hw_spi_fn);
  
  
  u8g_SetDefaultForegroundColor(&u8g);

  set_gpio_mode(DEFAULT_KEY, 0, 1);

  for(;;)
  {
    /* picture loop */
    u8g_FirstPage(&u8g);
    do
    {
      draw(12, LPC_GPIO0->DIR, LPC_GPIO0->DATA);
      
      if ( get_gpio_level(DEFAULT_KEY) == 0 )
	u8g_DrawStr(&u8g, 0,6*12,"0");
      else
	u8g_DrawStr(&u8g, 0,6*12,"1");
    } while ( u8g_NextPage(&u8g) );
    
    /* refresh screen after some delay */
    u8g_Delay(100);
    
  }  
}

