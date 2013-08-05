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

void pq_AddChar(pq_t *pq, uint8_t c)
{
  crb_AddChar(&(pq->crb), c);  
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

pq_entry_t *pq_GetLatestEntry(pq_t *pq)
{
  if ( pq->cnt == 0 )
    return NULL;
  return &(pq->queue[pq->cnt-1]);
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

uint8_t pq_GetLonLatFloat(pq_t *pq, gps_float_t *f)
{
  uint8_t digit_cnt;
  uint32_t num;
  uint32_t minutes;
  gps_float_t fraction;
  if ( pq_GetNum(pq, &num, NULL) == 0 )
    return 0;
  minutes = num % 100UL;
  num /= 100UL;  
  *f = (gps_float_t)num;
  fraction = 0.0;
  if ( pq_GetCurr(pq) == '.' )
  {
    pq_GetNext(pq);
    if ( pq_GetNum(pq, &num, &digit_cnt) == 0 )
      return 0;
    fraction = (gps_float_t)num;
    pq->digit_cnt = digit_cnt;
    while( digit_cnt > 0 )
    {
      fraction /= (gps_float_t)10;
      digit_cnt--;
    }
    fraction += (gps_float_t)minutes;
    fraction /= (gps_float_t)60;
    *f += fraction;
  }
  return 1;
}

/* read a small string, max 8 bytes, including '\0' */ 
#define PQ_STR_MAX 8
const char *pq_GetStr(pq_t *pq)
{
  static char buf[PQ_STR_MAX];
  uint8_t pos;
  int16_t c;
  
  if ( pq_SkipSpace(pq) == 0 )
    return NULL;
  c = pq_GetCurr(pq);
  pos = 0;
  while( (c >=64 || c == '$') && pos < PQ_STR_MAX-1 )
  {
    buf[pos] = c;
    c = pq_GetNext(pq);
    pos++;
  }
  buf[pos] = '\0';
  return buf;
}

uint8_t pq_CheckChar(pq_t *pq, int16_t c)
{
  if ( pq_SkipSpace(pq) == 0 )
    return 0;
  if ( pq_GetCurr(pq) != c )
    return 0;
  pq_GetNext(pq);
  return 1;
}

uint8_t pq_CheckComma(pq_t *pq)
{
  return pq_CheckChar(pq, ',');
}

/* *result is 0 for c1 and 1 for c2, undefined if none of the two is matched */
/* return value is 0 if none has matched */
uint8_t pq_CheckTwoChars(pq_t *pq, uint8_t *result, int16_t c1, int16_t c2)
{
  if ( pq_GetCurr(pq) == ',' || pq_GetCurr(pq) == '*' )
  {
    *result = 0;
    return 1;
  }
  if ( pq_CheckChar(pq, c1) != 0 )
  {
    *result = 0;
    return 1;
  }
  if ( pq_CheckChar(pq, c2) != 0 )
  {
    *result = 1;
    return 1;
  }
  return 0;
}

/*
  Assumes, that $GPRMC is alread paresed

$GPRMC,220516,A,5133.82,N,00042.24,W,173.8,231.8,130694,004.2,W*70
              1    2    3    4    5     6    7    8      9     10  11 12


      1   220516     Time Stamp
      2   A          validity - A-ok, V-invalid
      3   5133.82    current Latitude
      4   N          North/South
      5   00042.24   current Longitude
      6   W          East/West
      7   173.8      Speed in knots
      8   231.8      True course
      9   130694     Date Stamp
      10  004.2      Variation
      11  W          East/West
      12  *70        checksum

Latitude
  S --> negative
  
Longitude
  W --> negative

*/
uint8_t pq_ParseGPRMC(pq_t *pq)
{
  gps_float_t time;
  uint32_t date;
  uint8_t is_valid;
  uint8_t is_south;
  uint8_t is_west;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetFloat(pq, &time) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_CheckTwoChars(pq, &is_valid, 'V', 'A') == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetLonLatFloat(pq, &(pq->interface.pos.latitude)) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_CheckTwoChars(pq, &is_south, 'N', 'S') == 0 ) return 0;
  if ( is_south != 0 ) pq->interface.pos.latitude = -pq->interface.pos.latitude;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetLonLatFloat(pq, &(pq->interface.pos.longitude)) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_CheckTwoChars(pq, &is_west, 'E', 'W') == 0 ) return 0;
  if ( is_west != 0 ) pq->interface.pos.longitude = -pq->interface.pos.longitude;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetFloat(pq, &(pq->interface.speed_in_knots)) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetFloat(pq, &(pq->interface.true_course)) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetNum(pq, &date, NULL) == 0 ) return 0;  
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetFloat(pq, &(pq->interface.magnetic_variation)) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_CheckTwoChars(pq, &is_west, 'E', 'W') == 0 ) return 0;
  if ( is_west != 0 ) pq->interface.pos.longitude = -pq->interface.pos.longitude;
  if ( is_valid != 0 )
  {
    pq_AddInterfaceValuesToQueue(pq);
    pq->valid_gprmc++;
  }
  else
  {
    pq->invalid_gprmc++;
  }
  return 1;
}

