/*

  TouchPanel4W.pde
  
  >>> Before compiling: Please remove comment from the constructor of the 
  >>> connected graphics display (see below).
  
  Universal 8bit Graphics Library, http://code.google.com/p/u8glib/
  
  Copyright (c) 2012, olikraus@gmail.com
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
// IMPORTANT NOTE: The complete list of supported devices is here: http://code.google.com/p/u8glib/wiki/device

//U8GLIB_NHD27OLED_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_NHD27OLED_2X_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_NHD27OLED_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_NHD27OLED_2X_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_NHD31OLED_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_NHD31OLED_2X_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_NHD31OLED_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_NHD31OLED_2X_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGS102 u8g(13, 11, 10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGM132 u8g(13, 11, 10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
U8GLIB_DOGM128 u8g(13, 11, 10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_ST7920_128X64_1X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_128X64_4X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_128X64_1X u8g(18, 16, 17);	// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//U8GLIB_ST7920_128X64_4X u8g(18, 16, 17);	// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//U8GLIB_ST7920_192X32_1X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_192X32_4X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_192X32_1X u8g(18, 16, 17);	// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//U8GLIB_ST7920_192X32_4X u8g(18, 16, 17);	// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//U8GLIB_ST7920_192X32_1X u8g(13, 11, 10);	// SPI Com: SCK = en = 13, MOSI = rw = 11, CS = di = 10
//U8GLIB_ST7920_192X32_4X u8g(10);		// SPI Com: SCK = en = 13, MOSI = rw = 11, CS = di = 10, HW SPI
//U8GLIB_ST7920_202X32_1X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_202X32_4X u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);   // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, di=17,rw=16
//U8GLIB_ST7920_202X32_1X u8g(18, 16, 17);	// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//U8GLIB_ST7920_202X32_4X u8g(18, 16, 17);	// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17
//U8GLIB_LM6059 u8g(13, 11, 10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_LM6063 u8g(13, 11, 10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_BW u8g(10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_2X_BW u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGXL160_2X_GR u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
//U8GLIB_PCF8812 u8g(13, 11, 10, 9, 8);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8
//U8GLIB_KS0108_128 u8g(8, 9, 10, 11, 4, 5, 6, 7, 18, 14, 15, 17, 16); 		// 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, cs1=14, cs2=15,di=17,rw=16
//U8GLIB_LC7981_160X80 u8g(8, 9, 10, 11, 4, 5, 6, 7,  18, 14, 15, 17, 16); 	// 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, cs=14 ,di=15,rw=17, reset = 16
//U8GLIB_LC7981_240X64 u8g(8, 9, 10, 11, 4, 5, 6, 7,  18, 14, 15, 17, 16); 	// 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, cs=14 ,di=15,rw=17, reset = 16
//U8GLIB_LC7981_240X128 u8g(8, 9, 10, 11, 4, 5, 6, 7,  18, 14, 15, 17, 16); 	// 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 en=18, cs=14 ,di=15,rw=17, reset = 16
//U8GLIB_ILI9325D_320x240 u8g(18,17,19,U8G_PIN_NONE,16 );  			// 8Bit Com: D0..D7: 0,1,2,3,4,5,6,7 en=wr=18, cs=17, rs=19, rd=U8G_PIN_NONE, reset = 16
//U8GLIB_SBN1661_122X32 u8g(8,9,10,11,4,5,6,7,14,15, 17, U8G_PIN_NONE, 16); 	// 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 cs1=14, cs2=15,di=17,rw=16,reset = 16
//U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 9);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_SSD1306_128X64 u8g(10, 9);		// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);	// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_128X32 u8g(13, 11, 10, 9);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_SSD1306_128X32 u8g(10, 9);             // HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);	// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)
//U8GLIB_SSD1309_128X64 u8g(13, 11, 10, 9);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_SSD1327_96X96_GR u8g(U8G_I2C_OPT_NONE);	// I2C
//U8GLIB_SSD1327_96X96_2X_GR u8g(U8G_I2C_OPT_NONE);	// I2C
//U8GLIB_NHD_C12864 u8g(13, 11, 10, 9, 8);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, RST = 8
//U8GLIB_NHD_C12832 u8g(13, 11, 10, 9, 8);	// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, RST = 8
//U8GLIB_T6963_240X128 u8g(8, 9, 10, 11, 4, 5, 6, 7, 14, 15, 17, 18, 16); // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7, cs=14, a0=15, wr=17, rd=18, reset=16
//U8GLIB_T6963_240X64 u8g(8, 9, 10, 11, 4, 5, 6, 7, 14, 15, 17, 18, 16); // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7, cs=14, a0=15, wr=17, rd=18, reset=16
//U8GLIB_T6963_128X64 u8g(8, 9, 10, 11, 4, 5, 6, 7, 14, 15, 17, 18, 16); // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7, cs=14, a0=15, wr=17, rd=18, reset=16


uint8_t tp_left = A3;
uint8_t tp_right = A5;
uint8_t tp_top = A4;
uint8_t tp_bottom = A2;


/*
  stati: OPEN, PRESSED, FREEZE


  stabil: schwankung des raw wertes innerhalb eines deltas 
  wenn is_pressed == 0
    wenn stabil dann is_pressed = 1
    
  wenn is_pressed == 1
      wenn nicht stabil, dann den letzten wert einfrieren, is_pressed bleibt 1
      wenn die is_pressed berechung 0 liefert, dann is_pressed = 0
    

*/


