/*
  
  u8g_arduino_parallel.c

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


#if  defined(ARDUINO)

#if ARDUINO < 100 
#include <WProgram.h> 
#else 
#include <Arduino.h> 
#endif


#define PIN_D0 8
#define PIN_D1 9
#define PIN_D2 10
#define PIN_D3 11
#define PIN_D4 4
#define PIN_D5 5
#define PIN_D6 6
#define PIN_D7 7

#define PIN_CS1 14
#define PIN_CS2 15
#define PIN_RW 16
#define PIN_DI 17
#define PIN_EN 18

//#define PIN_RESET





static void u8g_com_arduino_parallel_init(void)
{
  pinMode(PIN_D0, OUTPUT);
  digitalWrite(PIN_D0, LOW);
  pinMode(PIN_D1, OUTPUT);
  digitalWrite(PIN_D1, LOW);
  pinMode(PIN_D2, OUTPUT);
  digitalWrite(PIN_D2, LOW);
  pinMode(PIN_D3, OUTPUT);
  digitalWrite(PIN_D3, LOW);
  pinMode(PIN_D4, OUTPUT);
  digitalWrite(PIN_D4, LOW);
  pinMode(PIN_D5, OUTPUT);
  digitalWrite(PIN_D5, LOW);
  pinMode(PIN_D6, OUTPUT);
  digitalWrite(PIN_D6, LOW);
  pinMode(PIN_D7, OUTPUT);
  digitalWrite(PIN_D7, LOW);
  
  pinMode(PIN_EN, OUTPUT);
  digitalWrite(PIN_EN, LOW);

  pinMode(PIN_DI, OUTPUT);
  digitalWrite(PIN_DI, HIGH);

  pinMode(PIN_RW, OUTPUT);
  digitalWrite(PIN_RW, LOW);

  pinMode(PIN_CS1, OUTPUT);
  digitalWrite(PIN_CS1, HIGH);
  pinMode(PIN_CS2, OUTPUT);
  digitalWrite(PIN_CS2, HIGH);
}




void u8g_com_arduino_parallel_write(uint8_t val)
{
  digitalWrite(PIN_D0, val&1);
  val >>= 1;
  digitalWrite(PIN_D1, val&1);
  val >>= 1;
  digitalWrite(PIN_D2, val&1);
  val >>= 1;
  digitalWrite(PIN_D3, val&1);
  val >>= 1;
  digitalWrite(PIN_D4, val&1);
  val >>= 1;
  digitalWrite(PIN_D5, val&1);
  val >>= 1;
  digitalWrite(PIN_D6, val&1);
  val >>= 1;
  digitalWrite(PIN_D7, val&1);
  
  /* EN cycle time must be 1 micro second, digitalWrite is slow enough to do this */
  digitalWrite(PIN_EN, HIGH);
  digitalWrite(PIN_EN, LOW);
}


uint8_t u8g_com_arduino_parallel_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_INIT:
      u8g_com_arduino_parallel_init();
      break;
    
    case U8G_COM_MSG_STOP:
      break;

    case U8G_COM_MSG_CHIP_SELECT:
      if ( arg_val == 0 )
      {
        /* disable */
        digitalWrite(PIN_CS1, HIGH);
        digitalWrite(PIN_CS2, HIGH);
      }
      else if ( arg_val == 1 )
      {
        /* enable */
        digitalWrite(PIN_CS1, LOW);
        digitalWrite(PIN_CS2, HIGH);  
      }
      else if ( arg_val == 2 )
      {
        /* enable */
        digitalWrite(PIN_CS1, HIGH);
        digitalWrite(PIN_CS2, LOW);  
      }
      else
      {
        /* enable */
        digitalWrite(PIN_CS1, LOW);
        digitalWrite(PIN_CS2, LOW);  
      }
      break;

    case U8G_COM_MSG_WRITE_BYTE:
      u8g_com_arduino_parallel_write(arg_val);
      break;
    case U8G_COM_MSG_WRITE_SEQ:
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
          u8g_com_arduino_parallel_write(*ptr++);
          arg_val--;
        }
      }
      break;
    case U8G_COM_MSG_WRITE_SEQ_P:
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
          u8g_com_arduino_parallel_write(u8g_pgm_read(ptr));
          ptr++;
          arg_val--;
        }
      }
      break;
    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      digitalWrite(PIN_DI, arg_val);
      break;
  }
  return 1;
}

#else


uint8_t u8g_com_arduino_parallel_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  return 1;
}

#endif /* ARDUINO */

