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
  if ( data & 1 )
    set_gpio_level(8, 1);
  else
    set_gpio_level(8, 0);

  if ( data & 2 )
    set_gpio_level(9, 1);
  else
    set_gpio_level(9, 0);

  if ( data & 4 )
    set_gpio_level(10, 1);
  else
    set_gpio_level(10, 0);

  if ( data & 8 )
    set_gpio_level(11, 1);
  else
    set_gpio_level(11, 0);
  
}

void led_show_adr(uint8_t adr)
{
  if ( adr & 1 )
    set_gpio_level(0x10, 1);
  else
    set_gpio_level(0x10, 0);

  if ( adr & 2 )
    set_gpio_level(0x11, 1);
  else
    set_gpio_level(0x11, 0);

  if ( adr & 4 )
    set_gpio_level(0x12, 1);
  else
    set_gpio_level(0x12, 0);

  if ( adr & 8 )
    set_gpio_level(0x13, 1);
  else
    set_gpio_level(0x13, 0);
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
  
  volatile unsigned queue_start;
  volatile unsigned queue_end;
  volatile unsigned queue_list[KEY_QUEUE_LEN];
  
  volatile unsigned is_stop_key;
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
  if ( get_gpio_level(0x18) == 0 )
    return KEY_UP;
  if ( get_gpio_level(0x19) == 0 )
    return KEY_DOWN;
  if ( get_gpio_level(0x01) == 0 )
    return KEY_RUN;
  if ( get_gpio_level(0x02) == 0 )
    return KEY_D3;
  if ( get_gpio_level(0x03) == 0 )
    return KEY_D2;
  if ( get_gpio_level(0x04) == 0 )
    return KEY_D1;
  if ( get_gpio_level(0x07) == 0 )
    return KEY_D0;
  return 0;
}

