

#include "u8g_dogm128_api.h"
#include <stdlib.h>
#include <stdio.h>


int u8g_sdl_get_key(void);

#ifdef OLD
int main(void)
{
  u8g_uint_t w,h;
  u8g_t u8g;
  
  u8g_Init(&u8g, &u8g_dev_sdl_1bit);
  u8g_FirstPage(&u8g);
  do
  {
    u8g_SetColorIndex(&u8g, 1);
    u8g_SetFont(&u8g, u8g_font_10x20);
    //u8g_SetFont(&u8g, u8g_font_fur17);
    w = u8g_GetFontBBXWidth(&u8g);
    h = u8g_GetFontBBXHeight(&u8g);
    //u8g_DrawStr(&u8g, 0, 2*h, 0, "ABCgdef");
    u8g_DrawStr(&u8g, 0, 5, 0, "g");
    u8g_DrawStr(&u8g, 10, 7, 0, "g");
    u8g_DrawStr(&u8g, 20, 9, 0, "g");
    u8g_DrawStr(&u8g, 20, 9, 0, "ga");

    //u8g_DrawStr(&u8g, 40, 9, 0, "g");
    u8g_DrawStr(&u8g, 70, 25, 0, "gabc");
    u8g_DrawStr(&u8g, 70, 25, 1, "gabc");
    u8g_DrawStr(&u8g, 70, 25, 2, "gabc");
    u8g_DrawStr(&u8g, 70, 25, 3, "gabc");

    
    //u8g_DrawFrame(&u8g, 2, 2, 9, 3);
    //u8g_DrawFrame(&u8g, 0, 0, 13, 7);
    //u8g_DrawHLine( &u8g, 0, 16, 50 );   
    
    u8g_SetColorIndex(&u8g, 1);
    
    u8g_DrawHLine( &u8g, 0, 3, 127 );   
    
    u8g_SetColorIndex(&u8g, 0);
    u8g_DrawHLine( &u8g, 0, 4, 127 );   
    
    
  }while( u8g_NextPage(&u8g) );
  
  while( u8g_sdl_get_key() < 0 )
    ;
  
  return 0;
}

#endif


int main(void)
{
  uint16_t adc = 128;
  u8g_InitDogm128API(&u8g_dev_sdl_1bit);
  
  
  
  for(;;)
  {    
    dog_StartPage();
    do
    {
      st_Draw(0);
    } while( dog_NextPage() );
    //adc = sys_adc();
    //adc >>= 2;
    //dog_Delay(10);
    SDL_Delay(10);
    st_Step(adc, 1, 0);
    
    if ( u8g_sdl_get_key() >= 0 )
      break;
  }  
  return 0;
}

