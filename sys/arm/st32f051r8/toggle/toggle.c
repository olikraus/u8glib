
#include "stm32f0xx.h"

void SystemInit()
{    
    RCC->AHBENR |= 1<<17;	/* Enable Port A */
    RCC->AHBENR |= 1<<18;	/* Enable Port B */
    RCC->AHBENR |= 1<<19;	/* Enable Port C */
    RCC->AHBENR |= 1<<20;	/* Enable Port D */
    RCC->AHBENR |= 1<<22;	/* Enable Port F */
}

void __attribute__ ((interrupt)) SysTick_Handler(void)
{
}

void main(void)
{
  __disable_irq();

  
}
