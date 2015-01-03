

/*
  30 MHz
  
*/

#include "chip.h"

#define HALF_BITS 6

struct dac_struct
{
  
};
typedef struct dac_struct;



/* only an even number of bits is allowed */
void dac_init(uint16_t bits)
{
  uint16_t limit = (1<<(bits-1))-1;
  
  /* two independent 16 bit counter, both have autolimit */
  LPC_SCT->CONFIG = (1<<17)|(1<<18);
  /* halt L&H counter, set prescalar to 1(max freq) */
  LPC_SCT->CTRL_L = (1<<2);
  LPC_SCT->CTRL_H = (1<<2);
  
  /* autolimit values are in MATCH[0] */
  LPC_SET->MATCH[0].L = limit;
  LPC_SET->MATCH[0].H = limit;
  
}