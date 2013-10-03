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
// IMPORTANT NOTE: The following list is incomplete. The complete list of supported 
// devices with all constructor calls is here: http://code.google.com/p/u8glib/wiki/device
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
//U8GLIB_DOGM128 u8g(13, 11, 10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_DOGM128_2X u8g(13, 11, 10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
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
//U8GLIB_HT1632_24X16 u8g(3, 2, 4);		// WR = 3, DATA = 2, CS = 4
//U8GLIB_SSD1351_128X128_332 u8g(13, 11, 8, 9, 7); // Arduino UNO: SW SPI Com: SCK = 13, MOSI = 11, CS = 8, A0 = 9, RESET = 7 (http://electronics.ilsoft.co.uk/ArduinoShield.aspx)
//U8GLIB_SSD1351_128X128_332 u8g(76, 75, 8, 9, 7); // Arduino DUE: SW SPI Com: SCK = 13, MOSI = 11, CS = 8, A0 = 9, RESET = 7 (http://electronics.ilsoft.co.uk/ArduinoShield.aspx)
//U8GLIB_SSD1351_128X128_332 u8g(8, 9, 7); // Arduino: HW SPI Com: SCK = 13, MOSI = 11, CS = 8, A0 = 9, RESET = 7 (http://electronics.ilsoft.co.uk/ArduinoShield.aspx)
//U8GLIB_SSD1351_128X128_4X_332 u8g(76, 75, 8, 9, 7); // Arduino DUE: SW SPI Com: SCK = 13, MOSI = 11, CS = 8, A0 = 9, RESET = 7 (http://electronics.ilsoft.co.uk/ArduinoShield.aspx)
//U8GLIB_SSD1351_128X128_4X_332 u8g(8, 9, 7); // Arduino : HW SPI Com: SCK = 13, MOSI = 11, CS = 8, A0 = 9, RESET = 7 (http://electronics.ilsoft.co.uk/ArduinoShield.aspx)
//U8GLIB_SSD1351_128X128_HICOLOR u8g(76, 75, 8, 9, 7); // Arduino DUE, SW SPI Com: SCK = 76, MOSI = 75, CS = 8, A0 = 9, RESET = 7 (http://electronics.ilsoft.co.uk/ArduinoShield.aspx)
//U8GLIB_SSD1351_128X128_HICOLOR u8g(8, 9, 7); // Arduino, HW SPI Com: SCK = 76, MOSI = 75, CS = 8, A0 = 9, RESET = 7 (http://electronics.ilsoft.co.uk/ArduinoShield.aspx)
//U8GLIB_SSD1351_128X128_4X_HICOLOR u8g(76, 75, 8, 9, 7); // Arduino DUE, HW SPI Com, 4x Memory: SCK = 76, MOSI = 75, CS = 8, A0 = 9, RESET = 7 (http://electronics.ilsoft.co.uk/ArduinoShield.aspx)
//U8GLIB_SSD1351_128X128_4X_HICOLOR u8g(8, 9, 7); // Arduino, HW SPI Com, 4x Memory: SCK = 76, MOSI = 75, CS = 8, A0 = 9, RESET = 7 (http://electronics.ilsoft.co.uk/ArduinoShield.aspx)
//U8GLIB_SSD1351_128X128GH_332 u8g(8, 9, 7); // Arduino, HW SPI Com: SCK = 76, MOSI = 75, CS = 8, A0 = 9, RESET = 7 (Freetronics OLED)
//U8GLIB_SSD1351_128X128GH_HICOLOR u8g(8, 9, 7); // Arduino, HW SPI Com: SCK = 76, MOSI = 75, CS = 8, A0 = 9, RESET = 7 (Freetronics OLED)

//================================================================
// Setup 4-Wire Resistive Touch Panel

uint8_t tp_left = A3;
uint8_t tp_right = A5;
uint8_t tp_top = A4;
uint8_t tp_bottom = A2;

//================================================================
// Touch Panel Code

