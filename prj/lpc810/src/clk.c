

#include "clk.h"

clk_t clk_current_time; 

void clk_init(clk_t *clk)
{
  clk->cnt[0] = 0;
  clk->cnt[1] = 0;
  clk->cnt[2] = 0;
  clk->cnt[3] = 0;
  clk->max[0] = 59;
  clk->max[1] = 59;
  clk->max[2] = 23;
  clk->max[3] = 7;
}


unsigned clk_inc_idx(clk_t *clk, unsigned idx)
{
  uint32_t cnt = clk->cnt[idx];
  cnt++;
  if ( cnt > clk->max[idx] )
  {
    clk->cnt[idx] = 0;
    return 1;
  }
  clk->cnt[idx] = cnt;
  return 0;
}

void clk_inc(clk_t *clk)
{
  unsigned i = 0;
  for( i = 0; i < 4; i++ )
  {
    if ( clk_inc_idx(clk, i) == 0 )
      break;
  }
}

void clk_irq(void)
{
  static unsigned t;
  t++;
  /* there are about 100 calls per second */
  if ( t >= 100 )
  {
    t = 0;
    clk_current_time.is_update = 1;
    clk_inc(&clk_current_time);
  }
}

