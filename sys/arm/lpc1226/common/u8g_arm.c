/*
  
  u8g_arm.c
  

  u8g utility procedures for LPC122x

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

 
  The following delay procedures must be implemented for u8glib. This is done in this file:

  void u8g_Delay(uint16_t val)		Delay by "val" milliseconds
  void u8g_MicroDelay(void)		Delay be one microsecond
  void u8g_10MicroDelay(void)	Delay by 10 microseconds
  
  Additional requirements:
  
      SysTick must be enabled, but SysTick IRQ is not required. Any LOAD values are fine,
      it is prefered to have at least 1ms
      Example:
        SysTick->LOAD = (SystemCoreClock/1000UL*(unsigned long)SYS_TICK_PERIOD_IN_MS) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 7;   // enable, generate interrupt (SysTick_Handler), do not divide by 2
*/

#include "u8g_arm.h"


/*========================================================================*/
/* system clock setup for LPC122x */

uint32_t SystemCoreClock = 12000000;

/* activate PLL for the int. RC osc. Assumes the IRC is already running */
/* this procedure is not required for u8glib, but can be called from the init code */
 void init_system_clock(void)
 {
   
   /* do some simple startup tasks */
  LPC_SYSCON->SYSMEMREMAP = 2;  
  LPC_WWDT->MOD = 0;			/* disable watchdog */
  LPC_SYSCON->INTNMI = 0x03f;	/* disable NMI */
  
      
   /* setup 24MHz for the LPC122x (does not require additional wait states for the flash) */
   
   /* oscillator controll registor, no change needed for int. RC osc. */
  LPC_SYSCON->SYSOSCCTRL = 0;		/* no bypass (bit 0), low freq range (bit 1), reset value is also 0 */
   
  LPC_SYSCON->SYSPLLCLKSEL = 0;		/* select PLL source, 0: IRC, 1: Sys osc */
  LPC_SYSCON->SYSPLLCLKUEN = 0;	/* confirm change by writing 0 and 1 to SYSPLLCLKUEN */
  LPC_SYSCON->SYSPLLCLKUEN = 1;
  
  LPC_SYSCON->SYSPLLCTRL = 1 | (3 << 5);	/* 48 Mhz, m = 2, p = 4 */
  LPC_SYSCON->PDRUNCFG &= ~(1UL<<7); 	/* power-up PLL */

  while (!(LPC_SYSCON->SYSPLLSTAT & 1))
    ;	/* wait for PLL lock */
   
  LPC_SYSCON->MAINCLKSEL = 3;				/* select PLL for main clock */
  LPC_SYSCON->MAINCLKUEN = 0;				/* confirm change by writing 0 and 1 to MAINCLKUEN */
  LPC_SYSCON->MAINCLKUEN = 1;	

  LPC_SYSCON->SYSAHBCLKDIV = 1;			/* set AHB clock divider to 1 */
  
  SystemCoreClock = 24000000UL;
}

/*========================================================================*/
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

  sys_ticks = SystemCoreClock;
  sys_ticks /=1000000UL;
  sys_ticks *= us;
  delay_system_ticks(sys_ticks);  
}

/*========================================================================*/
/* generic gpio procedures (not required for u8glib) */

struct _lpc_pin_info_struct
{
  uint16_t offset;
  uint8_t iocon_gpio_value_no_pullup;
  uint8_t iocon_gpio_value_pullup;		/* identical to iocon_gpio_value_no_pullup if there is no pullup */
};
typedef struct _lpc_pin_info_struct lpc_pin_info_struct;

