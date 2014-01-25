#include "U8glib.h"

// setup u8g object, please remove comment from one of the following constructor calls
// IMPORTANT NOTE: The following list is incomplete. The complete list of supported 
// devices with all constructor calls is here: http://code.google.com/p/u8glib/wiki/device

U8GLIB_DOGM128 u8g(13, 11, 10, 9);		// SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9

//HW DIP 2&4 ON 1&3 OFF
//U8GLIB_DOGM128_2X u8g(40, 38, 39);
//U8GLIB_DOGM128 u8g(40, 38, 39);
//SW DIP 1&3 ON 2&4 OFF
//U8GLIB_DOGM128 u8g(33, 34, 40, 38, 39);
//U8GLIB_DOGM128_2X u8g(33, 34, 40, 38, 39);


#include "master.xbm" 
//MASTER.XBM: this works perfectly, the master.xbm includes the correct resolutions multiplied by 8
//Inside you'll find the defines for the resolution and the databits naming
#include "BaseBody.xbm"
//In this file, I didn't renamed the names of the array and the resolutin defines, soI kept pic_width, pic_height and pic_bits
#include "BaseBody64.xbm"
//This is the same picture of BaseBody but resized with an H multiple of 8, so it works. 
//IMPORTANT, I don't have one now but I'll provide you ASAP: the BMP files begin with the vertical column filled with a black pixel in case of photoshop.
//IF i don't shift the image in the canvas to the right of one pixel, the first column become the last, keeping the image integer in the overall but not for the first column.

uint8_t draw_state = 0;

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}



void draw(void) {
  if(draw_state == 0){
  u8g.drawXBMP( 34, 23, baseBody_width, baseBody_height, baseBody_bits);
   u8g.drawXBMP( 45, 0, baseHead_width, baseHead_height, baseHead_bits);
   delay(100);
  }
  else if(draw_state == 1){       
  u8g.drawXBMP( 34, 23, baseBody_width, baseBody_height, baseBody_bits);
   u8g.drawXBMP( 45, 0, baseHead_width, baseHead_height, headNMN0_bits); 
   delay(100);
  }
  else if(draw_state == 2){       
  u8g.drawXBMP( 34, 23, baseBody_width, baseBody_height, baseBody_bits);
   u8g.drawXBMP( 45, 0, baseHead_width, baseHead_height, headNMN1_bits);
   delay(100);
  }
  else if(draw_state == 3){    
  u8g.drawXBMP( 34, 23, baseBody_width, baseBody_height, baseBody_bits);
   u8g.drawXBMP( 45, 0, baseHead_width, baseHead_height, headNMN2_bits);
   delay(100);
  }
  else if(draw_state == 4){    
  u8g.drawXBMP( 34, 23, pic_width, pic_height, pic_bits);
   delay(100);
  }
  else if(draw_state == 5){    
  u8g.drawXBMP( 34, 23, pic2_width, pic2_height, pic2_bits);
   delay(100);
  }
  else {
  }
}

void setup(void) {
  // flip screen, if required
  //u8g.setRot180();
  pinMode(37, OUTPUT);           
  digitalWrite(37, LOW); 
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw_state = 4;
    draw();
  } while( u8g.nextPage() );
  // increase the state
  draw_state++;
  if ( draw_state >= 6 )
    draw_state = 0;
   
  // rebuild the picture after some delay
   delay(300);
  /* delay(50);
  for(int blikk = 0; blikk <= 2; blikk +=1){
  digitalWrite(37, HIGH);
  delay(25);
  digitalWrite(37, LOW);
  delay(25);
  } */
}

