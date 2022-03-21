/*

  Chess.pde
  
  Little Rook Chess

  >>> Before compiling: Please remove comment from the constructor of the 
  >>> connected graphics display (see below).
  
  Universal 8bit Graphics Library, https://github.com/olikraus/u8glib/
  
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


#include "u8g_dogm128_api.h"


// DOGS102 shield configuration values
//uint8_t uiKeyPrev = 2;
//uint8_t uiKeyNext = 4;
//uint8_t uiKeySelect = 5;
//uint8_t uiKeyBack = 3;

// DOGM128-Shield	 configuration values
// DOGXL60-Shield configuration values
uint8_t uiKeyPrev = 7;
uint8_t uiKeyNext = 3;
uint8_t uiKeySelect = 2;
uint8_t uiKeyBack = 8;

uint8_t uiKeyCodeFirst = CHESS_KEY_NONE;
uint8_t uiKeyCodeSecond = CHESS_KEY_NONE;
uint8_t uiKeyCode = CHESS_KEY_NONE;


//int a0Pin = PIN_A0_DEFAULT;      // address line a0 for the dogm module
//Dogm dogm(a0Pin);

void uiSetup(void) {
  // configure input keys 
#if defined(ARDUINO)
  pinMode(uiKeyPrev, INPUT);           // set pin to input
  digitalWrite(uiKeyPrev, HIGH);       // turn on pullup resistors
  pinMode(uiKeyNext, INPUT);           // set pin to input
  digitalWrite(uiKeyNext, HIGH);       // turn on pullup resistors
  pinMode(uiKeySelect, INPUT);           // set pin to input
  digitalWrite(uiKeySelect, HIGH);       // turn on pullup resistors
  pinMode(uiKeyBack, INPUT);           // set pin to input
  digitalWrite(uiKeyBack, HIGH);       // turn on pullup resistors
#endif
}

void uiStep(void)
{
  uiKeyCodeSecond = uiKeyCodeFirst;
#if defined(ARDUINO)
  if ( digitalRead(uiKeyPrev) == LOW )
    uiKeyCodeFirst = CHESS_KEY_PREV;
  else if ( digitalRead(uiKeyNext) == LOW )
    uiKeyCodeFirst = CHESS_KEY_NEXT;
  else if ( digitalRead(uiKeySelect) == LOW )
    uiKeyCodeFirst = CHESS_KEY_SELECT;
  else if ( digitalRead(uiKeyBack) == LOW )
    uiKeyCodeFirst = CHESS_KEY_BACK;
  else
#endif
    uiKeyCodeFirst = CHESS_KEY_NONE;

  if ( uiKeyCodeSecond == uiKeyCodeFirst )
    uiKeyCode = uiKeyCodeFirst;
  else
    uiKeyCode = CHESS_KEY_NONE;
}


void setup() {
  //u8g_InitHWSPIDogm128API(&u8g_dev_uc1701_dogs102_hw_spi, 10, 9, U8G_PIN_NONE);
  //u8g_InitSPIDogm128API(&u8g_dev_uc1701_dogs102_sw_spi, 13, 11, 10, 9, U8G_PIN_NONE);
  //u8g_InitSPIDogm128API(&u8g_dev_st7920_192x32_sw_spi, 18, 16, 17, U8G_PIN_NONE, U8G_PIN_NONE);
  //u8g_InitSPIDogm128API(&u8g_dev_st7920_128x64_sw_spi, 18, 16, 17, U8G_PIN_NONE, U8G_PIN_NONE);
  u8g_InitSPIDogm128API(&u8g_dev_st7565_dogm128_hw_spi, 13, 11, 10, 9, U8G_PIN_NONE);

  //u8g_SetDogmRot180();
  uiSetup();
  chess_Init(&u8g_dogm128_obj, 0);
}

void loop() {  
  uint8_t keyCode = CHESS_KEY_NONE;
  
  dog_StartPage();
  do {
    chess_Draw();
    uiStep();
    if ( uiKeyCode != CHESS_KEY_NONE )
      keyCode = uiKeyCode;
  } while( dog_NextPage() );
  
  u8g_Delay(10);
  chess_Step(keyCode);
  uiStep();
  keyCode = uiKeyCode;
}


