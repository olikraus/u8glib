
#include "LPC11xx.h"

uint32_t SystemCoreClock;

#define SYS_TICK_PERIOD_IN_MS 100

void SystemInit()
{
  /* SystemInit() is called by the startup code */
  /* according to system_LPC11xx.h it is expected, that the clock freq is set here */
  SystemCoreClock = F_CPU;
  
  /* SysTick is defined in core_cm0.h */
  SysTick->CTRL = 7;   /* enable, generate interrupt, do not divide by 2 */
  SysTick->LOAD = (SystemCoreClock/1000UL*(unsigned long)SYS_TICK_PERIOD_IN_MS) - 1;
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
  

void delay_micro_seconds(uint16_t us)
{
  uint32_t sys_ticks;
  uint32_t val;

#ifdef F_CPU 
  sys_ticks = F_CPU / 10000000UL * us;
#else  
  sys_ticks = SystemCoreClock;
  sys_ticks /=10000000UL;
  sys_ticks *= us;
#endif
  
  val = SysTick->VAL;
  sys_ticks+=val;
  if ( sys_ticks >= SysTick->LOAD )		/* warning: could be too close to the LOAD value */
  {
    /* correct target time */
    sys_ticks-=SysTick->LOAD;
    
    /* wait until overflow */
    while( val < SysTick->VAL )
      ;    
  }
    
  /* wait until target time */
  while( sys_ticks > SysTick->VAL )
    ;
  
}
  

void main()
{
	while (1)
	{
	  delay_micro_seconds(100);
	}
}