const lpc_pin_info_struct lpc11xx_pin_info[] = 
{
  { offsetof(LPC_IOCON_Type,PIO0_0), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_1), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_2), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_3), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_4), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_5), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_6), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_7), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_8), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_9), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_10), 			128, 128},	/* no pullup available */
  { offsetof(LPC_IOCON_Type,PIO0_11), 			128, 128},	/* no pullup available */
  { offsetof(LPC_IOCON_Type,PIO0_12), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,RESET_PIO0_13), 		128+16, 128+16},  /* reset pin, disallow GPIO here, always keep pullup */
  { offsetof(LPC_IOCON_Type,PIO0_14), 		128, 128+16}, 
  { offsetof(LPC_IOCON_Type,PIO0_15), 		128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_16), 		128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_17), 		128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_18), 		128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_19), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_20), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_21), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_22), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_23), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_24), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,SWDIO_PIO0_25), 		128+6, 128+16+6},
  { offsetof(LPC_IOCON_Type,SWCLK_PIO0_26), 		128+6, 128+16+6},
  { offsetof(LPC_IOCON_Type,PIO0_27), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_28), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO0_29), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,R_PIO0_30), 			128+1, 128+16+1},
  { offsetof(LPC_IOCON_Type,R_PIO0_31), 			128+1, 128+16+1},
  
  { offsetof(LPC_IOCON_Type,R_PIO1_0), 			128+1, 128+16+1},
  { offsetof(LPC_IOCON_Type,R_PIO1_1), 			128+1, 128+16+1},
  { offsetof(LPC_IOCON_Type,PIO1_2), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO1_3), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO1_4), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO1_5), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO1_6), 			128, 128+16},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
  { 0, 									0, 0},
    
  { offsetof(LPC_IOCON_Type,PIO2_0), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_1), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_2), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_3), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_4), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_5), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_6), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_7), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_8), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_9), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_10), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_11), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_12), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_13), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_14), 			128, 128+16},
  { offsetof(LPC_IOCON_Type,PIO2_15), 			128, 128+16},
  
  
};

LPC_GPIO_Type   *lpc11xx_gpio_base[4] = {LPC_GPIO0, LPC_GPIO1, LPC_GPIO2};


void set_gpio_mode(uint16_t pin, uint8_t is_output, uint8_t is_pullup)
{
  uint32_t value;
  LPC_GPIO_Type   *gpio;
  
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	/* enable IOCON clock */

   
  if ( is_pullup == 0 )
    value = lpc11xx_pin_info[pin].iocon_gpio_value_no_pullup;
  else
    value = lpc11xx_pin_info[pin].iocon_gpio_value_pullup;
  *(__IO uint32_t *)(((char *)LPC_IOCON)+(size_t)(lpc11xx_pin_info[pin].offset)) = value;
  
  gpio = lpc11xx_gpio_base[pin >> 5];
  
  if ( is_output == 0 )
    gpio->DIR &= ~( 1UL << (pin & 0x01f));
  else
    gpio->DIR |= ( 1UL << (pin & 0x01f));  
}

void set_gpio_level(uint16_t pin, uint8_t level)
{
  
  /* assumes that pins are not affected by MASK register */
  LPC_GPIO_Type  *gpio = lpc11xx_gpio_base[pin >> 5];
  pin &= 0x01f;
  if ( level != 0 )
  {
    gpio->SET = 1UL << (pin);
  }
  else
  {
    gpio->CLR = 1UL << (pin);
  }
}

uint8_t get_gpio_level(uint16_t pin)
{
  LPC_GPIO_Type  *gpio = lpc11xx_gpio_base[pin >> 5];
  pin &= 0x01f;
  if ( (gpio->PIN & (1<<(pin))) == 0 )
    return 0;
  return 1;  
}




/*========================================================================*/
/* 
  SPI 
  typedef struct {                             (@ 0x40040000) SSP Structure          
	  union{
    __IO uint32_t CR[2];						 (@ 0x40040000) Control Registers. 
    struct{
    __IO uint32_t CR0;                         (@ 0x40040000) Control Register 0. Selects the serial clock rate, bus type, and data size. 
    __IO uint32_t CR1;                         (@ 0x40040004) Control Register 1. Selects master/slave and other modes. 
    };
    };
    __IO uint32_t DR;                          (@ 0x40040008) Data Register. Writes fill the transmit FIFO, and reads empty the receive FIFO. 
    __I  uint32_t SR;                          (@ 0x4004000C) Status Register        
    __IO uint32_t CPSR;                        (@ 0x40040010) Clock Prescale Register 
    __IO uint32_t IMSC;                        (@ 0x40040014) Interrupt Mask Set and Clear Register 
    __I  uint32_t RIS;                         (@ 0x40040018) Raw Interrupt Status Register 
    __I  uint32_t MIS;                         (@ 0x4004001C) Masked Interrupt Status Register 
    __IO uint32_t ICR;                         (@ 0x40040020) SSPICR Interrupt Clear Register 
    __IO uint32_t DMACR;                       (@ 0x40040024) DMA Control Register   
  } LPC_SSP_Type;


  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	enable IOCON clock
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<11;	enable SSP clock
  LPC_SYSCON->SSPCLKDIV = 1;

  //LPC_IOCON->SCK_LOC = 0;			SCK0 at PIO0_10
  LPC_IOCON->PIO0_14 = 2;			select SCK at PIO0_14, no pullup
  LPC_IOCON->PIO0_17 = 2;			select MOSI at PIO0_17, no pullup
  
  LPC_SSP->CR1 = 0;								disable SPI, enable master mode
  LPC_SSP->CR0 = 7 | (CPOL << 6) | (CPHA <<7); 		8 bit, SPI mode, SCR = 1 (prescale)
  LPC_SSP->CPSR = 12;			
  LPC_SSP->CR1 = 2;								enable SPI, (enable master mode)

*/


