/*

  main.c
  
  Flashing LED (Port 0_2, LPC810, DIP8)

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



#include "chip.h"
#include "sys.h"
#include "oled.h"
#include "port.h"


#define SYS_CORE_CLOCK 12000000UL
#define SYS_TICK_PERIOD_IN_MS 50

unsigned hour = 0;
unsigned minute = 0;


/*=======================================================================*/

void draw_hm(oled_t *oled, unsigned h, unsigned m)
{
  unsigned x, y, d;
  y = 47;
  x = 0;
  d = 25;
  oled_draw_glyph(oled, x, y, '0' + h / 10);
  x += d;
  oled_draw_glyph(oled, x, y, '0' + h % 10);
  x += d;
  oled_draw_glyph(oled, x, y, ':');
  x += d/2;
  oled_draw_glyph(oled, x, y, '0' + m / 10);
  x += d;
  oled_draw_glyph(oled, x, y, '0' + m % 10);
  x += d;
}

/*=================================================*/


//Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 2);
const uint16_t pcs_led_out[] = 
{  
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  PCS_SETB(2, 0x000/4) | PCS_END
};

//Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 0, 2); 	
const uint16_t pcs_led_high[] = 
{  
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  PCS_SETB(2, 0x200/4) | PCS_END
};

//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 2);    
const uint16_t pcs_led_low[] = 
{
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  PCS_SETB(2, 0x280/4) | PCS_END
};


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
  //Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 2);
  pcs(pcs_led_out);
  
  oled_init();
  
  for(;;)
  {    
    pcs(pcs_led_high);
    delay_micro_seconds(500000UL);
    pcs(pcs_led_low);
    delay_micro_seconds(500000UL);
    
    
    oled_start_page(&oled_o);
    do
    {
      //oled_draw_hline(&oled_o, 0,5,60);
      //oled_draw_hline(&oled_o, 0,5+8,60);
      oled_set_font(&oled_o, logisoso46);
      draw_hm(&oled_o, hour, minute);
      oled_set_font(&oled_o, helvR14small);
      oled_draw_string(&oled_o, 0, 63, "HELLO");
    }
    while( oled_next_page(&oled_o) );
    
      hour++;
    if ( hour >= 24 )
      hour = 0;
    minute++;
    if ( minute >= 60 )
      minute = 0;
  }

  
  /* enter sleep mode: Reduce from 1.4mA to 0.8mA with 12MHz */  
  while (1)
  {
    SCB->SCR |= (1UL << SCB_SCR_SLEEPONEXIT_Pos);		/* enter sleep mode after interrupt */ 
    Chip_PMU_SleepState(LPC_PMU);						/* enter sleep mode now */
  }
}

