/*
  port command sequence
  
 LPC_WWDT_BASE         (0x40000000UL)
 LPC_MRT_BASE          (0x40004000UL)
 LPC_WKT_BASE          (0x40008000UL)
 LPC_SWM_BASE          (0x4000C000UL)
 LPC_PMU_BASE          (0x40020000UL)
 LPC_CMP_BASE          (0x40024000UL)

 LPC_FMC_BASE          (0x40040000UL)			7*4
 LPC_IOCON_BASE        (0x40044000UL)		18x4
 LPC_SYSCTL_BASE       (0x40048000UL)		0x3FC   254*4
 LPC_I2C_BASE          (0x40050000UL)
 LPC_SPI0_BASE         (0x40058000UL)
 LPC_SPI1_BASE         (0x4005C000UL)
 LPC_USART0_BASE       (0x40064000UL)
 LPC_USART1_BASE       (0x40068000UL)
 LPC_USART2_BASE       (0x4006C000UL)

 LPC_CRC_BASE          (0x50000000UL)
 LPC_SCT_BASE          (0x50004000UL)

 LPC_GPIO_PORT_BASE    (0xA0000000UL)		2272*4
 LPC_PIN_INT_BASE      (0xA0004000UL)

 0000 0000 dddd dddd	Delay by dddddddd micro seconds
 0001 xxxx yyyy zzzz  	Load base address    0xX00YZ000UL
 001b bbbb xxxx xxxx	Return bit bbbbb in uint32 at 4*xxxxxxxx + base adr
 010b bbbb xxxx xxxx	Clear bit bbbbb in uint32 at 4*xxxxxxxx + base adr
 011b bbbb xxxx xxxx	Set bit bbbbb in uint32 at 4*xxxxxxxx + base adr
 3320
 
 
*/

#include "sys.h"
#include "port.h"

/* PCS = Port command sequence */
/* return value is 0 or 1 */
unsigned pcs(const uint16_t *seq)
{
  uint16_t cmd;
  unsigned ret = 0;
  uint32_t mask;
  uint32_t lowbyte;
  uint32_t *base = 0;
  do
  {
      cmd = *seq++;
      lowbyte = cmd & 255;
      mask = 1UL<<((cmd >> 8)&31);
      switch((cmd>>13) & 3)
      {
	case 0:
	  if ( (cmd & 0x1000) != 0 )
	  {
	    /* load base adr */
	    base = (uint32_t *)(((cmd & 0x0f00UL)<<20) | ((lowbyte)<<12));
	    //printf("%p\n", base);
	  }
	  else
	  {
	    /* delay */
	    delay_micro_seconds(lowbyte);	    
	  }
	  break;
	case 1:
	  ret = (base[lowbyte] & mask) == 0 ? 0 : 1 ;
	  break;
	case 2:
	  base[lowbyte]  &= ~mask;
	  break;
	case 3:
	  //printf("%04x %08x\n ", idx, mask);
	  base[lowbyte]  |= mask;
	  break;
      }
  } while( (cmd & PCS_END) == 0 );
  return ret;
}

/*
uint16_t test[] = 
{
  PCS_BASE(0x0a0000000+0x2000),
  PCS_SETB(2,0x0200/4) | PCS_END
};

void main(void)
{
  pcs(test);
}
*/