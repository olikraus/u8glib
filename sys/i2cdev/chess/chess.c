#include <stdio.h>
#include <stdlib.h>

#include "u8g_linux.h"


uint8_t get_key_code(void)
{
  uint8_t chess_key = CHESS_KEY_NONE;
  int ch = u8g_linux_getch();

  switch ( ch ) {
  case 'n':
  case 274: // arrow down
  case 275: // arrow right
      chess_key = CHESS_KEY_NEXT;
      break;
  case 'p':
  case 273: // arrow up
  case 276: // arrow left
      chess_key = CHESS_KEY_PREV;
      break;
  case ' ':
      chess_key = CHESS_KEY_SELECT;
      break;
  case 'q':
      exit(0);
      break;
  }
  return chess_key;
}

int main(int argc, const char *argv[])
{
  
  uint8_t keyCode = CHESS_KEY_NONE;
  uint8_t is_redraw = 1;
  
  u8g_t u8g;

  u8g_linux_Init(&u8g, argc, argv);
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