/* touch panel dimension */
struct _tpd_struct
{
  uint8_t raw;		/* input value */
  
  uint8_t start;
  uint8_t end;		
  uint8_t open;		/* value, when not touched/pressed */
  
  uint8_t range;	/* result will have range fron 0..range  (including the value of range) */
  
  uint8_t result;	/* output value: position [0...range] */
  uint8_t is_pressed;	/* output value: pressed (=1) or not pressed (=0) */
};
typedef struct _tpd_struct tpd_struct;

struct _tp_struct
{
  tpd_struct x;
  tpd_struct y;
};
typedef struct _tp_struct tp_struct;

tp_struct tp;

static uint8_t tpd_delta(uint8_t a, uint8_t b)
{
  if ( a < b )
    return b-a;
  return a-b;
}

uint8_t tpd_is_pressed_sub(uint8_t raw, uint8_t cal_untouched, uint8_t cal)
{
  if ( tpd_delta(raw, cal_untouched)  < tpd_delta(raw, cal) )
    return 0;
  return 1;
}

uint8_t tpd_IsPressed(tpd_struct *d)
{
  uint8_t start, end;
  if  ( d->start < d->end )
  {
    start = d->start;
    end = d->end;
  }
  else
  {
    end = d->start;
    start = d->end;
  }
  
  
  if ( d->open < start )
  {
    if ( d->raw < start )	/* it is pressed if "raw >= start", so continue to check otherwise */
    {
      if ( d->raw <= d->open )
	return 0;	/* not pressed */
      if ( (d->raw - d->open) < (start-d->raw) )
	return 0;
    }
  }
  else if ( d->open > end )
  {
    if ( d->raw > end)	/* it is pressed if "raw >= start", so continue to check otherwise */
    {
      if ( d->raw >= d->open )
	return 0;	/* not pressed */
      if ( (d->open - d->raw) < (d->raw - end) )
	return 0;
    }
  }
  return 1;		/*default: assume touch panel pressed */
}


/* map raw value to 0...range */
void tpd_MapTouchPosition(tpd_struct *d)
{
  uint16_t p;
  uint8_t start, end;
  if  ( d->start < d->end )
  {
    start = d->start;
    end = d->end;
  }
  else
  {
    end = d->start;
    start = d->end;
  }
  
  if ( d->raw <= start )
  {
    d->result = 0;
    return;
  }
  
  if ( d->raw >= end )
  {
    d->result = d->range;
    return;
  }
  
  p = d->raw;
  p -= start;
  p *= d->range;
  end -= start;
  p /= end;
  
  d->result = p;
}

void tp_Init(tp_struct *tp)
{
  tp->x.start = 61;
  tp->x.end = 199;
  tp->x.open = 255;
  tp->x.range = 127;
  tp->y.start = 156;
  tp->y.end = 105;
  tp->y.open = 255;
  tp->y.range = 63;
}

void tp_Calculate(tp_struct *tp)
{
  tpd_MapTouchPosition(&(tp->x));
  tp->x.is_pressed = tpd_IsPressed(&(tp->x));
  tpd_MapTouchPosition(&(tp->y));
  tp->y.is_pressed = tpd_IsPressed(&(tp->y));
}

void tp_SetRaw(tp_struct *tp, uint8_t x, uint8_t y)
{
  tp->x.raw = x;
  tp->y.raw = y;
  tp_Calculate(tp);
}


uint8_t tp_raw_x;
uint8_t tp_raw_y;

uint8_t tp_cal_x0 = 61;
uint8_t tp_cal_y0 = 156;
uint8_t tp_cal_x1 = 199;
uint8_t tp_cal_y1 = 105;
uint8_t tp_cal_x_untouched = 255;
uint8_t tp_cal_y_untouched = 255;

uint8_t tp_x;
uint8_t tp_y;
uint8_t is_pressed = 0;



