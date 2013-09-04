/*
  
  u8g_lpc11xx.h
  
  Header file for u8g lpc11xx utility procedures 

  Universal 8bit Graphics Library
  
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


#ifndef _U8G_LPC11XX_H
#define _U8G_LPC11XX_H

#include "LPC11xx.h"
#include "u8g.h"

/* system helper procedures */
void init_system_clock(void);	/* optional: can be called from init code */

void delay_system_ticks(uint32_t sys_ticks);	
void delay_micro_seconds(uint32_t us);


#define PIN(base,bit) ((base)*16+(bit))
void set_gpio_mode(uint16_t pin, uint8_t is_output, uint8_t is_pullup) U8G_NOINLINE;
void set_gpio_level(uint16_t pin, uint8_t level) U8G_NOINLINE;
uint8_t get_gpio_level(uint16_t pin) U8G_NOINLINE;

void spi_init(uint32_t ns) U8G_NOINLINE;
void spi_out(uint8_t data);
uint8_t u8g_com_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);

#endif


