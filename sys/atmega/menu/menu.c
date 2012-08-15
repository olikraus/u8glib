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
    CS: PORTB, Bit 2
    A0: PORTB, Bit 1
    SCK: PORTB, Bit 5
    MOSI: PORTB, Bit 3
  */
  // u8g_InitSPI(&u8g, &u8g_dev_st7565_dogm132_sw_spi, PN(1, 5), PN(1, 3), PN(1, 2), PN(1, 1), U8G_PIN_NONE);

  /*
    Test Envionment 2, ATMEGA and Seeedstudio 96x96 OLED via I2C
    SCL: Port C, Bit 5
    SDA: Port C, Bit 4
  */
  
  /* activate pull-up, set ports to output, init U8glib */  
  u8g_SetPinInput(PN(2,5)); u8g_SetPinLevel(PN(2,5), 1); u8g_SetPinOutput(PN(2,5));
  u8g_SetPinInput(PN(2,4)); u8g_SetPinLevel(PN(2,4), 1); u8g_SetPinOutput(PN(2,4));
  u8g_InitI2C(&u8g, &u8g_dev_ssd1327_96x96_gr_i2c, U8G_I2C_OPT_NONE);

  /*
    Test Envionment 3, ATMEGA and NHD 192x32 ST7920 special SPI
    R/W, MOSI, Red: 	Port C, Bit 5
    RS, CS, Yellow: 	Port C, Bit 4
    EN, SCK, Green:	Port C, Bit 3
    Arguments for u8g_InitSPI are: SCK, MOSI, CS, A0, Reset
      A0 and Reset are not used.
  */
  // u8g_InitSPI(&u8g, &u8g_dev_st7920_192x32_sw_spi, PN(2, 3), PN(2, 5), PN(2, 4), U8G_PIN_NONE, U8G_PIN_NONE);
  
  /* flip screen, if required */
  u8g_SetRot180(&u8g);

  /* assign default color value */
  if ( u8g_GetMode(&u8g) == U8G_MODE_R3G3B2 ) 
    u8g_SetColorIndex(&u8g, 255);     /* white */
  else if ( u8g_GetMode(&u8g) == U8G_MODE_GRAY2BIT )
    u8g_SetColorIndex(&u8g, 3);         /* max intensity */
  else if ( u8g_GetMode(&u8g) == U8G_MODE_BW )
    u8g_SetColorIndex(&u8g, 1);         /* pixel on */
}


void sys_init(void)
{
#if defined(__AVR__)
  /* select minimal prescaler (max system speed) */
  CLKPR = 0x80;
  CLKPR = 0x00;
#endif
}

void sys_setup_keys(void)
{
#if defined(__AVR__)
  /* configure buttons (inputs with pullup) */
  DDRD &= ~(1<<5);
  PORTD |= (1<<5);
  DDRD &= ~(1<<6);
  PORTD |= (1<<6);
  DDRD &= ~(1<<7);
  PORTD |= (1<<7);
  DDRB &= ~(1<<7);
  PORTB |= (1<<7);
#endif
}

#define KEY_NONE 0
#define KEY_PREV 1
#define KEY_NEXT 2
#define KEY_SELECT 3
#define KEY_BACK 4

uint8_t sys_get_key(void)
{
  uint8_t result = KEY_NONE;
#if defined(__AVR__)
  if ( (PIND & (1<<5)) == 0 ) 
    result = KEY_PREV;
  if ( (PIND & (1<<6)) == 0 ) 
    result = KEY_NEXT;
  if ( (PIND & (1<<7)) == 0 ) 
    result |= KEY_SELECT;
  if ( (PINB & (1<<7)) == 0 ) 
    result |= KEY_BACK;
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

