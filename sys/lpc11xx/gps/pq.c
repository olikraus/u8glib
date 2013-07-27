/*
  position queue
  
*/

#include <stddef.h>
#include <string.h>
#include "datecalc.h"
#include "pq.h"


void pq_Init(pq_t *pq)
{
  memset(pq, 0, sizeof(pq_t));
  crb_Init(&(pq->crb));
}

void pq_AddStr(pq_t *pq, const char *str)
{
  crb_AddStr(&(pq->crb), str);  
}

void pq_DeleteFirst(pq_t *pq)
{
  uint8_t i;
  if ( pq->cnt > 0 )
  {
    for( i = 1; i < pq->cnt; i++ )
    {
      pq->queue[i-1] = pq->queue[i];
    }
    pq->cnt--;
  }
}

/* add values from the interface to the queue record */
void pq_AddInterfaceValuesToQueue(pq_t *pq)
{
  if ( pq->cnt >= PQ_LEN )
    pq_DeleteFirst(pq);
  pq->queue[pq->cnt].pos = pq->interface.pos;
  pq->cnt++;
}


/*===========================================*/


void pq_ResetParser(pq_t *pq)
{
  crb_GetInit(&(pq->crb));  
}

int16_t pq_GetCurr(pq_t *pq)
{
  return crb_GetCurr(&(pq->crb));
}

int16_t pq_GetNext(pq_t *pq)
{
  return crb_GetNext(&(pq->crb));
}

uint8_t pq_SkipSpace(pq_t *pq)
{
  int16_t c;
  c = pq_GetCurr(pq);
  if ( c < 0 )
    return 0;
  for(;;)
  {
    if ( c < 0 || c > 32 )
      break;
    c = pq_GetNext(pq);
  }
  return 1;
}


uint8_t pq_GetNum(pq_t *pq, uint32_t *num, uint8_t *digit_cnt)
{
  int16_t c;
  if ( pq_SkipSpace(pq) == 0 )
    return 0;
  if ( digit_cnt != NULL )
    *digit_cnt = 0;
  *num = 0L;
  c = pq_GetCurr(pq);
  if ( c < 0 )
    return 0;
  for(;;)
  {
    if ( c < '0' || c > '9' )
      break;
    *num *= 10L;
    *num += c - '0';
    if ( digit_cnt != NULL )
      *digit_cnt += 1;
    c = pq_GetNext(pq);
  }
  return 1;
}

uint8_t pq_GetFloat(pq_t *pq, gps_float_t *f)
{
  uint8_t digit_cnt;
  uint32_t num;
  if ( pq_GetNum(pq, &num, NULL) == 0 )
    return 0;
  *f = (gps_float_t)num;
  if ( pq_GetCurr(pq) == '.' )
  {
    pq_GetNext(pq);
    if ( pq_GetNum(pq, &num, &digit_cnt) == 0 )
      return 0;
    
    {
      gps_float_t g;
      g = (gps_float_t)num;
      while( digit_cnt > 0 )
      {
	g /= (gps_float_t)10;
	digit_cnt--;
      }
      *f += g;
    }
  }
  return 1;
}


