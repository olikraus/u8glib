

#ifndef _CLK_H
#define _CLK_H
#include "stdint.h"

struct time_data_struct
{
  /*
    0: seconds
    1: minutes
    2: hours
    3: weekdays
  */
  volatile uint8_t data[4];
};
typedef struct time_data_struct time_data_t;

struct clk_struct
{
  volatile unsigned is_update;	/* will be set to 1 after one second by the IRQ */
  time_data_t current_time;
  volatile uint8_t pcf8563[16];		/* a copy of the registers of the PCF8563 */
  //volatile uint32_t cnt[4];
};
typedef struct clk_struct clk_t;

extern clk_t clk_o;

void clk_write_current_time(void);


void clk_init(void);
void clk_inc(clk_t *clk);
void clk_irq(void);


#endif

