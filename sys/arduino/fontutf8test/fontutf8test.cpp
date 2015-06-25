/**
 * @file    fontutf8.cpp
 * @brief   font api test for u8g lib
 * @author  Yunhui Fu (yhfudev@gmail.com)
 * @version 1.0
 * @date    2015-04-19
 * @copyright GPL
 */
#define USE_SDL 0
#if defined(ARDUINO)

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#elif defined(U8G_RASPBERRY_PI)
#include <unistd.h>
//#define delay(a) usleep((a) * 1000)

#else
#undef USE_SDL
#define USE_SDL 1
#define delay(a) SDL_Delay((a)*1000)
#endif

//#include <U8glib.h>
#include "U8glib.h"

#include "fontutf8-data.h"

#if defined(ARDUINO) || defined(U8G_RASPBERRY_PI)

#if 0
#define OLED_MOSI   9 // SDA
#define OLED_CLK   10 // SCL
#define OLED_DC    11 // D/C (data or command)
#define OLED_CS    12 // no such pin
#define OLED_RESET 13 // RST
#else
#define OLED_MOSI   4 // SDA
#define OLED_CLK    5 // SCL
#define OLED_DC     2 // D/C (data or command)
#define OLED_CS    12 // no such pin
#define OLED_RESET  3 // RST
#endif

// SW SPI Com: SCK = 10, MOSI = 9, CS = 12, A0 = 11, reset=13
#define U8GVAL_SCK   OLED_CLK
#define U8GVAL_MOSI  OLED_MOSI
#define U8GVAL_CS    OLED_CS
#define U8GVAL_A0    OLED_DC
#define U8GVAL_RESET OLED_RESET
//U8GLIB_SH1106_128X64 u8g(U8GVAL_SCK, U8GVAL_MOSI, U8GVAL_CS, U8GVAL_A0, U8GVAL_RESET);


U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);
// 或者
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);

#else
// SDL
U8GLIB u8g(&u8g_dev_sdl_2bit);
#endif

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void setup(void) {
#if 0
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
#endif
  u8g_SetUtf8Fonts (g_fontinfo, NUM_ARRAY(g_fontinfo));
}

void DrawUtf8Str (U8GLIB *this1, unsigned int x, unsigned int y, const char *utf8_msg);

void
DrawUtf8Str (U8GLIB *this1, unsigned int x, unsigned int y, const char *utf8_msg)
{
    u8g_DrawUtf8Str (this1->getU8g(), x, y, utf8_msg);
}

void u8g_chinese() {
  char s1[] = _U8GT("黄沙百戰穿金甲，");
  char s2[] = _U8GT("不破樓蘭終不還。");
  char buf[20] = _U8GT("Chinese Glyph");
  sprintf (buf, "u32=%d,w=%d,s=%d",sizeof(uint32_t),sizeof(wchar_t),sizeof(size_t));
  //sprintf (buf, "i=%d,l=%d,u=%d",sizeof(int),sizeof(long),sizeof(unsigned));
  DrawUtf8Str (&u8g, 0, 11, buf);
  DrawUtf8Str (&u8g, 5, 30, s1);
  DrawUtf8Str (&u8g, 5, 48, s2);
}

void draw(void) {
  u8g_prepare();
  u8g_chinese();
}

// calculate new output values
void uiStep(void) {
#if USE_SDL
    int key = u8g_sdl_get_key();
    switch (key) {
    case 'q':
    case ' ':
        exit(0);
    }
#endif
}

void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    draw();
    //delay(500);
  } while( u8g.nextPage() );
  uiStep();
  // rebuild the picture after some delay
  delay(500);

}

#if 0 // #if ! defined(ARDUINO)
int
main(void)
{
  setup();
  while (1) {
    loop();
  }
  return 0;
}

#endif

