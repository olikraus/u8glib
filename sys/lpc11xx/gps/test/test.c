


#include "pq.h"
#include <stdio.h>
#include <assert.h>


pq_t pq_obj;

void test_float(pq_t *pq)
{
  gps_float_t f;
  pq_Init(pq);
  pq_AddStr(pq, "$123.456$");
  pq_ResetParser(pq);
  pq_GetNext(pq);
  pq_GetFloat(pq, &f);
  printf("%lf\n", (double)f);
}

void test_str(pq_t *pq)
{
  pq_Init(pq);
  pq_AddStr(pq, "$ABC$");
  pq_ResetParser(pq);
  printf("%s\n", pq_GetStr(pq));
  
}

void test_gprmc(pq_t *pq)
{
  pq_Init(pq);
  pq_AddStr(pq, "$GPRMC,220516,A,5133.82,N,00042.24,W,173.8,231.8,130694,004.2,W*70$");
  pq_ResetParser(pq);
  printf("%s\n", pq_GetStr(pq));
  if ( pq_ParseGPRMC(pq) == 0 ) 
  {
    printf("$GPRMC Error\n");
  }
  else
  {
    printf("Latitude: %lf\n", (double)pq->interface.pos.latitude);
    printf("Magnet Variation: %lf\n", (double)pq->interface.magnetic_variation);
  }
 
  
}

void test_sentence(pq_t *pq)
{
  pq_Init(pq);
  pq_AddStr(pq, "$GPRMC,220516,A,5133.82,N,00042.24,W,173.8,231.8,130694,004.2,W*70");

  assert ( crb_IsSentenceAvailable(&(pq->crb)) == 0 );

  pq_AddStr(pq, "$GPRMC,220516,A,1234.56,N,00042.24,W,173.8,231.8,130694,004.2,W*70");

  assert ( crb_IsSentenceAvailable(&(pq->crb)) != 0 );

  pq_AddStr(pq, "$GPRMC,220516,A,1234.56,N,00042.24,W,173.8,231.8,130694,004.2,W*70");

  assert ( crb_IsSentenceAvailable(&(pq->crb)) != 0 );
  
  pq_ResetParser(pq);
  if ( pq_ParseSentence(pq) == 0 ) 
  {
    printf("Sentence Error\n");
  }
  else
  {
    printf("Latitude: %lf\n", (double)pq->interface.pos.latitude);
    printf("Magnet Variation: %lf\n", (double)pq->interface.magnetic_variation);
  }

  pq_ResetParser(pq);
  if ( pq_ParseSentence(pq) == 0 ) 
  {
    printf("Sentence Error\n");
  }
  else
  {
    printf("Latitude: %lf\n", (double)pq->interface.pos.latitude);
    printf("Magnet Variation: %lf\n", (double)pq->interface.magnetic_variation);
  }

  assert ( crb_IsSentenceAvailable(&(pq->crb)) == 0 );


  printf("entry cnt: %d\n", pq->cnt);
  printf("Latitude of latest entry: %lf\n", (double)pq_GetLatestEntry(pq)->pos.latitude);
  

  
}




int main(void)
{
  test_sentence(&pq_obj);
  test_gprmc(&pq_obj);
  test_str(&pq_obj);
  test_float(&pq_obj);
}