/*
  setup spi0
  ns is the clock cycle time between 0 and 20000 ns
*/
void spi_init(uint32_t ns)
{
  uint32_t cpol = 1;
  uint32_t cpha = 1;
  uint32_t cpsr;

  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	/* enable IOCON clock */
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<11;	/* enable SSP0 clock  */
  LPC_SYSCON->SSPCLKDIV = 1;
  
  LPC_SYSCON->PRESETCTRL &= ~(1UL<<0);	/* reset SSP0 */
  
  LPC_IOCON->PIO0_14 = 2;			/* select SCK at PIO0_14 */
  LPC_IOCON->PIO0_17 = 2;			/* select MOSI at PIO0_17 */
  
  LPC_SYSCON->PRESETCTRL |= 1UL<<0;	/* de-asserted reset SSP0 */

  
  LPC_SSP->CR1 = 0;								/* disable SPI, enable master mode */
  LPC_SSP->CR0 = 7 | (cpol << 6) | (cpha <<7); 		/* 8 bit, SPI mode, SCR = 1 (prescale) */

  /*  
    calculate CPSR
    SystemCoreClock / CPSR = 1000000000 / ns 
    CPSR = SystemCoreClock * ns / 1000000000 
    CPSR = (SystemCoreClock/10000) * ns / 100000 
  */
  cpsr = SystemCoreClock;
  cpsr /= 10000UL;
  cpsr *= ns;
  cpsr += 100000UL  - 1UL;		/* round up */
  cpsr /= 100000UL;
  /* ensure that cpsr will be between 2 and 254 */
  if ( cpsr == 0 )
    cpsr = 1;
  cpsr++;
  cpsr &= 0x0feUL;
  LPC_SSP->CPSR = cpsr;
  LPC_SSP->CR1 = 2;								/* enable SPI, (enable master mode) */

  /*
  for(;;)
    spi_out(0x0f5);
  */
  /*
  set_gpio_mode(PIN(1,0), 1, 0);	
  for(;;)
  {
        set_gpio_level(PIN(1,0), 0);
        set_gpio_level(PIN(1,0), 0);
        set_gpio_level(PIN(1,0), 0);
        set_gpio_level(PIN(1,0), 1);
  }
  */

}

void spi_out(uint8_t data)
{
  while ( (LPC_SSP->SR & 2) == 0 )
    ;
  LPC_SSP->DR = data;
}

/*========================================================================*/
/*
  The following delay procedures must be implemented for u8glib

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
  delay_micro_seconds(1);
}

void u8g_10MicroDelay(void)
{
  delay_micro_seconds(10);
}




/*========================================================================*/
/* u8glib com procedure */

/* gps board */
/*
uint16_t u8g_pin_a0 = PIN(0,11);
uint16_t u8g_pin_cs = PIN(0,6);
uint16_t u8g_pin_rst = PIN(0,5);
*/

/* eval board */
uint16_t u8g_pin_a0 = PIN(1,1);
uint16_t u8g_pin_cs = PIN(1,2);
uint16_t u8g_pin_rst = PIN(1,0);


uint8_t u8g_com_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_STOP:
      break;
    
    case U8G_COM_MSG_INIT:

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
      else
      {
	spi_init(1200);
      }

      set_gpio_mode(u8g_pin_rst, 1, 0);		/* output, no pullup */
      set_gpio_mode(u8g_pin_cs, 1, 0);		/* output, no pullup */
      set_gpio_mode(u8g_pin_a0, 1, 0);		/* output, no pullup */

      u8g_MicroDelay();      
      break;
    
    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      u8g_10MicroDelay();
      set_gpio_level(u8g_pin_a0, arg_val);
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
	set_gpio_level(u8g_pin_cs, 1);
      }
      else
      {
        /* enable */
	set_gpio_level(u8g_pin_cs, 0);
      }
      u8g_MicroDelay();
      break;
      
    case U8G_COM_MSG_RESET:
      set_gpio_level(u8g_pin_rst, arg_val);
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

