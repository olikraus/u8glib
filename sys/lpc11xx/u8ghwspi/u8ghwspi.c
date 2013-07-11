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

#include "LPC11xx.h"
#include "u8g.h"

#define SYS_TICK_PERIOD_IN_MS 10


/*========================================================================*/
/* SystemInit */

/* activate PLL for the int. RC osc. Assumes the IRC is already running */
 void lpc11xx_set_irc_48mhz(void)
 {
   /* oscillator controll registor, no change needed for int. RC osc. */
   LPC_SYSCON->SYSOSCCTRL = 0;		/* no bypass (bit 0), low freq range (bit 1), reset value is also 0 */
   
  LPC_SYSCON->SYSPLLCLKSEL = 0;		/* select PLL source, 0: IRC, 1: Sys osc */
  LPC_SYSCON->SYSPLLCLKUEN = 0;	/* confirm change by writing 0 and 1 to SYSPLLCLKUEN */
  LPC_SYSCON->SYSPLLCLKUEN = 1;
  
  LPC_SYSCON->SYSPLLCTRL = 3 || (1 << 5);	/* 48 Mhz, m = 4, p = 2 */
  LPC_SYSCON->PDRUNCFG &= ~(1<<7); 	/* power-up PLL */

  while (!(LPC_SYSCON->SYSPLLSTAT & 1))
    ;	/* wait for PLL lock */
   
  LPC_SYSCON->MAINCLKSEL = 3;				/* select PLL for main clock */
  LPC_SYSCON->MAINCLKUEN = 0;				/* confirm change by writing 0 and 1 to MAINCLKUEN */
  LPC_SYSCON->MAINCLKUEN = 1;	

  LPC_SYSCON->SYSAHBCLKDIV = 1;			/* set AHB clock divider to 1 */
}



uint32_t SystemCoreClock;

