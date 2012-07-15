/*
  
  u8g_com_arduino_ssd_i2c.c

  com interface for arduino (atmega) and the SSDxxxx chip (SOLOMON) variant 
  I2C protocol 

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
  
  Special pin usage:
    U8G_PI_A0_STATE	used to store the last value of the command/data register selection
    U8G_PI_SCL		clock line
    U8G_PI_SDA		data line
    U8G_PI_RESET		reset line (optional)

  Protocol:
    SLA, Cmd/Data Selection, Arguments
    The command/data register is selected by a special instruction byte, which is sent after SLA
*/

#include "u8g.h"

#define I2C_SLA		(0x3c*2)
#define I2C_CMD_MODE	0x080
#define I2C_DATA_MODE	0x040



uint8_t u8g_com_arduino_ssd_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_INIT:
      //u8g_com_arduino_digital_write(u8g, U8G_PI_SCL, HIGH);
      //u8g_com_arduino_digital_write(u8g, U8G_PI_SDA, HIGH);
      u8g->pin_list[U8G_PI_A0_STATE] = 0;       /* inital RS state: unknown mode */
      break;
    
    case U8G_COM_MSG_STOP:
      break;

    case U8G_COM_MSG_RESET:
      /* reset must be ignored by I2C */
      /*
	reason: at the moment most init sequences are like this
	  init a0 line
	  exec reset
	  chip enable
    
	  this sequence would break the meachanism below where A0 command sends I2C START and SLA
          for I2C:
	    init a0 line  --> send START & SLA
	    exec reset  --> ignored
	    chip enable   --> skipped
    
      */
    
      /* u8g_com_arduino_digital_write(u8g, U8G_PI_RESET, arg_val); */
      break;
      
    case U8G_COM_MSG_CHIP_SELECT:
      if ( arg_val == 0 )
      {
        /* disable chip, send stop condition */
	u8g_i2c_stop();
      }
      else
      {
        /* enable, do nothing: the A0 selection will trigger the i2c start */
      }
      break;

    case U8G_COM_MSG_WRITE_BYTE:
      u8g_i2c_send_byte(arg_val);
      break;
    
    case U8G_COM_MSG_WRITE_SEQ:
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
	  if ( u8g_i2c_send_byte(*ptr++) == 0 )
	    return 0;
          arg_val--;
        }
      }
      break;

    case U8G_COM_MSG_WRITE_SEQ_P:
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
	  if ( u8g_i2c_send_byte(u8g_pgm_read(ptr)) == 0 )
	    return 0;
          ptr++;
          arg_val--;
        }
      }
      break;
      
    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      /* setup bus, might be a repeated start */
      if ( u8g_i2c_start(I2C_SLA) == 0 )
	return 0;
      if ( arg_val == 0 )
      {
	if ( u8g_i2c_send_byte(I2C_CMD_MODE) == 0 )
	  return 0;
      }
      else
      {
	if ( u8g_i2c_send_byte(I2C_DATA_MODE) == 0 )
	  return 0;
      }
      break;
  }
  return 1;
}