#define TPD_OPEN 0
#define TPD_PRESSED 1
#define TPD_OPEN_TO_PRESSED 2
#define TPD_PRESSED_TO_OPEN 3

/* touch panel dimension */
struct _tpd_struct
{
  uint8_t raw;		/* input value */
  uint8_t delta;		/* delta of the last raw value */
  uint8_t curr;		/* current valid position */
  uint8_t state;		/* state machine */
  
  /* calibration values (set during init phase) */
  uint8_t start;
  uint8_t end;		
  uint8_t open;		/* value, when not touched/pressed */
  
  /* calibration values (must be predefined) */
  uint8_t mt;		/* move and open threshold */
  
  /* user values */
  uint8_t range;	/* result will have range fron 0..range  (including the value of range) */
  
  uint8_t result;	/* output value: position [0...range] */
  uint8_t is_pressed;	/* output value: pressed (=1) or not pressed (=0) */
  uint8_t is_update;	/* will be set to 1 if result or is_pressed has been updated */
};
typedef struct _tpd_struct tpd_struct;


#define TP_STATE_OPEN_DETECT 0
#define TP_STATE_OPEN_DETECT_1 1
#define TP_STATE_START_PRESS 2
#define TP_STATE_WAIT_START_OPEN 3
#define TP_STATE_END_PRESS 4
#define TP_STATE_WAIT_END_OPEN 5
#define TP_STATE_NORMAL 6

#define TP_DISPLAY_DO_NOT_TOUCH 0
#define TP_DISPLAY_PRESS_AND_RELEASE_EDGE 1
#define TP_DISPLAY_PRESS_AND_RELEASE_OPPOSITE_EDGE 2
#define TP_DISPLAY_OK 3

struct _tp_struct
{
  tpd_struct x;
  tpd_struct y;
  uint8_t state;
  uint8_t is_pressed; /* combination of x.is_pressed && y.is_pressed */
  uint8_t is_update;
};
typedef struct _tp_struct tp_struct;

tp_struct tp;


uint8_t tp_GetDisplayState(tp_struct *tp)
{
  switch(tp->state)
  {
    case TP_STATE_OPEN_DETECT:
    case TP_STATE_OPEN_DETECT_1:
      return TP_DISPLAY_DO_NOT_TOUCH;
    case TP_STATE_START_PRESS:
    case TP_STATE_WAIT_START_OPEN:
      return TP_DISPLAY_PRESS_AND_RELEASE_EDGE;
    case TP_STATE_END_PRESS:
    case TP_STATE_WAIT_END_OPEN:
      return TP_DISPLAY_PRESS_AND_RELEASE_OPPOSITE_EDGE;
    case TP_STATE_NORMAL:
    default:
      return TP_DISPLAY_OK;
  }
}


uint8_t tpd_is_active_area(tpd_struct *d)
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

static uint8_t tpd_delta(uint8_t a, uint8_t b)
{
  if ( a < b )
    return b-a;
  return a-b;
}

static void tpd_next_step(tpd_struct *d, uint8_t raw)
{
  uint8_t is_pressed;
  d->delta = tpd_delta(d->raw, raw);
  d->raw = raw;
  is_pressed = tpd_is_active_area(d);
  
  switch(d->state)
  {
    case TPD_OPEN:
      if ( is_pressed == 0 )
      {
	d->curr = d->raw;    
      }
      else
      {
	d->state = TPD_OPEN_TO_PRESSED;
      }
      break;
    case TPD_PRESSED:
      if ( is_pressed == 0 )
      {
	d->state = TPD_OPEN;
	d->curr = d->raw;
      }
      else
      {
	if ( d->delta > d->mt )
	{
	  d->state = TPD_PRESSED_TO_OPEN;
	}
	else
	{
	  /* stay in PRESSED state */
	  d->curr = d->raw;
	}
      }
      break;
    case TPD_PRESSED_TO_OPEN:
    case TPD_OPEN_TO_PRESSED:
      if ( is_pressed == 0 )
      {
	d->state = TPD_OPEN;
	d->curr = d->raw;
      }
      else
      {
	if ( d->delta > d->mt )
	{
	  /* stay in current state */
	}
	else
	{
	  d->state = TPD_PRESSED;
	  d->curr = d->raw;
	}
      }
      break;
  }
  
  if ( d->state == TPD_OPEN || d->state == TPD_OPEN_TO_PRESSED )
    is_pressed = 0;
  else
    is_pressed = 1;
  if ( d->is_pressed != is_pressed )
    d->is_update = 1;
  d->is_pressed = is_pressed;
}


