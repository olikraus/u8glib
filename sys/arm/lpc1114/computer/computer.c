/*
  
  show_port.c
  
  >>> PLEASE UNCOMMENT DISPLAY TYPE IN THE MAIN PROCEDURE <<<
  
  ARM U8glib Example

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

#include "u8g_arm.h"

/*========================================================================*/
/* led output */

void led_show_data(uint8_t data)
{
}

void led_show_adr(uint8_t adr)
{
}



/*========================================================================*/
/* key handling */

#define KEY_STATE_WAIT_FOR_BUTTON 0
#define KEY_STATE_WAIT_FOR_DEBOUNCE 1
#define KEY_STATE_WAIT_INITIAL_KEY_DELAY 2
#define KEY_STATE_AUTO_REPEAT 3

#define KEY_DEBOUNCE_TICKS 3
#define KEY_INITAL_TICKS 50
#define KEY_REPEAT_TICKS 15

#define KEY_QUEUE_LEN 6

struct key_struct
{
  unsigned last_raw_code;
  unsigned state;
  unsigned debounce_cnt;
  unsigned initial_cnt;
  unsigned repeat_cnt;
  
  unsigned queue_start;
  unsigned queue_end;
  unsigned queue_list[KEY_QUEUE_LEN];
};

typedef struct key_struct key_t;
key_t key_o;

#define KEY_D0 1
#define KEY_D1 2
#define KEY_D2 3
#define KEY_D3 4

#define KEY_UP 5 
#define KEY_DOWN 6
#define KEY_RUN 7


/*
  return 0 if no button is pressed
  return 1 for button at ...
  return 2 for button at ...
*/
static unsigned key_get_raw_code(void)
{
  return 0;
}

void key_add_to_queue(unsigned code)
{
  unsigned end;

  __disable_irq();
  
  end = key_o.queue_end;
  end++;
  if ( end >= KEY_QUEUE_LEN )
    end = 0;
  if ( key_o.queue_start == end )
    return;	/* queue is full */
  key_o.queue_list[key_o.queue_end] = code;
  key_o.queue_end = end;
  
  __enable_irq();
}


unsigned key_get_from_queue(void)
{
  unsigned code;
  __disable_irq();
  
  if ( key_o.queue_start == key_o.queue_end )
  {
    code = 0;
  }
  else
  {
    code = key_o.queue_list[key_o.queue_start];
    key_o.queue_start++;
    if ( key_o.queue_start >= KEY_QUEUE_LEN )
      key_o.queue_start = 0;
  }
  
  __enable_irq();
  return code;
}


void key_irq(void)
{
  unsigned curr_raw_code = key_get_raw_code();
  
  switch(key_o.state)
  {
    case KEY_STATE_WAIT_FOR_BUTTON:
      if ( curr_raw_code != 0 )
      {
	key_o.last_raw_code = curr_raw_code;
	key_o.debounce_cnt = 0;
	key_o.state = KEY_STATE_WAIT_FOR_DEBOUNCE;
      }
      break;
    case KEY_STATE_WAIT_FOR_DEBOUNCE:
      if ( key_o.last_raw_code != curr_raw_code )
      {
	key_o.state = KEY_STATE_WAIT_FOR_BUTTON;
      }
      else
      {
	key_o.debounce_cnt++;
	if ( key_o.debounce_cnt >= KEY_DEBOUNCE_TICKS )
	{
	  key_o.initial_cnt = 0;
	  key_o.state = KEY_STATE_WAIT_INITIAL_KEY_DELAY;	  
	}
      }
      break;
    case KEY_STATE_WAIT_INITIAL_KEY_DELAY:
      if ( key_o.last_raw_code != curr_raw_code )
      {
	if ( curr_raw_code == 0 )
	{
	  key_add_to_queue(key_o.last_raw_code);
	}
	key_o.state = KEY_STATE_WAIT_FOR_BUTTON;
      }
      else
      {
	key_o.initial_cnt++;
	if ( key_o.initial_cnt >= KEY_INITAL_TICKS )
	{
	  key_add_to_queue(key_o.last_raw_code);
	  key_o.repeat_cnt = 0;
	  key_o.state = KEY_STATE_AUTO_REPEAT;
	}
      }
      break;
    case KEY_STATE_AUTO_REPEAT:    
      if ( key_o.last_raw_code != curr_raw_code )
      {
	key_o.state = KEY_STATE_WAIT_FOR_BUTTON;
      }
      else
      {
	key_o.repeat_cnt++;
	if ( key_o.repeat_cnt >=  KEY_REPEAT_TICKS )
	{
	  key_add_to_queue(key_o.last_raw_code);
	  key_o.repeat_cnt = 0;
	}	
      }
      break;
  }
}


/*========================================================================*/
/* SystemInit & SysTick Interrupt */

#define SYS_TICK_PERIOD_IN_MS 10

void SystemInit()
{    
  init_system_clock();		/* SystemCoreClock will be set here */
  
  /* SysTick is defined in core_cm0.h */
  SysTick->LOAD = (SystemCoreClock/1000UL*(unsigned long)SYS_TICK_PERIOD_IN_MS) - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = 7;   /* enable, generate interrupt (SysTick_Handler), do not divide by 2 */
}

void __attribute__ ((interrupt)) SysTick_Handler(void)
{
  key_irq();
}

/*========================================================================*/
/* main */


#define COMP_MEM_SIZE 16
struct comp_struct
{
  unsigned pc;
  uint8_t mem[COMP_MEM_SIZE]
};
typedef struct comp_struct comp_t;
comp_t comp_o;

void update_comp(void)
{
  led_show_data(comp_o.mem[comp_o.pc]);
  led_show_adr(comp_o.pc);
}


void editor(void)
{
  update_comp();
  switch(key_get_from_queue())
  {
    case KEY_UP:
      comp_o.pc++;
      if ( comp_o.pc  >= COMP_MEM_SIZE )
	comp_o.pc = 0;
      update_comp();
      break;
    case KEY_DOWN:
      if ( comp_o.pc  == 0 )
	comp_o.pc = COMP_MEM_SIZE-1;
      else
	comp_o.pc--;
      update_comp();
      break;
    case KEY_D0:
      comp_o.mem[comp_o.pc] ^= 1;
      update_comp();
      break;
    case KEY_D1:
      comp_o.mem[comp_o.pc] ^= 2;
      update_comp();
      break;
    case KEY_D2:
      comp_o.mem[comp_o.pc] ^= 4;
      update_comp();
      break;
    case KEY_D3:
      comp_o.mem[comp_o.pc] ^= 8;
      update_comp();
      break;    
  }
}




/*
void set_gpio_mode(uint16_t pin, uint8_t is_output, uint8_t is_pullup)
void set_gpio_level(uint16_t pin, uint8_t level)
uint8_t get_gpio_level(uint16_t pin)
*/

void main()
{
  
  
  set_gpio_mode(0x01, 0, 1);
  set_gpio_mode(0x08, 1, 0);
  for(;;)
  {
      
    if ( get_gpio_level(0x01) == 0 )
      set_gpio_level(0x08, 0);
    else
      set_gpio_level(0x08, 1);
    /* refresh screen after some delay */
    u8g_Delay(100);
    
  }  
}

  