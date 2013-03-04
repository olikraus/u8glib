/*

  SpaceTrash.pde
  
  Demo Game

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


#include "u8g_dogm128_api.h"

u8g_t u8g;

// frames per second
unsigned long next_sec_time;
uint8_t fps, frame_cnt;

// generic configuration values
uint8_t uiIncrement = 2;

// DOGS102 configuration values
uint8_t uiKeyUpPin = 5;
uint8_t uiKeyDownPin = 3;
uint8_t uiKeyFirePin = 4;

// DOGM132 configuration values
uint8_t uiKeyUpPin2 = 7;
uint8_t uiKeyDownPin2 = 3;
uint8_t uiKeyFirePin2 = 2;

// output values
uint8_t shipLocation = 127;
uint8_t isFire = 0;

// setup the user interface
void uiSetup(void) {
  // configure input keys 
  
  pinMode(uiKeyUpPin, INPUT);           // set pin to input
  digitalWrite(uiKeyUpPin, HIGH);       // turn on pullup resistors
  pinMode(uiKeyDownPin, INPUT);           // set pin to input
  digitalWrite(uiKeyDownPin, HIGH);       // turn on pullup resistors
  pinMode(uiKeyFirePin, INPUT);           // set pin to input
  digitalWrite(uiKeyFirePin, HIGH);       // turn on pullup resistors

  pinMode(uiKeyUpPin2, INPUT);           // set pin to input
  digitalWrite(uiKeyUpPin2, HIGH);       // turn on pullup resistors
  pinMode(uiKeyDownPin2, INPUT);           // set pin to input
  digitalWrite(uiKeyDownPin2, HIGH);       // turn on pullup resistors
  pinMode(uiKeyFirePin2, INPUT);           // set pin to input
  digitalWrite(uiKeyFirePin2, HIGH);       // turn on pullup resistors
  
  
  // assign some (more or less) useful values to the output variables
  shipLocation = 127;
}

// calculate new output values
void uiStep(void) {
  if ( digitalRead(uiKeyUpPin) == LOW || digitalRead(uiKeyUpPin2) == LOW )
    if ( shipLocation <= 255 -  uiIncrement )
      shipLocation += uiIncrement;
  if ( digitalRead(uiKeyDownPin) == LOW || digitalRead(uiKeyDownPin2) == LOW )
    if ( shipLocation >= 0+  uiIncrement )
      shipLocation -= uiIncrement;
  isFire = 0;
  if ( digitalRead(uiKeyFirePin) == LOW || digitalRead(uiKeyFirePin2) == LOW )
    isFire = 1;
}


void setup(void)
{
  //u8g_InitDogm128API(&u8g_dev_uc1701_dogs102_sw_spi);

  /*
#define PIN_SCK 13
#define PIN_MISO  12
#define PIN_MOSI 11
#define PIN_CS 10
#define PIN_A0 9
#define PIN_RST 8
  */

  u8g_InitHWSPIDogm128API(&u8g_dev_uc1701_dogs102_hw_spi, 10, 9, U8G_PIN_NONE);
  //u8g_InitSPIDogm128API(&u8g_dev_uc1701_dogs102_sw_spi, 13, 11, 10, 9, U8G_PIN_NONE);
  //u8g_InitSPIDogm128API(&u8g_dev_st7920_192x32_sw_spi, 18, 16, 17, U8G_PIN_NONE, U8G_PIN_NONE);
  //u8g_InitSPIDogm128API(&u8g_dev_st7920_128x64_sw_spi, 18, 16, 17, U8G_PIN_NONE, U8G_PIN_NONE);
  //u8g_InitSPIDogm128API(&u8g_dev_st7565_dogm128_hw_spi, 13, 11, 10, 9, U8G_PIN_NONE);

  u8g_SetDogmRot180();
  
  uiSetup();
  next_sec_time = millis() + 1000UL;
  fps = 0;
  frame_cnt = 0;
   
}

void loop(void)
{
  dog_StartPage();
  do
  {
    st_Draw(fps);
  } while( dog_NextPage() );
  
  uiStep();
  st_Step(shipLocation, 0, isFire);

  frame_cnt++;
  if ( next_sec_time < millis() )
  {
    fps = frame_cnt;
    frame_cnt = 0;
    next_sec_time = millis() + 1000UL;
  }
  
}

