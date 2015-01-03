/*

  main.c
  
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
#include "clk.h"
#include "menu.h"



/*=======================================================================*/


/*=======================================================================*/


/*=================================================*/



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
  PCS_SETB(3, 0x1c0/4),

  PCS_BASE(LPC_IOCON_BASE),
  
  /* Chip_IOCON_PinSetMode(LPC_IOCON,IOCON_PIO0,PIN_MODE_INACTIVE); */
  /* PIO1 is at index 0x0B, Clear bit 3, set bit 4 for pullup */
  PCS_CLRB(3, 0x0B),
  PCS_SETB(4, 0x0B),
  /* disable open drain */
  PCS_CLRB(10, 0x0B),

    /* PIO4 is at index 0x04, Clear bit 3, set bit 4 for pullup */
  PCS_CLRB(3, 0x04),
  PCS_SETB(4, 0x04),
  /* disable open drain */
  PCS_CLRB(10, 0x04),

  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
//Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 1);
  PCS_CLRB(1, 0x000/4),
//Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 4);
  PCS_CLRB(4, 0x000/4) | PCS_END
  
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
 /*
  4:0 6:5
31:7
Description Reset
value
4:0	MSEL 	Feedback divider value. The division value M is the programmed MSEL value + 1.
			00000: Division ratio M = 1
			to
			11111: Division ratio M = 32 0
6:5	PSEL 	Post divider ratio P. The division ratio is 2 X P
			Value
			0x0 P = 1
			0x1 P = 2
			0x2 P = 4
			0x3 P = 8
			
Fout = Fin * M = Fin * MSEL+1
*/  
  
  
  LPC_SYSCTL->SYSPLLCTRL = 4 | (1 << 5);	/* 60 Mhz, m (bits 0..4) = 4, p (bits 5..6)= 1 (div by 2) */
  //LPC_SYSCTL->SYSPLLCTRL = 3 | (1 << 5);	/* 60 Mhz, m (bits 0..4) = 4, p (bits 5..6)= 1 (div by 2) */
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

  clk_init();

  oled_init();
  
  menu();
  
  /*
  {
    for(;;)
    {    
      pcs(pcs_led_high);
      delay_micro_seconds(100000UL);
      pcs(pcs_led_low);
      delay_micro_seconds(100000UL);
    }
    
  }
  */
  
  /* enter sleep mode: Reduce from 1.4mA to 0.8mA with 12MHz */  
  while (1)
  {
    SCB->SCR |= (1UL << SCB_SCR_SLEEPONEXIT_Pos);		/* enter sleep mode after interrupt */ 
    Chip_PMU_SleepState(LPC_PMU);						/* enter sleep mode now */
  }
}

