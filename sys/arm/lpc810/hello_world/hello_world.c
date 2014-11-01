/*

  hello_world.c
  
  Universal 8bit Graphics Library
  
  Copyright (c) 2014, olikraus@gmail.com
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



#include "chip.h"
#include "lpc81x_system.h"
#include "u8g.h"




/*========================================================================*/
/* main */

u8g_t u8g;

void draw(uint8_t pos)
{
  u8g_SetFont(&u8g, u8g_font_5x8r);
  u8g_DrawStr(&u8g,  0, 12+pos*2, "Hello World!");
}

void u8g_main()
{
  uint8_t pos = 0;
  /*
    Please uncomment one of the displays below
    Notes:
      - "2x", "4x": high speed version, which uses more RAM
      - "hw_spi": All hardware SPI devices can be used with software SPI also.
	Access type is defined by u8g_com_hw_spi_fn
  */

  u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_hw_spi, u8g_com_ssd_i2c_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_2x_hw_spi, u8g_com_ssd_i2c_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1309_128x64_hw_spi, u8g_com_ssd_i2c_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x32_hw_spi, u8g_com_ssd_i2c_fn);
  
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x32_2x_hw_spi, u8g_com_ssd_i2c_fn);
  
  
  u8g_SetDefaultForegroundColor(&u8g);

  for(;;)
  {
    /* picture loop */
    Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 0, 2); 	
    u8g_FirstPage(&u8g);
    do
    {
      draw(pos);
    } while ( u8g_NextPage(&u8g) );
    
    Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 2);    
    
    /* refresh screen after some delay */
    u8g_Delay(100);
    
    /* update position */
    pos++;
    pos &= 15;
  }  
}



/*=======================================================================*/
/* main procedure, called by "Reset_Handler" */

int __attribute__ ((noinline)) main(void)
{

  /* set systick and start systick interrupt */
  SysTick_Config(SYS_CORE_CLOCK/1000UL*(unsigned long)SYS_TICK_PERIOD_IN_MS);
  
  /* turn on GPIO */
  Chip_GPIO_Init(LPC_GPIO_PORT);

  /* disable SWCLK and SWDIO, after reset, boot code may activate this */
  Chip_SWM_DisableFixedPin(2);
  Chip_SWM_DisableFixedPin(3);
  
  /* turn on IOCON */
  Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);
  
  /* turn on switch matrix */
  Chip_SWM_Init();
  
  /* activate analog comperator */
  Chip_ACMP_Init(LPC_CMP);

  /* let LED on pin 4 of the DIP8 blink */
  Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 2);  
  
  delay_micro_seconds(100000UL);

  u8g_main();
  
  /* enter sleep mode: Reduce from 1.4mA to 0.8mA with 12MHz */  
  while (1)
  {
    SCB->SCR |= (1UL << SCB_SCR_SLEEPONEXIT_Pos);		/* enter sleep mode after interrupt */ 
    Chip_PMU_SleepState(LPC_PMU);						/* enter sleep mode now */
  }
}