void SystemInit()
{
  /* SystemInit() is called by the startup code */
  /* according to system_LPC11xx.h it is expected, that the clock freq is set here */
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


/*============================================================*/
/* Generic ARM delay procedure, based on the system timer (SysTick) */

/*
  Delay by the provided number of system ticks.
  The delay must be smaller than the RELOAD value.
  This delay has an imprecision of about +/- 20 system ticks.   
*/
static void _delay_system_ticks_sub(uint32_t sys_ticks)
{
  uint32_t start_val, end_val, curr_val;
  uint32_t load;
  
  start_val = SysTick->VAL;
  start_val &= 0x0ffffffUL;
  end_val = start_val;
  
  if ( end_val < sys_ticks )
  {
    /* check, if the operation after this if clause would lead to a negative result */
    /* if this would be the case, then add the reload value first */
    load = SysTick->LOAD;
    load &= 0x0ffffffUL;
    end_val += load;
  }
  /* counter goes towards zero, so end_val is below start value */
  end_val -= sys_ticks;		
  
  
  /* wait until interval is left */
  if ( start_val >= end_val )
  {
    for(;;)
    {
      curr_val = SysTick->VAL;
      curr_val &= 0x0ffffffUL;
      if ( curr_val <= end_val )
	break;
      if ( curr_val > start_val )
	break;
    }
  }
  else
  {
    for(;;)
    {
      curr_val = SysTick->VAL;
      curr_val &= 0x0ffffffUL;
      if ( curr_val <= end_val && curr_val > start_val )
	break;
    }
  }
}

/*
  Delay by the provided number of system ticks.
  Any values between 0 and 0x0ffffffff are allowed.
*/
void delay_system_ticks(uint32_t sys_ticks)
{
  uint32_t load4;
  load4 = SysTick->LOAD;
  load4 &= 0x0ffffffUL;
  load4 >>= 2;
  
  while ( sys_ticks > load4 )
  {
    sys_ticks -= load4;
    _delay_system_ticks_sub(load4);
  }
  _delay_system_ticks_sub(sys_ticks);
}

/*
  Delay by the provided number of micro seconds.
  Limitation: "us" * System-Freq in MHz must now overflow in 32 bit.
  Values between 0 and 1.000.000 (1 second) are ok.
*/
void delay_micro_seconds(uint32_t us)
{
  uint32_t sys_ticks;

#ifdef F_CPU 
  sys_ticks = F_CPU / 1000000UL * us;
#else  
  sys_ticks = SystemCoreClock;
  sys_ticks /=1000000UL;
  sys_ticks *= us;
#endif
  delay_system_ticks(sys_ticks);  
}


/*========================================================================*/
/* 
  SPI 
    typedef struct
    {
      __IO uint32_t CR0;                    Offset: 0x000 Control Register 0 (R/W) 
      __IO uint32_t CR1;                     Offset: 0x004 Control Register 1 (R/W) 
      __IO uint32_t DR;                      Offset: 0x008 Data Register (R/W) 
      __I  uint32_t SR;                      Offset: 0x00C Status Registe (R/ )		Bit 0: Fifo empty, Bit 1: Fifo not full 
      __IO uint32_t CPSR;                    Offset: 0x010 Clock Prescale Register (R/W) (2..254)
      __IO uint32_t IMSC;                    Offset: 0x014 Interrupt Mask Set and Clear Register (R/W) 
      __IO uint32_t RIS;                     Offset: 0x018 Raw Interrupt Status Register (R/W) 
      __IO uint32_t MIS;                     Offset: 0x01C Masked Interrupt Status Register (R/W) 
      __IO uint32_t ICR;                     Offset: 0x020 SSPICR Interrupt Clear Register (R/W) 
    } LPC_SSP_TypeDef;

  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	enable IOCON clock
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<11;	enable SSP0 clock
  LPC_SYSCON->SSP0CLKDIV = 1;

  LPC_IOCON->SCK_LOC = 0;			SCK0 at PIO0_10
  LPC_IOCON->SWCLK_PIO0_10 = 2;	select SCK0 at PIO0_10
  LPC_IOCON->PIO0_9 = 1;			select MOSI0 at PIO0_9
  
  LPC_SSP0->CR1 = 0;								disable SPI, enable master mode
  LPC_SSP0->CR0 = 7 | (CPOL << 6) | (CPHA <<7); 		8 bit, SPI mode, SCR = 1 (prescale)
  LPC_SSP0->CPSR = 12;			
  LPC_SSP0->CR1 = 2;								enable SPI, (enable master mode)

*/


/*
  setup spi0
  ns is the clock cycle time between 0 and 20000
*/
void spi_init(uint32_t ns) __attribute__((noinline));
void spi_init(uint32_t ns)
{
  uint32_t cpol = 1;
  uint32_t cpha = 1;
  uint32_t cpsr;
  
  LPC_SYSCON->PRESETCTRL |= 1<<0;	/* de-asserted reset SSP0 */
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	/* enable IOCON clock */
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<11;	/* enable SSP0 clock  */
  LPC_SYSCON->SSP0CLKDIV = 1;

  LPC_IOCON->SCK_LOC = 0;			/* SCK0 at PIO0_10 */
  LPC_IOCON->SWCLK_PIO0_10 = 2;		/* select SCK0 at PIO0_10 */
  LPC_IOCON->PIO0_9 = 1;			/* select MOSI0 at PIO0_9 */
  
  LPC_SSP0->CR1 = 0;								/* disable SPI, enable master mode */
  LPC_SSP0->CR0 = 7 | (cpol << 6) | (cpha <<7); 		/* 8 bit, SPI mode, SCR = 1 (prescale) */
  LPC_SSP0->CR0 = 7 | (cpol << 6) | (cpha <<7); 		/* 8 bit, SPI mode, SCR = 1 (prescale) */

  /*  
    calculate CPSR
    SystemCoreClock / CPSR = 1000000000 / ns 
    CPSR = SystemCoreClock * ns / 1000000000 
    CPSR = (SystemCoreClock/10000) * ns / 100000 
  */
  cpsr = SystemCoreClock;
  cpsr /= 10000UL;
  cpsr *= ns;
  cpsr += 100000UL / 2UL;		/* round up */
  cpsr /= 100000UL;
  /* ensure that cpsr will be between 2 and 254 */
  if ( cpsr == 0 )
    cpsr = 1;
  cpsr++;
  cpsr &= 0x0feUL;
  
  LPC_SSP0->CPSR = cpsr;
  LPC_SSP0->CR1 = 2;								/* enable SPI, (enable master mode) */
}

void spi_out(uint8_t data)  __attribute__((noinline));
void spi_out(uint8_t data)
{
  while ( (LPC_SSP0->SR & 2) == 0 )
    ;
  LPC_SSP0->DR = data;
}




/*========================================================================*/
/*
  The following delay procedures must be implemented

  void u8g_Delay(uint16_t val)		Delay by "val" milliseconds
  void u8g_MicroDelay(void)		Delay be one microsecond
  void u8g_10MicroDelay(void)	Delay by 10 microseconds

*/

void u8g_Delay(uint16_t val)
{
  delay_micro_seconds(1000UL*(uint32_t)val);
}

void u8g_MicroDelay(void)
{
#ifdef F_CPU 
  _delay_system_ticks_sub(F_CPU / 1000000UL);
#else
  delay_micro_seconds(1);
#endif
}

void u8g_10MicroDelay(void)
{
#ifdef F_CPU 
  _delay_system_ticks_sub(F_CPU / 100000UL);
#else
  delay_micro_seconds(10);
#endif
}



/*========================================================================*/
/* u8glib com procedure */

#define A0_GPIO	LPC_GPIO1
#define A0_PIN 	1

#define CS_GPIO	LPC_GPIO1
#define CS_PIN 	2

#define RST_GPIO	LPC_GPIO1
#define RST_PIN 	0


uint8_t u8g_com_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_STOP:
      break;
    
    case U8G_COM_MSG_INIT:

      LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	/* enable IOCON clock */

      LPC_IOCON->R_PIO1_0 = 1;			/* select GPIO mode */
      LPC_IOCON->R_PIO1_1 = 1;			/* select GPIO mode */
      LPC_IOCON->R_PIO1_2 = 1;			/* select GPIO mode */
        
      A0_GPIO->DIR |= 1 << A0_PIN;
      CS_GPIO->DIR |= 1 << CS_PIN;
      RST_GPIO->DIR |= 1 << RST_PIN;
      
      if ( arg_val <= U8G_SPI_CLK_CYCLE_50NS )
      {
	spi_init(50);
      }
      else if ( arg_val <= U8G_SPI_CLK_CYCLE_300NS )
      {
	spi_init(300);
      }
      else if ( arg_val <= U8G_SPI_CLK_CYCLE_400NS )
      {
	spi_init(400);
      }
      else /* 1200ns */
      {
	spi_init(1200);
      }
      
      u8g_MicroDelay();      
      break;
    
    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      if ( arg_val != 0 )
	  A0_GPIO->DATA |= 1 << A0_PIN;
      else
	  A0_GPIO->DATA &= ~(1 << A0_PIN);
      u8g_MicroDelay();
      break;

    case U8G_COM_MSG_CHIP_SELECT:
#if defined(CS_GPIO)
      if ( arg_val == 0 )
      {
        /* disable */
	u8g_MicroDelay();		/* this delay is required to avoid that the display is switched off too early --> DOGS102 with DUE */
	CS_GPIO->DATA |= 1 << CS_PIN;
	u8g_MicroDelay();
      }
      else
      {
        /* enable */
	CS_GPIO->DATA &= ~(1 << CS_PIN);
	u8g_MicroDelay();
      }
#endif
      break;
      
    case U8G_COM_MSG_RESET:
#if defined(RST_GPIO)
      if ( arg_val != 0 )
	  RST_GPIO->DATA |= 1 << RST_PIN;
      else
	  RST_GPIO->DATA &= ~(1 << RST_PIN);
#endif
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


void draw(void)
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
    u8g_SetFont(&u8g, u8g_font_unifont);
    u8g_DrawStr(&u8g,  0, 22, "Hello World!");
  }
}

