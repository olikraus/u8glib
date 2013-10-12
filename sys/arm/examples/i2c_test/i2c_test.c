/*
  
  i2c_test.c
  
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
uint16_t test_cnt = 0;

uint8_t i2c_buf[2] = { 0x0ab, 0x0aa };

i2c_struct i2c;

void draw(uint8_t pos)
{
  u8g_SetFont(&u8g, u8g_font_5x7r);
  u8g_DrawStr(&u8g,   0, 7, "TestCnt:");
  u8g_DrawStr(&u8g,  60, 7, u8g_u16toa(test_cnt, 4));
  u8g_DrawStr(&u8g,   0, 7+8, "ErrState:");
  u8g_DrawStr(&u8g,  60, 7+8, u8g_u8toa(i2c.err_state, 2));
  u8g_DrawStr(&u8g,   0, 7+16, "ErrCode:");
  u8g_DrawStr(&u8g,  60, 7+16, u8g_u8toa(i2c.err_code, 2));
  u8g_DrawStr(&u8g,   0, 7+24, "HW State:");
  u8g_DrawStr(&u8g,  60, 7+24, u8g_u8toa(i2c.err_hw_stat, 3));
  u8g_DrawStr(&u8g,  90, 7+24, u8g_u8toa(i2c_buf[0], 3));
}

void main()
{
  uint8_t pos = 0;
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
  u8g_InitComFn(&u8g, &u8g_dev_st7565_nhd_c12832_hw_spi, u8g_com_hw_spi_fn);
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
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_hicolor_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_4x_hicolor_hw_spi, u8g_com_hw_spi_fn);
  
  
  u8g_SetDefaultForegroundColor(&u8g);

  for(;;)
  {
    /* picture loop */
    u8g_FirstPage(&u8g);
    do
    {
      draw(pos);
    } while ( u8g_NextPage(&u8g) );

    if ( i2c_send_3byte(&i2c, 0x050, test_cnt >> 8, test_cnt & 255, 255 - (test_cnt & 255), 1) != 0 )
    {
      u8g_Delay(20);
      if ( i2c_send_2byte(&i2c, 0x050, test_cnt >> 8, test_cnt & 255, 0) != 0 )
      {
	i2c_receive_data(&i2c, 0x050, 1, i2c_buf, 1);
      }
    }

    
    test_cnt++;
    
    /* refresh screen after some delay */
    u8g_Delay(480);
    
    /* update position */
    pos++;
    pos &= 15;
  }  
}

