/*
  
  u8g_arm.h
  
  Header file for u8g LPC11xx utility procedures 

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


#ifndef _U8G_ARM_H
#define _U8G_ARM_H

#include "LPC11xx.h"
#include "u8g.h"

/* system helper procedures */
void init_system_clock(void);	/* optional: can be called from init code */

void delay_system_ticks(uint32_t sys_ticks);	
void delay_micro_seconds(uint32_t us);


#define PIN(base,bit) ((base)*16+(bit))
#define DEFAULT_KEY PIN(0,1)

void set_gpio_mode(uint16_t pin, uint8_t is_output, uint8_t is_pullup) U8G_NOINLINE;
void set_gpio_level(uint16_t pin, uint8_t level) U8G_NOINLINE;
uint8_t get_gpio_level(uint16_t pin) U8G_NOINLINE;

void spi_init(uint32_t ns) U8G_NOINLINE;
void spi_out(uint8_t data);

extern uint16_t u8g_pin_a0;
extern uint16_t u8g_pin_cs;
extern uint16_t u8g_pin_rst;
uint8_t u8g_com_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);

/* lpc11xx_i2c.c */
struct _i2c_struct
{  
  /* INPUT */
  uint8_t adr;			/* slave address */
  /* the following value should be set to 1 in most cases */
  /* however, a second transmit follows, then this might be set to 0 */
  uint8_t is_send_stop;
  uint32_t pre_data_cnt;
  uint8_t *pre_data_buf;
  uint32_t data_cnt;		/* number of bytes to transfer */
  uint8_t *data_buf;		/* pointer to the data */

  /* INTERNAL VARIABLES */
  uint32_t data_pos;		/* current byte to transmit */
  uint32_t timeout_cnt;	/* timeout counter */
  uint8_t err_hw_stat;	/* last hw stat, that was seen */
  uint8_t err_state;		/* state in which the error occured */
  uint8_t err_code;		/* set to one for bus error */
  uint8_t state;			/* internal state */
};
typedef struct _i2c_struct i2c_struct;

#define I2C_ERR_NONE 0
#define I2C_ERR_BUS 1
#define I2C_ERR_TIMEOUT 2

uint8_t i2c_send_data(i2c_struct *i2c, uint8_t adr, uint32_t cnt, uint8_t *buf, uint8_t send_stop);
uint8_t i2c_send_pre_data(i2c_struct *i2c, uint8_t adr, uint32_t pre_cnt, uint8_t *pre_buf, uint32_t cnt, uint8_t *buf);
uint8_t i2c_receive_data(i2c_struct *i2c, uint8_t adr, uint32_t cnt, uint8_t *buf, uint8_t send_stop);
uint8_t i2c_send_2byte(i2c_struct *i2c, uint8_t adr, uint8_t b1, uint8_t b2, uint8_t send_stop);
uint8_t i2c_send_3byte(i2c_struct *i2c, uint8_t adr, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t send_stop);

#endif


