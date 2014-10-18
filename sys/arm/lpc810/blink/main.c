

#include "chip.h"


#define SYS_CORE_CLOCK 12000000UL
#define SYS_TICK_PERIOD_IN_MS 50



/*=======================================================================*/
/* delay */

void delay_system_ticks(uint32_t sys_ticks);		/* from lpc81x_system.c */

/*
  Delay by the provided number of micro seconds.
  Limitation: "us" * System-Freq in MHz must now overflow in 32 bit.
  Values between 0 and 1.000.000 (1 second) are ok.
*/
void delay_micro_seconds(uint32_t us)
{
  uint32_t sys_ticks;

  sys_ticks = SYS_CORE_CLOCK / 1000000UL;
  sys_ticks *= us;
  delay_system_ticks(sys_ticks);  
}


/*=======================================================================*/
/* system procedures and sys tick master task */

volatile uint32_t sys_tick_irq_cnt=0;


void __attribute__ ((interrupt)) SysTick_Handler(void)
{
  sys_tick_irq_cnt++;
  
}


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
  Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 2);  
  
  for(;;)
  {
    Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 0, 2); 	
    delay_micro_seconds(500000UL);
    Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 2);    
    delay_micro_seconds(500000UL);
  }

  
  /* enter sleep mode: Reduce from 1.4mA to 0.8mA with 12MHz */  
  while (1)
  {
    SCB->SCR |= (1UL << SCB_SCR_SLEEPONEXIT_Pos);		/* enter sleep mode after interrupt */ 
    Chip_PMU_SleepState(LPC_PMU);						/* enter sleep mode now */
  }
}

