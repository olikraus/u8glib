
#include "LPC11xx.h"

uint32_t SystemCoreClock;


void SystemInit()
{
  /* SystemInit() is called by the startup code */
  /* according to system_LPC11xx.h it is expected, that the clock freq is set here */
  SystemCoreClock = F_CPU;  
}


#define LED_GPIO	LPC_GPIO1
#define LED_PIN 8			


void main()
{
	volatile uint32_t count, count_max = 100000;
	LED_GPIO->DIR |= 1 << LED_PIN;		
	LED_GPIO->DATA |= 1 << LED_PIN;

  
	while (1)
	{
		for (count = 0; count < count_max; count++);	// delay
		LED_GPIO->DATA |= 1 << LED_PIN;
		for (count = 0; count < count_max; count++);	// delay
		LED_GPIO->DATA &= ~(1 << LED_PIN);
	}
}
