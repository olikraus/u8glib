/*

  analog_value.c

  output analog values
  
  Hello World for ATTINY84 Controller

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

void sys_init(void)
{
#if defined(__AVR__)
  /* select minimal prescaler (max system speed) */
  CLKPR = 0x80;
  CLKPR = 0x00;
#endif
}

#define ADC_PRESCALAR 0x07
/*
  Notes
  - Internet: ADCH is stable after ADEN = 0 (shutdown)
  - Internet: Discard first conversion result
*/

/*
  measure voltage difference between ADC0 (positive, PORT A/Pin 0) and ADC1 (negative, PORT A/Pin 1)
  gain_bit == 0: 1x
  gain_bit == 1: 20x
*/
uint16_t sys_diff_adc_2_3(uint8_t gain_bit)
{
  uint16_t l, h;
  
  /* datasheet recomends to turn off ADC for differntial measurement first */
  ADCSRA = 0x00 | ADC_PRESCALAR;		/* turn off ADC */  

  /* use PA2 and PA3 as input  */
  DDRA &= ~_BV(2);
  DDRA &= ~_BV(3);

  /* enable, but do not start ADC (ADEN, Bit 7) */
  /* clear the interrupt indicator flag (ADIF, Bit 4) */
  ADCSRA = 0x90 | ADC_PRESCALAR;
  
  ADMUX = 16 | gain_bit;
  /* enable bipolar mode, voltage diff may be higher or lower, result is signed */
  ADCSRB = 0x080;
  /* enable and start conversion  */
  ADCSRA = 0xc0|ADC_PRESCALAR;
  /* wait for conversion to be finished (ADIF, Bit 4) */
  while ( (ADCSRA & _BV(4)) == 0 )
    ;
  /* return 8 bit result */
  l = ADCL;
  h = ADCH;
  
  /* save some power */
  ADCSRA = 0x00 | ADC_PRESCALAR;		/* turn off ADC */  
  
  return (h<<8) | l ;  
}


/* read from adc7 (Port A, Pin 7) */
uint16_t sys_adc7(void)
{
  uint16_t l, h;

  /* turn off ADC to force long conversion */
  ADCSRA = 0x00 | ADC_PRESCALAR;		/* turn off ADC */  

  /* use PA7 as input pin for the ADC */
  DDRA &= ~_BV(7);
  
  /* enable, but do not start ADC (ADEN, Bit 7) */
  /* clear the interrupt indicator flag (ADIF, Bit 4) */
  ADCSRA = 0x90 | ADC_PRESCALAR;
  
  /* ADC 7, wait for conversion finished*/
  //while( ADCSRA & _BV(6) )
  //  ;
  ADMUX = 7;	
  /* default operation */
  ADCSRB = 0x0;
  /* enable and start conversion, maximum prescalar */
  ADCSRA = 0xc0|ADC_PRESCALAR;
  /* wait for conversion to be finished (ADIF, Bit 4) */
  while ( (ADCSRA & _BV(4)) == 0 )
    ;
  /* return 8 bit result */
  
  l = ADCL;
  h = ADCH;

  /* save some power */
  ADCSRA = 0x00 | ADC_PRESCALAR;		/* turn off ADC */  
  
  return (h<<8) | l ;
}

void u8g_setup(void)
{  
  /*
    Test Envionment: ATTINY84 and DOGM132 
    CS: PORTB, Bit 0
    A0: PORTB, Bit 1
    SCK: PORTA, Bit 4
    MOSI: PORTA, Bit 5
  */
  u8g_InitSPI(&u8g, &u8g_dev_st7565_dogm132_sw_spi, PN(0, 4) , PN(0, 5), PN(1, 0), PN(1, 1), U8G_PIN_NONE);  
}

uint16_t adc_val1 = 0;
uint16_t adc_val2 = 0;
uint8_t sign;
uint16_t val;
int16_t sval;
int16_t min = 2000;
int16_t max = -2000;


void draw_signed(uint8_t x, uint8_t y, int16_t v)
{
  if ( v < 0 )
  {
    u8g_DrawStr(&u8g, x, y, "-");
    u8g_DrawStr(&u8g, x+8, y, u8g_u16toa(-v, 3));
  }
  else
  {
    u8g_DrawStr(&u8g, x, y, "+");
    u8g_DrawStr(&u8g, x+8, y, u8g_u16toa(v, 3));
  }
}


void draw(void)
{
  u8g_SetFont(&u8g, u8g_font_fixed_v0r);
  //u8g_SetFont(&u8g, u8g_font_7x13r);
  u8g_DrawStr(&u8g, 0, 10, "Analog Values");
  u8g_DrawStr(&u8g, 0, 20, u8g_u16toa(adc_val1, 4));
  u8g_DrawStr(&u8g, 40, 20, u8g_u16toa(adc_val2, 4));
  u8g_DrawStr(&u8g, 80, 20, sign == 0 ? "+" : "-");
  u8g_DrawStr(&u8g, 80+8, 20, u8g_u16toa(val, 3));
  
  draw_signed(0, 30, sval);
  draw_signed(40, 30, min);
  draw_signed(80, 30, max);
  
}

int main(void)
{
  uint8_t i;
  sys_init();
  u8g_setup();

  for(;;)
  {  
    
    /* 
      why do we need two conversons???  seen notes above
    */
    
    for( i = 0; i < 100; i++ )
    {
      adc_val1 = sys_adc7();
      //adc_val1 = sys_adc7();
      adc_val2 = sys_diff_adc_2_3(1);
      //adc_val2 = sys_diff_adc_2_3(1);
      
      sign = 0;
      val = adc_val2;
      if ( val >= 512 )
      {
	sign = 1;
	val = 1024-val ;
      }
      
      sval = val;
      if ( sign != 0 )
	sval = -sval;
      
      if ( min > sval )
	min = sval;
      
      if ( max < sval )
	max = sval;
    }
    
    
    u8g_FirstPage(&u8g);
    do
    {
      draw();
    } while ( u8g_NextPage(&u8g) );
    u8g_Delay(10);
  }
  
}

