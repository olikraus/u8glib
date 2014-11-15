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


unsigned hour = 0;
unsigned minute = 0;


/*=======================================================================*/

void draw_hm(oled_t *oled, unsigned h, unsigned m)
{
  unsigned x, y, d;
  y = 47;
  x = 0;
  d = 25;
  
  x += oled_draw_num(oled,x,y,d,0,h);
  oled_draw_glyph(oled, x, y, ':');
  x += d/2;
  x += oled_draw_num(oled,x,y,d,1,m);
  
  /*
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
  */
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

//Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 2);    
const uint16_t pcs_main_init[] = 
{
  PCS_BASE(LPC_SYSCTL_BASE),
  /* enable GPIO (bit 6) in SYSAHBCLKCTRL, Chip_GPIO_Init(LPC_GPIO_PORT); */
  PCS_SETB(6, 0x080/4),
  /* enable IOCON (bit 18) in SYSAHBCLKCTRL,Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON); */
  PCS_SETB(18, 0x080/4),
  /* enable switch matrix (bit 6), Chip_SWM_Init(); */
  PCS_SETB(7, 0x080/4),
  
  /* load switch matrix base */
  PCS_BASE(LPC_SWM_BASE),
  /* disable SWCLK at PIO_3, this might be enabled by boot sequence */
  PCS_SETB(2, 0x1c0/4),
  /* disable SWDIO at PIO_2, this might be enabled by boot sequence */
  PCS_SETB(3, 0x1c0/4) | PCS_END
};


/*=======================================================================*/
/* main procedure, called by "Reset_Handler" */

int __attribute__ ((noinline)) main(void)
{
  
  /* setup 30MHz for the LPC810 */
   
   /* oscillator controll registor, no change needed for int. RC osc. */
  //LPC_SYSCTL->SYSOSCCTRL = 0;		/* no bypass (bit 0), low freq range (bit 1), reset value is also 0 */
  
  //LPC_SYSCTL->SYSPLLCLKSEL = 0;			/* select PLL source, 0: IRC, 1: Sys osc, reset value is 0 */
  //LPC_SYSCTL->SYSPLLCLKUEN = 0;			/* confirm change by writing 0 and 1 to SYSPLLCLKUEN */
  //LPC_SYSCTL->SYSPLLCLKUEN = 1;
  
  LPC_SYSCTL->SYSPLLCTRL = 3 | (1 << 5);	/* 60 Mhz, m (bits 0..4) = 5, p (bits 5..6)= 1 (div by 2) */
  LPC_SYSCTL->SYSAHBCLKDIV = 2;			/* divide by 2 to get 30 MHz, however, at the moment we will get 6MHz */
  LPC_SYSCTL->PDRUNCFG &= ~(1UL<<7); 	/* power-up PLL */

  while (!(LPC_SYSCTL->SYSPLLSTAT & 1))
    ;	/* wait for PLL lock */
   
  LPC_SYSCTL->MAINCLKSEL = 3;				/* select PLL for main clock */
  LPC_SYSCTL->MAINCLKUEN = 0;				/* confirm change by writing 0 and 1 to MAINCLKUEN */
  LPC_SYSCTL->MAINCLKUEN = 1;	


  /* set systick and start systick interrupt */
  SysTick_Config(SYS_CORE_CLOCK/1000UL*(unsigned long)SYS_TICK_PERIOD_IN_MS);
 

  /* enable peripheral systems */ 
  pcs(pcs_main_init);
  
  /* turn on GPIO */
  //Chip_GPIO_Init(LPC_GPIO_PORT);
 
  /* disable SWCLK and SWDIO, after reset, boot code may activate this */
  //Chip_SWM_DisableFixedPin(2);
  //Chip_SWM_DisableFixedPin(3);
  
  /* turn on IOCON */
  //Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);
  /* turn on switch matrix */
  //Chip_SWM_Init();
  
  /* activate analog comperator */
  //Chip_ACMP_Init(LPC_CMP);

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