static void tpd_do_calibrate(tpd_struct *d)
{
  if ( tpd_delta(d->raw, d->open) < d->mt )
    return;
  if ( d->state != TPD_PRESSED )
    return;

  if  ( d->start < d->end )
  {
    if ( d->end < d->raw )
      d->end = d->raw;
    if ( d->start > d->raw )
      d->start = d->raw;
  }
  else
  {
    if ( d->end > d->raw )
      d->end = d->raw;
    if ( d->start < d->raw )
      d->start = d->raw;
  }

}



/* map curr value to 0...range (result) */
void tpd_map_touch_position(tpd_struct *d)
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
  
  if ( d->curr <= start )
  {
    d->result = 0;
    return;
  }
  
  if ( d->curr >= end )
  {
    d->result = d->range;
    return;
  }
  
  p = d->curr;
  p -= start;
  p *= d->range;
  end -= start;
  p /= end;
  
  if ( d->result != p )
    d->is_update = 1;
  d->result = p;
}


void tp_Init(tp_struct *tp, uint8_t width, uint8_t height)
{
  tp->x.start = 0;
  tp->x.end = 0;
  tp->x.open = 0;
  tp->x.range = width-1;
  tp->x.mt = width/8;
  tp->x.state = TPD_OPEN;
  
  tp->y.start = 0;
  tp->y.end = 0;
  tp->y.open = 0;
  tp->y.range = height-1;
  tp->y.mt = height/8;
  tp->y.state = TPD_OPEN;
  
  tp->state = TP_STATE_OPEN_DETECT;
  tp->is_update = 1;
}

uint8_t tp_IsOpen(tp_struct *tp, uint8_t x, uint8_t y)
{
  if ( tpd_delta(tp->x.open, x) < tp->x.mt &&  tpd_delta(tp->y.open, y)  < tp->y.mt )
    return 1;
  return 0;
}

void tp_SetRaw(tp_struct *tp, uint8_t x, uint8_t y)
{
  switch( tp->state )
  {
    case TP_STATE_OPEN_DETECT:
      tp->x.open = x; 
      tp->y.open = y;
      tp->state = TP_STATE_OPEN_DETECT_1;
      tp->is_update = 1;
      break;
    case TP_STATE_OPEN_DETECT_1:
      if ( tpd_delta(tp->x.open, x) <= tp->x.mt &&  tpd_delta(tp->y.open, y)  <= tp->y.mt )
      {
	tp->is_update = 1;
	tp->state = TP_STATE_START_PRESS;
      }
      tp->x.open = x; 
      tp->y.open = y;
      break;
    case TP_STATE_START_PRESS:
      if ( tp_IsOpen(tp,x,y) == 0 )
      {
	if ( tpd_delta(tp->x.start, x) <= tp->x.mt &&  tpd_delta(tp->y.start, y)  <= tp->y.mt )
	{
	  tp->state = TP_STATE_WAIT_START_OPEN;
	  tp->is_update = 1;
	}
	tp->x.start = x;
	tp->y.start = y;
      }
      break;
    case TP_STATE_WAIT_START_OPEN:
      if ( tp_IsOpen(tp,x,y) != 0 )
      {      
	tp->state = TP_STATE_END_PRESS;
	tp->is_update = 1;
      }
      break;
    case TP_STATE_END_PRESS:
      if ( tp_IsOpen(tp,x,y) == 0 )
      {
	if ( tpd_delta(tp->x.start, x) > tp->x.mt &&  tpd_delta(tp->y.start, y)  > tp->y.mt )
	{
	  if ( tpd_delta(tp->x.end, x) <= tp->x.mt &&  tpd_delta(tp->y.end, y)  <= tp->y.mt )
	  {
	    tp->state = TP_STATE_WAIT_END_OPEN;
	    tp->is_update = 1;
	  }
	  tp->x.end = x;
	  tp->y.end = y;
	}
      }
      break;
    case TP_STATE_WAIT_END_OPEN:
      if ( tp_IsOpen(tp,x,y) != 0 )
      {
	tp->state = TP_STATE_NORMAL;
	tp->is_update = 1;
      }
      break;
    default:
      tpd_next_step(&(tp->x), x);
      tpd_map_touch_position(&(tp->x));
      tpd_do_calibrate(&(tp->x));
      
      tpd_next_step(&(tp->y), y);
      tpd_map_touch_position(&(tp->y));
      tpd_do_calibrate(&(tp->y));
      
      tp->is_pressed = tp->x.is_pressed && tp->y.is_pressed;
      tp->is_update = tp->x.is_update && tp->y.is_update;
      break;
  }
}


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


