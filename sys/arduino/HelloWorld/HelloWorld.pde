

#include "u8g.h"

u8g_t u8g;


void setup(void)
{
  pinMode(13, OUTPUT);

  
  u8g_Init(&u8g, &u8g_dev_pcf8812_96x65_sw_spi);
  // u8g_Init(&u8g, &u8g_dev_ks0108_128x64);
  // u8g_Init(&u8g, &u8g_dev_uc1701_dogs102_sw_spi);
  //u8g_SetRot180(&u8g);
}

void loop(void)
{
  u8g_uint_t w,h;
  static u8g_uint_t o = 0;

  u8g_FirstPage(&u8g);
  
  do
  {
    //u8g_SetFont(&u8g, u8g_font_10x20);
    u8g_SetFont(&u8g, u8g_font_osb18r);
    w = u8g_GetFontBBXWidth(&u8g);
    h = u8g_GetFontBBXHeight(&u8g);
    
    u8g_DrawStr(&u8g, 20+2+o, h, 0, "A");
    u8g_DrawStr(&u8g, 20+2+o, h+2, 1, "B");
    u8g_DrawStr(&u8g, 20+o, h+2, 2, "C");
    u8g_DrawStr(&u8g, 20+o, h, 3, "D");

    u8g_DrawPixel(&u8g, 10,0);
    u8g_DrawPixel(&u8g, 20,0);
    u8g_DrawPixel(&u8g, 30,0);
    
    u8g_DrawPixel(&u8g, 60,0);
    u8g_DrawPixel(&u8g, 70,0);
    u8g_DrawPixel(&u8g, 80,0);

    
    u8g_DrawFrame(&u8g, 2, 2+3, 9, 3+3);
    u8g_DrawFrame(&u8g, 0, 0+3, 13, 7+3);
    
    u8g_DrawFrame(&u8g, 60, 40, 1+o, 1+o);
    
    /*
    u8g_DrawFrame(&u8g, 0, 0, 2, 64);
    
    u8g_SetPixel(&u8g, 20, 5);
    */
  } while( u8g_NextPage(&u8g) );
  o++;
  o = o & 15;
  
  delay(500);
}

