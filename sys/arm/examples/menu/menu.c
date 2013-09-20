/*

  menu.c 
  
  Simple Menu for ATMEGA Controller
  
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

void u8g_setup(void)
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
  u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_332_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_4x_332_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_hicolor_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_4x_hicolor_hw_spi, u8g_com_hw_spi_fn);
  
  
  u8g_SetDefaultForegroundColor(&u8g);

}


void sys_setup_keys(void)
{
  /* configure GPIO as input with pullup */
  set_gpio_mode(DEFAULT_KEY, 0, 1);
  // set_gpio_mode(PIN(1,5), 0, 1);
}

#define KEY_NONE 0
#define KEY_PREV 1
#define KEY_NEXT 2
#define KEY_SELECT 3
#define KEY_BACK 4

uint8_t sys_get_key(void)
{
  uint8_t result = KEY_NONE;
  if ( get_gpio_level(DEFAULT_KEY) != 0 )
    result = KEY_NEXT;
  // if ( get_gpio_level(PIN(1,5)) != 0 )
  //   result = KEY_PREV;
  return result;
}

uint8_t sys_key_first = KEY_NONE;
uint8_t sys_key_second = KEY_NONE;
uint8_t sys_key_code = KEY_NONE;


void sys_debounce_key(void) 
{
  sys_key_second = sys_key_first;
  sys_key_first = sys_get_key();
    
  if ( sys_key_second == sys_key_first )
    sys_key_code = sys_key_first;
  else
    sys_key_code = KEY_NONE;
}


#define MENU_ITEMS 4
char *menu_strings[MENU_ITEMS] = { "First Line", "Second Item", "3333333", "abcdefg" };

uint8_t menu_current = 0;
uint8_t menu_redraw_required = 0;
uint8_t last_key_code = KEY_NONE;

void draw_menu(void) 
{
  uint8_t i, h;
  u8g_uint_t w, d;

  u8g_SetFont(&u8g, u8g_font_5x7);
  u8g_SetFontRefHeightText(&u8g);
  u8g_SetFontPosTop(&u8g);
  
  h = u8g_GetFontAscent(&u8g)-u8g_GetFontDescent(&u8g);
  w = u8g_GetWidth(&u8g);
  for( i = 0; i < MENU_ITEMS; i++ ) 
  {
    d = (w-u8g_GetStrWidth(&u8g, menu_strings[i]))/2;
    u8g_SetDefaultForegroundColor(&u8g);
    if ( i == menu_current ) 
    {
      u8g_DrawBox(&u8g, 0, i*h+1, w, h);
      u8g_SetDefaultBackgroundColor(&u8g);
    }
    u8g_DrawStr(&u8g, d, i*h, menu_strings[i]);
  }
}

void update_menu(void) 
{
  if ( sys_key_code != KEY_NONE && last_key_code == sys_key_code ) 
  {
    return;
  }
  last_key_code = sys_key_code;
  
  switch ( sys_key_code ) 
  {
    case KEY_NEXT:
      menu_current++;
      if ( menu_current >= MENU_ITEMS )
        menu_current = 0;
      menu_redraw_required = 1;
      break;
    case KEY_PREV:
      if ( menu_current == 0 )
        menu_current = MENU_ITEMS;
      menu_current--;
      menu_redraw_required = 1;
      break;
  }
}

int main(void)
{
  sys_setup_keys();
  u8g_setup();

  menu_redraw_required = 1;
  for(;;)
  {  
    
    sys_debounce_key();
    
    if (  menu_redraw_required != 0 ) 
    {
      u8g_FirstPage(&u8g);
      do
      {
        draw_menu();
      } while ( u8g_NextPage(&u8g) );
      menu_redraw_required = 0;
    }

    update_menu();
  }
}

