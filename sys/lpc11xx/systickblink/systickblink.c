
#include "LPC11xx.h"

uint32_t SystemCoreClock;

#define SYS_TICK_PERIOD_IN_MS 100

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

#define LED_GPIO	LPC_GPIO1
#define LED_PIN 8			


volatile uint32_t sys_tick_irq_cnt=0;

void __attribute__ ((interrupt)) SysTick_Handler(void)
{
  sys_tick_irq_cnt++;
  LED_GPIO->DIR |= 1 << LED_PIN;	
  if ( sys_tick_irq_cnt & 1 )
    LED_GPIO->DATA |= 1 << LED_PIN;
  else
    LED_GPIO->DATA &= ~(1 << LED_PIN);
}
  
void main()
{
	while (1)
	{
	}
}
