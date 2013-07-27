

#ifndef _CRB_H
#define _CRB_H


#define CRB_LEN 256

struct _crb_stuct
{
  volatile uint16_t start;
  volatile uint16_t good_end;
  volatile uint16_t end;
  volatile uint8_t is_full;
  volatile uint8_t is_wait_for_dollar;	/* only updated by crb_AddChar() */
  uint8_t buf[CRB_LEN];

  uint8_t curr_pos;
};
typedef struct _crb_stuct crb_t;

int16_t crb_GetInit(crb_t *crb);
int16_t crb_GetCurr(crb_t *crb);
int16_t crb_GetNext(crb_t *crb);

#endif