/*
$GPGGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh
1    = UTC of Position
2    = Latitude
3    = N or S
4    = Longitude
5    = E or W
6    = GPS quality indicator (0=invalid; 1=GPS fix; 2=Diff. GPS fix)
7    = Number of satellites in use [not those in view]
8    = Horizontal dilution of position
9    = Antenna altitude above/below mean sea level (geoid)
10   = Meters  (Antenna height unit)
11   = Geoidal separation (Diff. between WGS-84 earth ellipsoid and
       mean sea level.  -=geoid is below WGS-84 ellipsoid)
12   = Meters  (Units of geoidal separation)
13   = Age in seconds since last update from diff. reference station
14   = Diff. reference station ID#
15   = Checksum
*/
uint8_t pq_ParseGPGGA(pq_t *pq)
{
  gps_float_t time;
  uint32_t int_time;
  uint32_t gps_quality;
  uint32_t sat_cnt;
  gps_float_t dilution;
  gps_float_t altitude;
  uint8_t is_south;
  uint8_t is_west;
  gps_float_t age;
  uint32_t ref_sat;
  
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetFloat(pq, &time) == 0 ) return 0;
  int_time = time;
  pq->interface.hour = int_time / 10000;
  pq->interface.minute = ((uint32_t)(int_time / 100)) % 100;
  pq->interface.second = ((uint32_t)int_time) % 100;
  pq->interface.millisecond = 0;	/* not used */
  
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetLonLatFloat(pq, &(pq->interface.pos.latitude)) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_CheckTwoChars(pq, &is_south, 'N', 'S') == 0 ) return 0;
  if ( is_south != 0 ) pq->interface.pos.latitude = -pq->interface.pos.latitude;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetLonLatFloat(pq, &(pq->interface.pos.longitude)) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_CheckTwoChars(pq, &is_west, 'E', 'W') == 0 ) return 0;
  if ( is_west != 0 ) pq->interface.pos.longitude = -pq->interface.pos.longitude;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetNum(pq, &gps_quality, NULL) == 0 ) return 0;  
  pq->gps_quality = gps_quality;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetNum(pq, &sat_cnt, NULL) == 0 ) return 0;  
  pq->sat_cnt = sat_cnt;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetFloat(pq, &dilution) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetFloat(pq, &altitude) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_CheckTwoChars(pq, &is_west, 'M', 'm') == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetFloat(pq, &age) == 0 ) return 0;
  if ( pq_CheckComma(pq) == 0 ) return 0;
  if ( pq_GetNum(pq, &ref_sat, NULL) == 0 ) return 0;  
  
  if ( gps_quality != 0 )
  {
    pq_AddInterfaceValuesToQueue(pq);
    pq->valid_gpgga++;
  }
  else
  {
    pq->invalid_gpgga++;
  }
  return 1;
}


/* GPGSA, GPGSV */

/* return 0 on parsing error */
uint8_t pq_ParseSentence(pq_t *pq)
{
  uint8_t result = 0;
  const char *s;
  if ( crb_IsSentenceAvailable(&(pq->crb)) == 0 )
    return 1;
  pq_ResetParser(pq);
  s = pq_GetStr(pq);
  if ( s != NULL )
  {
    if (  strcmp(s, "$GPRMC") == 0 )
    {
      pq->processed_gprmc++;
      result = pq_ParseGPRMC(pq);
      if ( result == 0 )
	pq->parser_error_gprmc++; 
    }
    else if (  strcmp(s, "$GPGGA") == 0 )
    {
      pq->processed_gpgga++;
      result = pq_ParseGPGGA(pq);
      if ( result == 0 )
	pq->parser_error_gpgga++; 
      
    }
    else
    {
      if ( *s != '\0' )
      {
	strncpy(pq->last_unknown_msg, s, 8);
	pq->last_unknown_msg[7] = '\0';
      }
    }
  } 
  crb_DeleteSentence(&(pq->crb));
  pq->processed_sentences++;
  return result;
}

