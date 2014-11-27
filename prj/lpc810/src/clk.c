

#include "chip.h"
#include "clk.h"
#include "sys.h"

clk_t clk_o; 


static const time_data_t time_data_max = { { 59, 59, 23, 7 } };



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
  } while ( i < 15 );
  clk_o.pcf8563[i] = i2c_read_byte(1);
  
  i2c_stop();
}

/*
02h VL_seconds VL SECONDS (0 to 59)
03h Minutes x MINUTES (0 to 59)
04h Hours x x HOURS (0 to 23)
05h Days x x DAYS (1 to 31)
06h Weekdays x x x x
07h Century_months C x x MONTHS (1 to 12)
08h Years YEARS (0 to 99)
*/

static void clk_pcf8563_to_currrent_time(void)
{
  __disable_irq();
  clk_o.current_time.data[0] = clk_o.pcf8563[2] & 127;
  clk_o.current_time.data[1] = clk_o.pcf8563[3] & 127;
  clk_o.current_time.data[2] = clk_o.pcf8563[4] & 63;
  clk_o.current_time.data[3] = clk_o.pcf8563[6] & 7;
  __enable_irq();
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

/*=======================================================================*/

void clk_init(void)
{
  clk_read_pcf_pcf8563_raw_data();
  clk_pcf8563_to_currrent_time();
}

