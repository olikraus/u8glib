

#ifndef _CLK_H
#define _CLK_H
#include "stdint.h"


struct clk_struct
{
  volatile uint32_t cnt[4];
  volatile uint32_t max[4];
};
typedef struct clk_struct clk_t;

extern clk_t clk_current_time;


void clk_init(clk_t *clk);
void clk_inc(clk_t *clk);
void clk_irq(void);


#endif

