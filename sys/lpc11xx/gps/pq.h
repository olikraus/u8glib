


#ifndef _PQ_H
#define _PQ_H

#include <float.h>
#include <math.h>
#include "crb.h"

typedef float gps_float_t;
#define GPS_MODF(x,f)	modff((x),(f))
#define GPS_FLOAT_MAX	FLT_MAX


struct _gps_pos_struct
{
  gps_float_t latitude;
  gps_float_t longitude;
};
typedef struct _gps_pos_struct gps_pos_t;

struct _pq_entry_struct
{
  gps_pos_t pos;
  uint32_t timestamp;	/* seconds since 1.1.2000 */
  uint16_t millisecond;	/* milliseconds of the timestamp */
};
typedef struct _pq_entry_struct pq_entry_t;

struct _pq_interface_struct
{
  gps_pos_t pos;
  gps_float_t speed_in_knots;
  gps_float_t true_course;
  gps_float_t magnetic_variation;
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint16_t millisecond;
};
typedef struct _pq_interface_struct pq_interface_t;

#define PQ_LEN 16

struct _pq_struct
{
  crb_t crb;
  pq_interface_t interface;
  
  uint32_t processed_sentences;
  uint32_t processed_gprmc;
  uint32_t parser_error_gprmc;
  uint32_t valid_gprmc;
  uint32_t invalid_gprmc;
  uint32_t processed_gpgga;
  uint32_t parser_error_gpgga;
  uint32_t valid_gpgga;
  uint32_t invalid_gpgga;
  uint8_t gps_quality;	/* GPS quality from GPGGA record */
  uint8_t sat_cnt;	/* satellites in use (GPGGA record) */
  uint8_t cnt;		/* entries in the queue */	
  uint8_t digit_cnt;	/* number of fraction digits of lon/lat from the gps receiver */

  uint8_t pos_is_neg;	/* temp variable for gps_float_t conversion */
  uint8_t pos_minutes;	/* temp variable for gps_float_t conversion 0..59 */
  uint16_t pos_fraction;	/* 0...999 */
  uint16_t pos_degree;	/* temp variable for gps_float_t conversion */
  
  pq_entry_t queue[PQ_LEN];
  char last_unknown_msg[8];
};
typedef struct _pq_struct pq_t;

void pq_Init(pq_t *pq);
void pq_AddChar(pq_t *pq, uint8_t c);
void pq_DeleteFirst(pq_t *pq);
void pq_AddInterfaceValuesToQueue(pq_t *pq);
pq_entry_t *pq_GetLatestEntry(pq_t *pq);
void pq_ResetParser(pq_t *pq);
int16_t pq_GetCurr(pq_t *pq);
int16_t pq_GetNext(pq_t *pq);
uint8_t pq_SkipSpace(pq_t *pq);
uint8_t pq_GetNum(pq_t *pq, uint32_t *num, uint8_t *digit_cnt);
uint8_t pq_GetFloat(pq_t *pq, gps_float_t *f);
uint8_t pq_GetLonLatFloat(pq_t *pq, gps_float_t *f);
const char *pq_GetStr(pq_t *pq);
uint8_t pq_ParseGPRMC(pq_t *pq);
uint8_t pq_ParseGPGGA(pq_t *pq);
uint8_t pq_ParseSentence(pq_t *pq);

void pg_itoa(char *s, uint16_t x, uint8_t cnt);
void pg_FloatToDegreeMinutes(pq_t *pq, gps_float_t f);
void pg_DegreeMinutesToStr(pq_t *pq, uint8_t is_lat, char *s);
void pg_FloatToStr(gps_float_t f, char *s);


#endif 