void main()
{
  volatile uint32_t i, cnt = 100000;
  LED_GPIO->DIR |= 1 << LED_PIN;	  

  A0_GPIO->DIR |= 1 << A0_PIN;
  CS_GPIO->DIR |= 1 << CS_PIN;
  RST_GPIO->DIR |= 1 << RST_PIN;
  
  spi_init(50);
  
  u8g_InitComFn(&u8g, &u8g_dev_ssd1351_128x128_332_hw_spi, u8g_com_hw_spi_fn);
  //u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_bw_hw_spi, u8g_com_hw_spi_fn);
  
  for(;;)
  {
    u8g_FirstPage(&u8g);
    do
    {
      draw();
    } while ( u8g_NextPage(&u8g) );
    LED_GPIO->DATA |= 1 << LED_PIN;
    //A0_GPIO->DATA |= 1 << A0_PIN;
    u8g_Delay(100);
    LED_GPIO->DATA &= ~(1 << LED_PIN);
    //A0_GPIO->DATA &= ~(1 << A0_PIN);
    u8g_Delay(100);
  }
  
  while (1)
  {
    for( i = 0; i < cnt; i++ ) 
      spi_out(0x0a0);
    LED_GPIO->DATA |= 1 << LED_PIN;
    for( i = 0; i < cnt; i++ )
      spi_out(0x0a0);
    LED_GPIO->DATA &= ~(1 << LED_PIN);
  }
}
