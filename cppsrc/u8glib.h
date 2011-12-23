/*

  u8glib.h
  
  C++ Interface

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

class U8GLIB 
{
  private:
    u8g_t u8g;
    uint8_t initSPI(u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE);
    uint8_t initHWSPI(u8g_dev_t *dev, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE);
    uint8_t init8Bit(u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, 
        uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE);
  public:
  
    U8GLIB(u8g_dev_t *dev, uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset) 
      { initSPI(dev, sck, mosi, cs, a0, reset); }
    U8GLIB(u8g_dev_t *dev, uint8_t cs, uint8_t a0, uint8_t reset) 
      { initHWSPI(dev, cs, a0, reset); }
    U8GLIB(u8g_dev_t *dev, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, 
        uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw, uint8_t reset) 
      { init8Bit(dev, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset); }
      
    void setFont(const u8g_pgm_uint8_t *font) {u8g_SetFont(&u8g, font); }
    u8g_uint_t drawStr(u8g_uint_t x, u8g_uint_t y, const char *s) { return u8g_DrawStr(&u8g, x, y, s); }
    u8g_uint_t drawStrP(u8g_uint_t x, u8g_uint_t y, const u8g_pgm_uint8_t *s) { return u8g_DrawStrP(&u8g, x, y, s); }
};


class U8GLIB_DOGS102 : public U8GLIB 
{
  public:
    U8GLIB_DOGS102(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) 
      : U8GLIB(&u8g_dev_uc1701_dogs102_sw_spi, sck, mosi, cs, a0, reset)
      { }
    U8GLIB_DOGS102(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) 
      : U8GLIB(&u8g_dev_uc1701_dogs102_sw_spi, cs, a0, reset)
      { }
};