/*
  uint8_t pos_is_neg;	temp variable for gps_float_t conversion 
  uint8_t pos_minutes;	temp variable for gps_float_t conversion 0..59 
  uint16_t pos_fraction;	0...999 
  uint16_t pos_degree;	temp variable for gps_float_t conversion 
*/
void pg_FloatToDegreeMinutes(pq_t *pq, gps_float_t f)
{
  float g;
  pq->pos_is_neg = 0;
  if ( f < (gps_float_t)0 )
    f = -f;
  f = GPS_MODF(f,&g);
  pq->pos_degree = g;
  f *=(gps_float_t)60;
  f = GPS_MODF(f,&g);
  pq->pos_minutes = g;
  f *= (gps_float_t)1000;
  pq->pos_fraction = f;  
}

/* writes cnt + 1 chars to s, including '\0' */
void pg_itoa(char *s, uint16_t x, uint8_t cnt)
{
  uint16_t c;
  s[cnt] = '\0';
  while( cnt > 0 )
  {
    cnt--;
    c = x % 10;
    c += '0';
    s[cnt] = c;
    x /= 10;
  }
  
}

/*
  copy internal 
  uint8_t pos_is_neg;	temp variable for gps_float_t conversion 
  uint8_t pos_minutes;	temp variable for gps_float_t conversion 0..59 
  uint16_t pos_fraction;	0...999 
  uint16_t pos_degree;	temp variable for gps_float_t conversion 
  into a string
  N ddd° mm.fff'   --> 14 chars, 15 with '\0'  
*/
void pg_DegreeMinutesToStr(pq_t *pq, uint8_t is_lat, char *s)
{
  uint8_t cnt;
  if ( is_lat != 0 )
  {
    if ( pq->pos_is_neg != 0 )
    {
      s[0] = 'S';
    }
    else
    {
      s[0] = 'N';
    }
  }
  else
  {
    if ( pq->pos_is_neg != 0 )
    {
      s[0] = 'W';
    }
    else
    {
      s[0] = 'E';
    }
  }
  s[1] = ' ';
  pg_itoa(s+2, pq->pos_degree, 3);
  s[5] = '°';
  s[6] = ' ';
  pg_itoa(s+7, pq->pos_minutes, 2);
  s[9] = '.';
  pg_itoa(s+10, pq->pos_fraction, 3);
  s[13] = '\'';
  s[14] = '\0';
}

/* s must be at least 10 chars long */
void pg_FloatToStr(gps_float_t f, char *s)
{
  float g;
  if ( f < (gps_float_t)0 )
  {
    f = -f;
    *s = '-';
    s++;
  }
  f = GPS_MODF(f,&g);
  pg_itoa(s, g, 3);
  f*=10000;
  f = GPS_MODF(f,&g);
  s[3] = '.';
  pg_itoa(s+4, g, 4);
  s[8] = '\0';
  
}

/*
M_PI
M_TWOPI
*/

#ifdef EXTRA
// returns distance in meters between two positions, both specified
// as signed decimal-degrees latitude and longitude. Uses great-circle
// distance computation for hypothised sphere of radius 6372795 meters.
// Because Earth is no exact sphere, rounding errors may be upto 0.5%.
// Source:  Maarten Lamers, http://www.maartenlamers.com/nmea/
float distance(float lat1, float long1, float lat2, float long2, float units_per_meter) 
{
  float delta = radians(long1-long2);
  float sdlong = sin(delta);
  float cdlong = cos(delta);
  lat1 = radians(lat1);
  lat2 = radians(lat2);
  float slat1 = sin(lat1);
  float clat1 = cos(lat1);
  float slat2 = sin(lat2);
  float clat2 = cos(lat2);
  delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
  delta = sq(delta);
  delta += sq(clat2 * sdlong);
  delta = sqrt(delta);
  float denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
  delta = atan2(delta, denom);
  return delta * 6372795 * units_per_meter;
}

// returns initial course in degrees (North=0, West=270) from
// position 1 to position 2, both specified as signed decimal-degrees
// latitude and longitude.
// Source:  Maarten Lamers, http://www.maartenlamers.com/nmea/
float course(float lat1, float long1, float lat2, float long2) 
{
  float dlon = radians(long2-long1);
  lat1 = radians(lat1);
  lat2 = radians(lat2);
  float a1 = sin(dlon) * cos(lat2);
  float a2 = sin(lat1) * cos(lat2) * cos(dlon);
  a2 = cos(lat1) * sin(lat2) - a2;
  a2 = atan2(a1, a2);
  if (a2 < 0.0) {
  	a2 += TWO_PI;			// modulo operator doesn't seem to work on floats
  }
  return degrees(a2);
}

#endif