void key_add_to_queue(unsigned code)
{
  unsigned end;

  __disable_irq();
  if ( code == KEY_RUN )
    key_o.is_stop_key = 1;
    
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
      key_o.debounce_cnt = 0;
      if ( curr_raw_code != 0 )
      {
	key_o.last_raw_code = curr_raw_code;
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
    default:
      key_o.state = KEY_STATE_WAIT_FOR_BUTTON;
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
  uint8_t mem[COMP_MEM_SIZE];
};
typedef struct comp_struct comp_t;
comp_t comp_o;

void update_comp(void)
{
  led_show_data(comp_o.mem[comp_o.pc]);
  led_show_adr(comp_o.pc);
}

void inc_pc(void)
{
  comp_o.pc++;
  if ( comp_o.pc  >= COMP_MEM_SIZE )
    comp_o.pc = 0;
}



unsigned exec_cmd(void)
{
  unsigned key;
  switch(comp_o.mem[comp_o.pc])
  {    
    case 0:		/* stop */
      inc_pc();
      return 1;
    case 1:		/* 1 sekunde warten */
      u8g_Delay(500);
      break;
    case 2:		/* warte auf eine taste */      
      key = key_get_from_queue();
      if ( key == 0 )
	return 0;
      if ( key == KEY_RUN )
	return 1;
      break;
    case 3:		/* RGB LED aus */
      set_gpio_level(0x06, 0);		/* grün */
      set_gpio_level(0x14, 0);		/* blau */
      set_gpio_level(0x15, 0);		/* rot */
      break;
    case 4:		/* RGB LED grün */
      set_gpio_level(0x06, 1);		/* grün */
      set_gpio_level(0x14, 0);		/* blau */
      set_gpio_level(0x15, 0);		/* rot */
      break;
    case 5:		/* RGB LED blau */
      set_gpio_level(0x06, 0);		/* grün */
      set_gpio_level(0x14, 1);		/* blau */
      set_gpio_level(0x15, 0);		/* rot */
      break;
    case 6:		/* RGB LED rot */
      set_gpio_level(0x06, 0);		/* grün */
      set_gpio_level(0x14, 0);		/* blau */
      set_gpio_level(0x15, 1);		/* rot */
      break;
    case 7:		/* blinken */
      led_show_data(0);
      led_show_adr(0);
      u8g_Delay(100);
      led_show_data(15);
      led_show_adr(15);
      u8g_Delay(100);
      led_show_data(0);
      led_show_adr(0);
      u8g_Delay(100);
      led_show_data(15);
      led_show_adr(15);
      u8g_Delay(100);
      led_show_data(0);
      led_show_adr(0);
      break;
    case 8:		/* links rechts lauf */
      led_show_data(1);
      led_show_adr(0);
      u8g_Delay(100);
      led_show_data(2);
      led_show_adr(0);
      u8g_Delay(100);
      led_show_data(4);
      led_show_adr(0);
      u8g_Delay(100);
      led_show_data(8);
      led_show_adr(0);
      u8g_Delay(100);
      led_show_data(0);
      led_show_adr(1);
      u8g_Delay(100);
      led_show_data(0);
      led_show_adr(2);
      u8g_Delay(100);
      led_show_data(0);
      led_show_adr(4);
       u8g_Delay(100);
      led_show_data(0);
      led_show_adr(8);
       u8g_Delay(100);
      led_show_data(0);
      led_show_adr(0);
     break;
    case 9:		/* stop */
      return 1;
    case 10:		/* stop */
      return 1;
    case 11:		/* stop */
      return 1;
    case 12:		/* stop */
      return 1;
    case 13:		/* stop */
      return 1;
    case 14:		/* stop */
      return 1;
    case 15:		/* starte bei 0 */
      comp_o.pc = 0;
      return 0;
      
  }
  inc_pc();
  return 0;
}

unsigned execute(void)
{
  __disable_irq();
  key_o.queue_start = key_o.queue_end;		/* alle tasten löschen */
  __enable_irq();
  
  led_show_data(0);
  led_show_adr(0);
  
  key_o.is_stop_key = 0;
  while( exec_cmd() == 0 && key_o.is_stop_key == 0 )
    ;
  
  led_show_data(0);
  led_show_adr(0);
  __disable_irq();
  key_o.queue_start = key_o.queue_end;		/* alle tasten löschen */
  __enable_irq();
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
    case KEY_RUN:
      execute();
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
  uint8_t data = 1;

  /* tasten */
  set_gpio_mode(0x18, 0, 1);
  set_gpio_mode(0x19, 0, 1);
  set_gpio_mode(0x01, 0, 1);
  set_gpio_mode(0x02, 0, 1);
  set_gpio_mode(0x03, 0, 1);
  set_gpio_mode(0x04, 0, 1);
  set_gpio_mode(0x07, 0, 1);

  /* daten LEDs */
  set_gpio_mode(8, 1, 0);
  set_gpio_mode(9, 1, 0);
  set_gpio_mode(10, 1, 0);
  set_gpio_mode(11, 1, 0);

  /* adresse */
  set_gpio_mode(0x10, 1, 0);
  set_gpio_mode(0x11, 1, 0);
  set_gpio_mode(0x12, 1, 0);
  set_gpio_mode(0x13, 1, 0);

  /* RGB LED */
  set_gpio_mode(0x06, 1, 0);	/* grün */
  set_gpio_level(0x06, 0);		/* grün */
  
  set_gpio_mode(0x14, 1, 0);	/* blau */
  set_gpio_level(0x14, 0);		/* blau */

  set_gpio_mode(0x15, 1, 0);	/* rot */
  set_gpio_level(0x15, 0);		/* rot */

  SystemInit();
  
  for(;;)
    editor();
    
  led_show_data(data);
  
  for(;;)
  {
    if ( key_get_from_queue() != 0 )
    //if ( key_get_raw_code() != 0 )
    {
      data++;
      led_show_data(data);
    }
      
    /* refresh screen after some delay */
    u8g_Delay(10);
    
  }  
}

  