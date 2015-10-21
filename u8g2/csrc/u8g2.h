/*

  u8g2.h
  
  call sequence
  
  u8g2_Setup_XYZ
    u8x8_Setup_XYZ
      u8x8_SetupDefaults(u8g2);
      assign u8x8 callbacks
      u8x8->display_cb(u8x8, U8X8_MSG_DISPLAY_SETUP, 0, NULL);  
    setup tile buffer
    
  
  
  
  
*/




#ifndef _U8G2_H
#define _U8G2_H

#include "u8x8.h"

#ifdef __GNUC__
#  define U8G2_NOINLINE __attribute__((noinline))
#else
#  define U8G2_NOINLINE
#endif

#define U8G2_FONT_HEIGHT_MODE_TEXT 0
#define U8G2_FONT_HEIGHT_MODE_XTEXT 1
#define U8G2_FONT_HEIGHT_MODE_ALL 2




#endif

