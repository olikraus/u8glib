
#include "LPC11xx.h"

/*========================================================================*/
/* SystemInit */

uint32_t SystemCoreClock;

#define SYS_TICK_PERIOD_IN_MS 10

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

void spi_init(void) __attribute__((noinline));
void spi_init(void)
{
  uint32_t cpol = 1;
  uint32_t cpha = 0;
  
  LPC_SYSCON->PRESETCTRL |= 1<<0;	/* de-asserted reset SSP0 */
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	/* enable IOCON clock */
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<11;	/* enable SSP0 clock  */
  LPC_SYSCON->SSP0CLKDIV = 1;

  LPC_IOCON->SCK_LOC = 0;			/* SCK0 at PIO0_10 */
  LPC_IOCON->SWCLK_PIO0_10 = 2;		/* select SCK0 at PIO0_10 */
  LPC_IOCON->PIO0_9 = 1;			/* select MOSI0 at PIO0_9 */
  
  LPC_SSP0->CR1 = 0;								/* disable SPI, enable master mode */
  LPC_SSP0->CR0 = 7 | (cpol << 6) | (cpha <<7); 		/* 8 bit, SPI mode, SCR = 1 (prescale) */
  LPC_SSP0->CPSR = 12;			
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
/* main */

#define LED_GPIO	LPC_GPIO1
#define LED_PIN 8			


void main()
{
  volatile uint32_t i, cnt = 100000;
  LED_GPIO->DIR |= 1 << LED_PIN;	  
  
  spi_init();
  
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
