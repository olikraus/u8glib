

#ifndef _PORT_H
#define _PORT_H

#include <stdint.h>

#define PCS_END 0x8000UL
#define PCS_GETB(bit,idx) (0x2000UL | ((bit)<<8) | (idx))
#define PCS_CLRB(bit,idx) (0x4000UL | ((bit)<<8) | (idx))
#define PCS_SETB(bit,idx) (0x6000UL | ((bit)<<8) | (idx))
#define PCS_BASE(b) (0x1000UL | ((((b)>>28)&15)<<8) | ((((b)>>12)&255)))
#define PCS_DLY(us) (us)

unsigned pcs(const uint16_t *seq);

#endif
