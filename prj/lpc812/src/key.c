

#include <stdint.h>
#include "chip.h"
#include "sys.h"
#include "port.h"
#include "clk.h"
#include "key.h"


/* port configuration for the keys is done in the main procedure / main setup */


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

const uint16_t pcs_get_key_01[] = 
{  
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  PCS_GETB(1, 0x100/4) | PCS_END
};

const uint16_t pcs_get_key_04[] = 
{  
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  PCS_GETB(4, 0x100/4) | PCS_END
};

/*
  return 0 if no button is pressed
  return 1 for button at port 0_1
  return 2 for button at port 0_4
*/
static unsigned key_get_raw_code(void)
{
  if ( pcs(pcs_get_key_01) == 0 )
    return 1;
  if ( pcs(pcs_get_key_04) == 0 )
    return 2;
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

/*
void key_irq(void)
{
  unsigned curr_raw_code = key_get_raw_code();
  
  if (key_o.state == KEY_STATE_WAIT_FOR_BUTTON)
  {
      if ( curr_raw_code != 0 )
      {
	key_o.last_raw_code = curr_raw_code;
	key_o.debounce_cnt = 0;
	key_o.state = KEY_STATE_WAIT_FOR_DEBOUNCE;
      }
  }
  else if ( key_o.state == KEY_STATE_WAIT_FOR_DEBOUNCE )
  {
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
  }
    
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
*/