int cnt = 0;

uint8_t getTouchPos(uint8_t hiPin, uint8_t lowPin, uint8_t sensePin, uint8_t dcPin)
{
  uint8_t val;
  pinMode(dcPin, INPUT);
  pinMode(sensePin, INPUT_PULLUP);
  pinMode(hiPin, OUTPUT);
  pinMode(lowPin, OUTPUT);  
  
  digitalWrite(hiPin, HIGH);
  digitalWrite(lowPin, LOW);
  delay(10);
  val = analogRead(sensePin) >> 2;
  pinMode(hiPin, INPUT);
  pinMode(lowPin, INPUT);  
  delay(10);
  return val;
}

uint8_t tp_delta(uint8_t a, uint8_t b)
{
  if ( a < b )
    return b-a;
  return a-b;
}

uint8_t is_pressed_sub(uint8_t raw, uint8_t cal_untouched, uint8_t cal)
{
  if ( tp_delta(raw, cal_untouched)  < tp_delta(raw, cal) )
    return 0;
  return 1;
}

/*
  returns
    0: not pressed
    1: pressed
    2: error
*/
uint8_t isPressed(uint8_t raw, uint8_t cal_untouched, uint8_t cal0, uint8_t cal1)
{
  if ( cal0 < cal1 )
  {
    if ( cal_untouched > cal1 )
    {
      return is_pressed_sub(raw, cal_untouched, cal1 );
    }
    else if ( cal_untouched < cal0 )
    {      
      return is_pressed_sub(raw, cal_untouched, cal0 );
    }
    else
    {
      return 2;
    }
  }
  else
  {
    if ( cal_untouched > cal0 )
    {
      return is_pressed_sub(raw, cal_untouched, cal0 );
    }
    else if ( cal_untouched < cal1 )
    {      
      return is_pressed_sub(raw, cal_untouched, cal1 );
    }
    else
    {
      return 2;
    }
  }
}

/* map raw value to 0...range */
uint8_t mapTouchPos(uint8_t raw, uint8_t cal0, uint8_t cal1, uint8_t range)
{
  uint16_t p;
  if  ( cal0 < cal1 )
  {
    if ( raw < cal0 )
      raw = cal0;
    if ( raw > cal1 )
      raw = cal1;
    raw -= cal0;
    cal1 -= cal0;
    p = raw * range;
    p /= cal1;
  }
  else
  {
    if ( raw < cal1 )
      raw = cal1;
    if ( raw > cal0 )
      raw = cal0;
    raw -= cal1;
    cal0 -= cal1;
    p = raw * range;
    p /= cal0;
  }
  
  
  return p;
}

void getXY(void)
{
  tp_raw_x = getTouchPos(tp_right, tp_left, tp_bottom, tp_top);
  tp_x = mapTouchPos(tp_raw_x, tp_cal_x0, tp_cal_x1, 127 );
  tp_raw_y = getTouchPos(tp_top, tp_bottom, tp_left, tp_right);
  tp_y = mapTouchPos(tp_raw_y, tp_cal_y0, tp_cal_y1, 63 );
  
  is_pressed = 1;  
  if ( isPressed(tp_raw_x, tp_cal_x_untouched, tp_cal_x0, tp_cal_x1) == 0 )
    is_pressed = 0;
  if ( isPressed(tp_raw_y, tp_cal_y_untouched, tp_cal_y0, tp_cal_y1) == 0 )
    is_pressed = 0;

  tp_SetRaw(&tp, tp_raw_x, tp_raw_y);
  tp_x = tp.x.result;
  tp_y = tp.y.result;
  is_pressed = tp.x.is_pressed && tp.y.is_pressed;
  
}




void draw(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr( 0, 12, "Touch Panel");
  u8g.setPrintPos(0, 24); u8g.print((int)tp_raw_x); u8g.print(" ");u8g.print((int)tp_x);
  u8g.setPrintPos(0, 36); u8g.print((int)tp_raw_y);u8g.print(" ");u8g.print((int)tp_y);
  u8g.setPrintPos(0, 48); u8g.print((int)cnt);
  if ( is_pressed != 0 )
    u8g.print(" pressed");
  
}

void setup(void) {
  
  // flip screen, if required
  // u8g.setRot180();
  u8g.setCursorFont(u8g_font_cursor);
  u8g.setCursorStyle(32);
  
  tp_Init(&tp);
  
}

void loop(void) {
  getXY();
  if ( is_pressed != 0 )
    u8g.enableCursor();
  else
    u8g.disableCursor();
  
  u8g.setCursorPos(tp_x, 63-tp_y);
  
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(10);
  
  cnt++;
  
}

