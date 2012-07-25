
/*
  partial update of the screen by jumping out of the picture loop
*/

#include "U8glib.h"

U8GLIB_ST7920_128X64 u8g(18, 16, 17, U8G_PIN_NONE);                  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//U8GLIB_ST7920_192X32 u8g(18, 16, 17, U8G_PIN_NONE);                  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17

/*
  the pb object is (usually) the device name from http://code.google.com/p/u8glib/wiki/device
  with "_pb" added at the end.
*/
extern u8g_pb_t u8g_dev_st7920_192x32_sw_spi_pb;
extern u8g_pb_t u8g_dev_st7920_128x64_sw_spi_pb;
/*
  Within the body of the picture loop, the variables
    u8g_dev_st7920_128x64_sw_spi_pb.p.page_y0;
  and
    u8g_dev_st7920_128x64_sw_spi_pb.p.page_y1;
  will change.
*/

uint8_t fast_cnt;
uint8_t slow_cnt;

void drawFast(void) {
  // graphic commands to redraw upper part of the screen 
  u8g.drawStr( fast_cnt, 12, "Fast Area");
  u8g.drawVLine(fast_cnt,0, u8g.getHeight());
}

void drawSlow(void) {
  // graphic commands to redraw upper part of the screen 
  u8g.drawStr( 0, 30, "Slow Area");
  u8g.drawVLine(slow_cnt,0, u8g.getHeight());
}

void setup(void) {  
  fast_cnt = 0;
  slow_cnt = 0;
  u8g.setFont(u8g_font_unifont);
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    drawFast();
    /* check if the upper part has finished */
    if ( u8g_dev_st7920_128x64_sw_spi_pb.p.page_y0 >= 16 )
      break; 
    //if ( u8g_dev_st7920_192x32_sw_spi_pb.p.page_y0 >= 16 )
    //  break; 
  } while( u8g.nextPage() );
  
  fast_cnt++;
  if ( fast_cnt >= 4 ) {
    fast_cnt = 0;
    slow_cnt++;
    if ( slow_cnt >= u8g.getWidth() )
      slow_cnt = 0;
    u8g.firstPage();  
    do {
      /* draw complete screen, so draw both, fast and slow procedure */
      drawFast();
      drawSlow();
    } while( u8g.nextPage() );
  }
  
}