void updateTouchPanel(void)
{
  uint8_t tp_raw_x;
  uint8_t tp_raw_y;

  tp_raw_x = getTouchPos(tp_right, tp_left, tp_bottom, tp_top);
  tp_raw_y = getTouchPos(tp_top, tp_bottom, tp_left, tp_right);
  
  tp_SetRaw(&tp, tp_raw_x, tp_raw_y);  
}

//================================================================
// graphics output and picture loop

void center(u8g_uint_t y, const char *str)
{
  u8g_uint_t x;
  x = u8g.getWidth();
  x -= u8g.getStrWidth(str);
  x /= 2;
  u8g.drawStr(x, y, str);
}


void draw(void) {
  u8g.setFont(u8g_font_6x10);
  switch( tp_GetDisplayState(&tp) )
  {
    case TP_DISPLAY_DO_NOT_TOUCH:
      center(12, "Do Not Touch");
      break;
    case TP_DISPLAY_PRESS_AND_RELEASE_EDGE:
      /* it does not matter which edge is pressed, but later the opposite edge must be pressed */
      center( 12, "Press");
      center( 24, "Lower Left Edge");
      u8g.drawLine(0, u8g.getHeight()-1, 10, u8g.getHeight()-11);
      break;
    case TP_DISPLAY_PRESS_AND_RELEASE_OPPOSITE_EDGE:
      center( 12, "Press");
      center( 24, "Upper Right Edge");
      u8g.drawLine(u8g.getWidth()-11, 10, u8g.getWidth()-1, 0);
      break;
    case TP_DISPLAY_OK:
    default:
      center( 10, "Touch Panel");
      if ( tp.is_pressed != 0 )
      {
	u8g.setPrintPos(0, 20); u8g.print("x=");u8g.print((int)tp.x.result);
	u8g.setPrintPos(0, 30); u8g.print("y=");u8g.print((int)(u8g.getHeight()-tp.y.result-1));
      }
      break;
  }

  
}

void setup(void) {
  
  // flip screen, if required
  // u8g.setRot180();
  u8g.setCursorFont(u8g_font_cursor);
  u8g.setCursorStyle(32);
  
  tp_Init(&tp, u8g.getWidth(), u8g.getHeight());
  
}

void loop(void) {
  
  // update touch panel and handle return values
  updateTouchPanel();
  
  if ( tp.is_pressed != 0 )
    u8g.enableCursor();
  else
    u8g.disableCursor();
  
  u8g.setCursorPos(tp.x.result, u8g.getHeight()-tp.y.result-1);
  
  // picture loop
  if ( tp.is_update )
  {
    tp.is_update = 0;
    u8g.firstPage();  
    do {
      draw();
    } while( u8g.nextPage() );
  }
  
}

