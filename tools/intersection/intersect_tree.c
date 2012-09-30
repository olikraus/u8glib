
#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8g_uint_t;

uint8_t u8g_ccc(uint8_t c1, uint8_t c2, uint8_t c3)
{
  uint8_t tmp;
  tmp = c1;
  c1 &= c2;
  c2 &= c3;
  c3 &= tmp;
  c1 |= c2;
  c1 |= c3;
  return c1 & 1;
}

void print_truth_table(void)
{
  uint8_t c1;
  uint8_t c2;
  uint8_t c3;
  for( c3 = 0; c3 < 2; c3++ )
    for( c2 = 0; c2 < 2; c2++ )
      for( c1 = 0; c1 < 2; c1++ )
      {
	printf("%d %d %d | %d\n", c3, c2, c1, u8g_ccc(c1,c2,c3));
      }
  
}

int main(void)
{
  print_truth_table();
  return 1;
}

/* output will be:
0 0 0 | 0
0 0 1 | 0
0 1 0 | 0
0 1 1 | 1
1 0 0 | 0
1 0 1 | 1
1 1 0 | 1
1 1 1 | 1
*/

/* derived intersection procedure */


uint8_t u8g_is_intersection_math(u8g_uint_t a0, u8g_uint_t a1, u8g_uint_t v0, u8g_uint_t v1)
{
  uint8_t c1, c2, c3, tmp;
  c1 = v0 <= a1;
  c2 = v1 >= a0;
  c3 = v0 > v1;
  
  tmp = c1;
  c1 &= c2;
  c2 &= c3;
  c3 &= tmp;
  c1 |= c2;
  c1 |= c3;
  return c1 & 1;
}

uint8_t u8g_is_intersection_decision_tree(u8g_uint_t a0, u8g_uint_t a1, u8g_uint_t v0, u8g_uint_t v1)
{
  if ( v0 <= a1 )
  {
    if ( v1 >= a0 )
    {
      return 1;
    }
    else
    {
      if ( v0 > v1 )
      {
	return 1;
      }
      else
      {
	return 0;
      }
    }
  }
  else
  {
    if ( v1 >= a0 )
    {
      if ( v0 > v1 )
      {
	return 1;
      }
      else
      {
	return 0;
      }
    }
    else
    {
      return 0;
    }
  }
}

