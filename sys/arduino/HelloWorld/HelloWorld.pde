/*

  HelloWorld.pde
  
  Universal 8bit Graphics Library
  
  Copyright (c) 2011, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  


*/


#include "u8g.h"

u8g_t u8g;


void setup(void)
{
  //pinMode(13, OUTPUT);

  
  //u8g_Init8Bit(&u8g, &u8g_dev_ks0108_128x64_fast,  8,    9, 10, 11,   4,   5,   6,   7, 18, 14, 15, 17, 16, U8G_PIN_NONE);
  /*
#define PIN_SCK 13
#define PIN_MISO  12
#define PIN_MOSI 11
#define PIN_CS 10
#define PIN_A0 9
#define PIN_RST 8
  */
  
  //u8g_InitSPI(&u8g, &u8g_dev_uc1701_dogs102_sw_spi, 13, 11, 10, 9, U8G_PIN_NONE);
  u8g_InitSPI(&u8g, &u8g_dev_ssd1325_nhd_27_12864ucy3_sw_spi, 13, 11, 10, 9, U8G_PIN_NONE);
  
  //u8g_InitSPI(&u8g, &u8g_dev_pcf8812_96x65_sw_spi, 13, 11, 10, 9, 8);
  //u8g_InitSPI(&u8g, &u8g_dev_pcd8544_84x48_sw_spi, 13, 11, 10, 9, 8);
  
  //u8g_InitSPI(&u8g, &u8g_dev_uc1701_dogs102_sw_spi);
  //u8g_SetRot180(&u8g);
}

void loop(void)
{
  u8g_uint_t w,h;

  u8g_FirstPage(&u8g);
  
  do
  {
    u8g_SetFont(&u8g, u8g_font_unifont);
    //u8g_SetFont(&u8g, u8g_font_osb18r);
    w = u8g_GetWidth(&u8g);
    h = u8g_GetHeight(&u8g);
    
    u8g_DrawStr(&u8g, 0, 20, "Hello World!");
  } while( u8g_NextPage(&u8g) );
  
  u8g_Delay(100);
}

