/*

  Console.pde
  
  Read from serial monitor, output to display
  
  >>> Before compiling: Please remove comment from the constructor of the 
  >>> connected graphics display (see below).
  
  Universal 8bit Graphics Library, http://code.google.com/p/u8glib/
  
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


#include "U8glib.h"

// setup u8g object, please remove comment from one of the following constructor calls

//U8GLIB_NHD27OLED_BW u8g(13, 11, 10, 9);       // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_NHD27OLED_GR u8g(13, 11, 10, 9);       // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGS102 u8g(13, 11, 10, 9);                    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGM132 u8g(13, 11, 10, 9);                    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGM128 u8g(13, 11, 10, 9);                    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_ST7920_128X64 u8g(13, 11, U8G_PIN_NONE, U8G_PIN_NONE);                  // SPI Com: SCK = 13, MOSI = 11, CS = U8G_PIN_NONE, A0 = U8G_PIN_NONE
//U8GLIB_ST7920_128X64 u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, U8G_PIN_NONE, U8G_PIN_NONE, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_192X32 u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, U8G_PIN_NONE, U8G_PIN_NONE, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_LM6059 u8g(13, 11, 10, 9);                    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_LM6063 u8g(13, 11, 10, 9);                    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_BW u8g(13, 11, 10, 9);            // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_GR u8g(13, 11, 10, 9);             // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);                    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
//U8GLIB_PCF8812 u8g(13, 11, 10, 9, 8);                    // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
//U8GLIB_KS0108_128 u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 14, 15, 17, 16); // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, cs1=14, cs2=15,di=17,rw=16


// setup input buffer
#define LINE_MAX 18 
uint8_t line_buf[LINE_MAX] = "U8GLIB Console";
uint8_t line_pos = 0;

// setup a text screen to support scrolling
#define ROW_MAX 6
uint8_t screen[ROW_MAX][LINE_MAX];

// line height, which matches the selected font (5x7)
#define LINE_PIXEL_HEIGHT 7

// clear entire screen, called during setup
void clear_screen(void) {
  uint8_t i, j;
  for( i = 0; i < ROW_MAX; i++ )
    for( j = 0; j < LINE_MAX; j++ )
      screen[i][j] = 0;  
}

// append a line to the screen, scroll up
void add_line_to_screen(void) {
  uint8_t i, j;
  for( j = 0; j < LINE_MAX; j++ )
    for( i = 0; i < ROW_MAX-1; i++ )
      screen[i][j] = screen[i+1][j];
  
  for( j = 0; j < LINE_MAX; j++ )
    screen[ROW_MAX-1][j] = line_buf[j];
}

// U8GLIB draw procedure: output the screen
void draw(void) {
  uint8_t i;
  // graphic commands to redraw the complete screen are placed here  
  u8g.setFont(u8g_font_5x7);
  for( i = 0; i < ROW_MAX; i++ )
    u8g.drawStr( 0, (i+1)*LINE_PIXEL_HEIGHT, (char *)(screen[i]));
}

void exec_line(void) {
  // echo line to the serial monitor
  Serial.println((const char *)line_buf);
  
  // add the line to the screen
  add_line_to_screen();
  
  // U8GLIB picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
}

// clear current input buffer
void reset_line(void) { 
      line_pos = 0;
      line_buf[line_pos] = '\0';  
}

// add a single character to the input buffer 
void char_to_line(uint8_t c) {
      line_buf[line_pos] = c;
      line_pos++;
      line_buf[line_pos] = '\0';  
}

// check serial in and handle the character
void read_line(void) {
  if ( Serial.available() )
  {
    uint8_t c;
    c = Serial.read();
    if ( line_pos >= LINE_MAX-1 ) {
      exec_line();
      reset_line();
      char_to_line(c);
    } 
    else if ( c == '\n' ) {
      exec_line();
      reset_line();
    }
    else if ( c == '\r' ) {
      // ignore '\r' 
    }
    else {
      char_to_line(c);
    }
  }
}

// Arduino master setup
void setup(void) {
  clear_screen();               // clear screen
  delay(1000);                  // do some delay
  Serial.begin(9600);        // init serial
  exec_line();                    // place the input buffer into the screen
  reset_line();                   // clear input buffer
}

// Arduino main loop
void loop(void) {
  read_line();
}

