
#include "LPC11xx.h"


/*============================================================*/
/* Generic ARM setup code for system clock and system timer */

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

/*============================================================*/
/* u8glib interface for __arm___ */

/*
  The following procedures must be implemented

  void u8g_Delay(uint16_t val)		Delay by "val" milliseconds
  void u8g_MicroDelay(void)		Delay be one microsecond
  void u8g_10MicroDelay(void)	Delay by 10 microseconds

  uint8_t u8g_Pin(uint8_t port, uint8_t bitpos)						Convert to internal number: AVR: port*8+bitpos, ARM: port*16+bitpos
  void u8g_SetPinOutput(uint8_t internal_pin_number)
  void u8g_SetPinInput(uint8_t internal_pin_number)
  void u8g_SetPinLevel(uint8_t internal_pin_number, uint8_t level)
  uint8_t u8g_GetPinLevel(uint8_t internal_pin_number)
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

uint8_t u8g_Pin(uint8_t port, uint8_t bitpos)
{
  
}


#define LED_GPIO	LPC_GPIO1
#define LED_PIN 8			

  
void main()
{
  uint32_t us = 100000;		/* 0.1 s */
  LED_GPIO->DIR |= 1 << LED_PIN;	  
  
  while (1)
  {
    delay_micro_seconds(us);
    LED_GPIO->DATA |= 1 << LED_PIN;
    delay_micro_seconds(us);
    LED_GPIO->DATA &= ~(1 << LED_PIN);
  }
}
