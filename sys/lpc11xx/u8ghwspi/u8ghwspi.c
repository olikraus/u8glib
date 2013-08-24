/*
  
  u8ghwspi.c
  
  ARM U8g Example with HW SPI 

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

#include "u8g_lpc11xx.h"

#define SYS_TICK_PERIOD_IN_MS 10


/*========================================================================*/
/* SystemInit */


uint32_t SystemCoreClock;

void SystemInit()
{    
  
#if F_CPU >= 48000000
  /* SystemInit() is called by the startup code */
  lpc11xx_set_irc_48mhz();
#endif
  
  /* according to system_LPC11xx.h it is expected, that the clock freq is set int SystemInit() */
  SystemCoreClock = F_CPU;
  
  /* SysTick is defined in core_cm0.h */
  SysTick->LOAD = (SystemCoreClock/1000UL*(unsigned long)SYS_TICK_PERIOD_IN_MS) - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = 7;   /* enable, generate interrupt, do not divide by 2 */
}


/*========================================================================*/
/* SysTick */

volatile uint32_t sys_tick_irq_cnt=0;

void __attribute__ ((interrupt)) SysTick_Handler(void)
{
  sys_tick_irq_cnt++;
}

/*========================================================================*/

#define A0_GPIO	LPC_GPIO0
#define A0_PIN 	11

#define CS_GPIO	LPC_GPIO0
#define CS_PIN 	6

#define RST_GPIO	LPC_GPIO0
#define RST_PIN 	5


uint8_t u8g_com_hw_spi_gps_board_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_STOP:
      break;
    
    case U8G_COM_MSG_INIT:

      LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	/* enable IOCON clock */

      spi_init(400);

      LPC_IOCON->PIO0_5 = 1<<8;			/* select standard GPIO mode, disable I2C */
      LPC_IOCON->PIO0_6 = 128+64;				/* select GPIO mode */
      LPC_IOCON->R_PIO0_11 = 128+64+1;			/* select GPIO mode */
        
      A0_GPIO->DIR |= 1 << A0_PIN;
      CS_GPIO->DIR |= 1 << CS_PIN;
      RST_GPIO->DIR |= 1 << RST_PIN;
      
      u8g_MicroDelay();      
      break;
    
    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      u8g_10MicroDelay();
      if ( arg_val != 0 )
	  A0_GPIO->DATA |= 1 << A0_PIN;
      else
	  A0_GPIO->DATA &= ~(1 << A0_PIN);
      u8g_10MicroDelay();
     break;

    case U8G_COM_MSG_CHIP_SELECT:
      if ( arg_val == 0 )
      {
        /* disable */
	uint8_t i;
	
	/* this delay is required to avoid that the display is switched off too early --> DOGS102 with LPC1114 */
	for( i = 0; i < 5; i++ )
	  u8g_10MicroDelay();
	CS_GPIO->DATA |= 1 << CS_PIN;
	u8g_MicroDelay();
      }
      else
      {
        /* enable */
	CS_GPIO->DATA &= ~(1 << CS_PIN);
	u8g_MicroDelay();
      }
      break;
      
    case U8G_COM_MSG_RESET:
      if ( arg_val != 0 )
	  RST_GPIO->DATA |= 1 << RST_PIN;
      else
	  RST_GPIO->DATA &= ~(1 << RST_PIN);
      u8g_10MicroDelay();
      break;
      
    case U8G_COM_MSG_WRITE_BYTE:
      spi_out(arg_val);
      u8g_MicroDelay();
      break;
    
    case U8G_COM_MSG_WRITE_SEQ:
    case U8G_COM_MSG_WRITE_SEQ_P:
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
          spi_out(*ptr++);
          arg_val--;
        }
      }
      break;
  }
  return 1;
}


/*========================================================================*/
/* main */

#define LED_GPIO	LPC_GPIO1
#define LED_PIN 8			

u8g_t u8g;

void draw(uint8_t pos)
{
  if ( u8g_GetMode(&u8g) == U8G_MODE_HICOLOR || u8g_GetMode(&u8g) == U8G_MODE_R3G3B2) {
    /* draw background (area is 128x128) */
    u8g_uint_t r, g, b;
    for( b = 0; b < 4; b++ )
    {
      for( g = 0; g < 32; g++ )
      {
	for( r = 0; r < 32; r++ )
	{
	  u8g_SetRGB(&u8g, r<<3, g<<3, b<<4 );
	  u8g_DrawPixel(&u8g, g + b*32, r);
	  u8g_SetRGB(&u8g, r<<3, g<<3, (b<<4)+64 );
	  u8g_DrawPixel(&u8g, g + b*32, r+32);
	  u8g_SetRGB(&u8g, r<<3, g<<3, (b<<4)+128 );
	  u8g_DrawPixel(&u8g, g + b*32, r+32+32);
	  u8g_SetRGB(&u8g, r<<3, g<<3, (b<<4)+128+64 );
	  u8g_DrawPixel(&u8g, g + b*32, r+32+32+32);
	}
      }
    }
    u8g_SetRGB(&u8g, 255,255,255);
  }
  u8g_SetFont(&u8g, u8g_font_unifont);
  u8g_DrawStr(&u8g,  0, 22+pos, "Hello World!");
}

void main()
{
  volatile uint32_t i, cnt = 100000;
  LED_GPIO->DIR |= 1 << LED_PIN;
    uint8_t pos = 0;

  //spi_init(50);
  
  //u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_hicolor_hw_spi, u8g_com_hw_spi_fn);
  //u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_332_hw_spi, u8g_com_hw_spi_fn);
  //u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_bw_hw_spi, u8g_com_hw_spi_fn);
  //u8g_InitComFn(&u8g, &u8g_dev_st7565_dogm132_hw_spi, u8g_com_hw_spi_fn);
  u8g_InitComFn(&u8g, &u8g_dev_uc1701_dogs102_hw_spi, u8g_com_hw_spi_gps_board_fn);
  //u8g_InitComFn(&u8g, &u8g_dev_uc1701_dogs102_hw_spi, u8g_com_hw_spi_fn);

  for(;;)
  {
    u8g_FirstPage(&u8g);
    do
    {
      draw(pos);
    } while ( u8g_NextPage(&u8g) );
    LED_GPIO->DATA |= 1 << LED_PIN;
    u8g_Delay(100);
    LED_GPIO->DATA &= ~(1 << LED_PIN);
    u8g_Delay(100);
    
    pos++;
    pos &= 15;
  }
  
}
