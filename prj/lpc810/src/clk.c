

#include "clk.h"

clk_t clk_o; 


static const time_data_t time_data_max = { 59, 59, 23, 7 };


/*=======================================================================*/

void clk_init(void)
{
}


/*=======================================================================*/

void clk_read_pcf_pcf8563_raw_data(void)
{
  unsigned i=0;

  i2c_start();
  i2c_write_byte(0xa2);		// PCF8563 address and 0 (write) for RWn bit    
  i2c_write_byte(0);			// set index 0    
  i2c_start();				// restart
  i2c_write_byte(0xa3);		// PCF8563 address and 1 (read) for RWn bit    
  
  do
  {
    clk_o.pcf8563[i] = i2c_read_byte(0);
    i++;
  } while ( i < 15 )
  clk_o.pcf8563[i] = i2c_read_byte(1);
  
  i2c_stop();
  
}









/*=======================================================================*/

unsigned clk_inc_idx(clk_t *clk, unsigned idx)
{
  uint32_t cnt = clk->current_time.data[idx];
  cnt++;
  if ( cnt > time_data_max.data[idx] )
  {
    clk->current_time.data[idx] = 0;
    return 1;
  }
  clk->current_time.data[idx] = cnt;
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
    clk_o.is_update = 1;
    clk_inc(&clk_o);
  }
}

