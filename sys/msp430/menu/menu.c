/*

  main.c 
  
  Simple Menu for ATMEGA Controller

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


#include <msp430.h>

#define COLOR_128_DISPLAY	1


u8g_t u8g;

void u8g_setup(void)
{  
#if COLOR_128_DISPLAY != 1
  u8g_InitHWSPI(&u8g, &u8g_dev_sh1106_128x64_hw_spi, PN(2, 0) /*CSB*/, PN(2,2)/*CD*/, PN(2,6)/*RS*/);
#else
 // u8g_InitHWSPI(&u8g, &u8g_dev_ssd1353_160x128_hicolor_hw_spi, PN(2, 0) /*CSB*/, PN(2,2)/*CD*/, PN(2,6)/*RS*/);
  u8g_InitHWSPI(&u8g, &u8g_dev_ssd1353_160x128_332_hw_spi, PN(2, 0) /*CSB*/, PN(2,2)/*CD*/, PN(2,6)/*RS*/);
#endif
}


void
sys_init(void)
{
  UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
  UCSCTL2 = FLLD_1 + 488;                   // Set DCO Multiplier for 16MHz
  __bic_SR_register(SCG0);                  // Enable the FLL control loop
  __delay_cycles(250000);
  P3SEL |= BIT0|BIT2;                       // setup alternative mode
}


void sys_setup_keys(void)
{
#if defined(__MSP430__)
  P1REN |= 0x02;
  P1OUT |= 0x02;
  P2REN |= 0x02;
  P2OUT |= 0x02;
#endif
}

#define KEY_NONE 0
#define KEY_PREV 1
#define KEY_NEXT 2

uint8_t sys_get_key(void)
{
  uint8_t result = KEY_NONE;
#if defined(__MSP430__)
  if ( (P1IN & (1<<1)) == 0 )
    result = KEY_PREV;
  if ( (P2IN & (1<<1)) == 0 )
    result = KEY_NEXT;
#endif
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

#if COLOR_128_DISPLAY == 1
#define MENU_ITEMS 10
char *menu_strings[MENU_ITEMS] = { "First Line", "Second Item", "Third Item", "Fourth Item", "Fifth Item", "Sixth Item", "Seven", "Eight line", "Ninth Point", "Last Entry" };
#else
#define MENU_ITEMS 4
char *menu_strings[MENU_ITEMS] = { "First Line", "Second Item", "Third Item", "Fourth Item" };
#endif

uint8_t menu_current = 0;
uint8_t menu_redraw_required = 0;
uint8_t last_key_code = KEY_NONE;

void draw_menu(void) 
{
  uint8_t i, h;
  u8g_uint_t w, d;

  u8g_SetFont(&u8g, u8g_font_8x13);

  u8g_SetFontRefHeightText(&u8g);
  u8g_SetFontPosTop(&u8g);

  h = u8g_GetFontAscent(&u8g)-u8g_GetFontDescent(&u8g);
  w = u8g_GetWidth(&u8g);

  for( i = 0; i < MENU_ITEMS; i++ ) 
  {
    d = (w-u8g_GetStrWidth(&u8g, menu_strings[i]))/2;
#if COLOR_128_DISPLAY != 1
    u8g_SetDefaultForegroundColor(&u8g);
#else
    u8g_SetDefaultMidColor(&u8g);
#endif
    if ( i == menu_current ) 
    {
#if COLOR_128_DISPLAY == 1
      u8g_SetDefaultForegroundColor(&u8g);
#endif
      u8g_DrawBox(&u8g, 0, ((i+1)*h+1), w, h);
      u8g_SetDefaultBackgroundColor(&u8g);
      u8g_SetContrast(&u8g, 128);
    }
    u8g_DrawStr(&u8g, d, (i+1)*h, menu_strings[i]);
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
  sys_init();
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

