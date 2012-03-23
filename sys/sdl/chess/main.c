

#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>


int u8g_sdl_get_key(void);

uint8_t get_key_code(void)
{
  uint8_t chess_key;
  int sdl_key;
  sdl_key = u8g_sdl_get_key();
  chess_key = CHESS_KEY_NONE;
  if ( sdl_key > 0 )
  {
    if ( sdl_key == 'n' )
      chess_key = CHESS_KEY_NEXT;
    else if ( sdl_key == 'p' )
      chess_key = CHESS_KEY_PREV;
    else if ( sdl_key == ' ' )
      chess_key = CHESS_KEY_SELECT;
    else if ( sdl_key == 'q' )
      exit(0);
  }    
  return chess_key;  
}



int main(void)
{
  
  uint8_t keyCode = CHESS_KEY_NONE;
  uint8_t is_redraw = 1;
  
  u8g_t u8g;
  
  u8g_Init(&u8g, &u8g_dev_sdl_2bit);
  u8g_FirstPage(&u8g);
  chess_Init(&u8g, 0);

#ifdef PERFTEST
  chess_Step(CHESS_KEY_SELECT);
  chess_Step(CHESS_KEY_NONE);
  chess_Step(CHESS_KEY_NEXT);
  chess_Step(CHESS_KEY_NONE);
  chess_Step(CHESS_KEY_NEXT);
  chess_Step(CHESS_KEY_NONE);
#endif
  
  for(;;)
  {

    
    if ( is_redraw != 0 )
    {
#ifdef PERFTEST
      int i;
      for( i = 0; i < 500; i++ )
      {
#endif
        u8g_FirstPage(&u8g);
        do {
          chess_Draw();
        } while( u8g_NextPage(&u8g) );
#ifdef PERFTEST
      }
#endif
      is_redraw--;
    }
#ifdef PERFTEST
    exit(0);
#endif
    
    keyCode = get_key_code();
    if ( keyCode != CHESS_KEY_NONE )
    {
      is_redraw = 2;
      chess_Step(keyCode);
    }
    chess_Step(CHESS_KEY_NONE);
  }
}

