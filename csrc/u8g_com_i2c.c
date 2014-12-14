/*
  
  u8g_com_i2c.c

  generic i2c interface

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

//#define U8G_I2C_WITH_NO_ACK

static uint8_t u8g_i2c_err_code;
static uint8_t u8g_i2c_opt;		/* U8G_I2C_OPT_NO_ACK, SAM: U8G_I2C_OPT_DEV_1 */
/*
  position values
    1: start condition
    2: sla transfer
*/
static uint8_t u8g_i2c_err_pos;


void u8g_i2c_clear_error(void)
{
  u8g_i2c_err_code = U8G_I2C_ERR_NONE;
  u8g_i2c_err_pos = 0;
}

uint8_t  u8g_i2c_get_error(void)
{
  return u8g_i2c_err_code;
}

uint8_t u8g_i2c_get_err_pos(void)
{
  return u8g_i2c_err_pos;
}

static void u8g_i2c_set_error(uint8_t code, uint8_t pos)
{
  if ( u8g_i2c_err_code > 0 )
    return;
  u8g_i2c_err_code |= code;
  u8g_i2c_err_pos = pos;
}



#if defined(__AVR__)
#define U8G_ATMEGA_HW_TWI

/* remove the definition for attiny */
#if __AVR_ARCH__ == 2
#undef U8G_ATMEGA_HW_TWI
#endif
#if __AVR_ARCH__ == 25
#undef U8G_ATMEGA_HW_TWI
#endif
#endif

#if defined(U8G_ATMEGA_HW_TWI)

#include <avr/io.h>
#include <util/twi.h>



void u8g_i2c_init(uint8_t options)
{
  /*
  TWBR: bit rate register
  TWSR: status register (contains preselector bits)

  prescalar
    0		1
    1		4
    2		16
    3		64

  f = F_CPU/(16+2*TWBR*prescalar)
  
  F_CPU = 16MHz
    TWBR = 152;
    TWSR = 0;
	--> 50KHz

    TWBR = 72;
    TWSR = 0;
	--> 100KHz

    F_CPU/(2*100000)-8  --> calculate TWBR value for 100KHz
*/
  u8g_i2c_opt = options;
  TWSR = 0;
  TWBR = F_CPU/(2*100000)-8;
  u8g_i2c_clear_error();
}

uint8_t u8g_i2c_wait(uint8_t mask, uint8_t pos)
{
  volatile uint16_t cnt = 2000;	/* timout value should be > 280 for 50KHz Bus and 16 Mhz CPU, however the start condition might need longer */
  while( !(TWCR & mask) )
  {
      if ( cnt == 0 )
      {
	if ( u8g_i2c_opt & U8G_I2C_OPT_NO_ACK )
	{
	  return 1;	/* all ok */
	}
	else
	{
	  u8g_i2c_set_error(U8G_I2C_ERR_TIMEOUT, pos);
	  return 0; /* error */
	}
      }
      cnt--;
    }
  return 1;	/* all ok */
}

/* sla includes all 8 bits (with r/w bit), assums master transmit */
uint8_t u8g_i2c_start(uint8_t sla)
{
  register uint8_t status;
  
  /* send start */
  TWCR = _BV(TWINT) |  _BV(TWSTA)  |  _BV(TWEN);
   
  /* wait */
  if ( u8g_i2c_wait(_BV(TWINT), 1) == 0 )
    return 0;
  
  status = TW_STATUS;
 
  /* check status after start */  
  if ( status != TW_START && status != TW_REP_START )
  {
    u8g_i2c_set_error(U8G_I2C_ERR_BUS, 1);
    return 0;
  }

  /* set slave address */  
  TWDR = sla;
  
  /* enable sla transfer */
  TWCR = _BV(TWINT)  |  _BV(TWEN);

  /* wait */
  if ( u8g_i2c_wait(_BV(TWINT), 2) == 0 )
    return 0;

  if ( u8g_i2c_opt & U8G_I2C_OPT_NO_ACK )
  {
    /* do not check for ACK */
  }
  else
  {
    status = TW_STATUS;
    /* check status after sla */  
    if ( status != TW_MT_SLA_ACK )
    {
      u8g_i2c_set_error(U8G_I2C_ERR_BUS, 2);
      return 0;
    }
  }

   return 1;
}

uint8_t u8g_i2c_send_byte(uint8_t data)
{
  register uint8_t status;
  TWDR = data;
  TWCR = _BV(TWINT)  |  _BV(TWEN);
  if ( u8g_i2c_wait(_BV(TWINT), 3) == 0 )
    return 0;
    
  if ( u8g_i2c_opt & U8G_I2C_OPT_NO_ACK )
  {
    /* do not check for ACK */
  }
  else
  {
    status = TW_STATUS;  
    if ( status != TW_MT_DATA_ACK )
    {
      u8g_i2c_set_error(U8G_I2C_ERR_BUS, 3);
      return 0;
    }
  }

  return 1;  
}

void u8g_i2c_stop(void)
{
  /* write stop */
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);

  /* no error is checked for the stop condition */  
  u8g_i2c_wait(_BV(TWSTO), 4);
  
}

/*
void twi_send(uint8_t adr, uint8_t data1, uint8_t data2)
{
  u8g_i2c_start(adr<<1);
  u8g_i2c_send_byte(data1);
  u8g_i2c_send_byte(data2);
  u8g_i2c_stop();
}
*/

#elif defined(ARDUINO) && defined(__SAM3X8E__)
/* Arduino Due */
#include "sam.h"

/*
TWI0 TWCK0 PA18 A			DUE PCB: SCL1
TWI0 TWD0 PA17 A			DUE PCB: SDA1 
TWI1 TWCK1 PB13 A			DUE PCB: SCL 21
TWI1 TWD1 PB12 A			DUE PCB: SDA 20
*/


void u8g_i2c_init(uint8_t options)
{
  u8g_i2c_opt = options;
  u8g_i2c_clear_error();
  if ( u8g_i2c_opt & U8G_I2C_OPT_DEV_1 )
  {
    pmc_enable_periph_clk(ID_TWI1);
  }
  else
  {    
    pmc_enable_periph_clk(ID_TWI0);
  }
}

/*
uint8_t u8g_i2c_wait(uint8_t mask, uint8_t pos)
{
  return 1;
}
*/

uint8_t u8g_i2c_start(uint8_t sla)
{  
  Twi* TWI = TWI0;
  
  if ( u8g_i2c_opt & U8G_I2C_OPT_DEV_1 )
  {
    TWI=TWI1;
    REG_PIOA_PDR = PIO_PB12A_TWD1 | PIO_PB13A_TWCK1;
  }
  else
  {    
    REG_PIOA_PDR = PIO_PA17A_TWD0 | PIO_PA18A_TWCK0;
  }

  /* TWI reset */
  TWI->TWI_CR = TWI_CR_SWRST ;

  /* TWI Slave Mode Disabled, TWI Master Mode Disabled. */
  TWI->TWI_CR = TWI_CR_SVDIS ;
  TWI->TWI_CR = TWI_CR_MSDIS ;


  /*
    Frequenzy setup
    Due: 84000 KHz
    i2c:     100 KHz
    CKDIV = 3
    period = 105 
    --> 105*2^3 = 840
    CLDIV = 53
    CHDIV = 53
  */
  TWI->TWI_CWGR = (53) | (53<<8) | (4<<16);

  /* Set master mode */
  TWI->TWI_CR = TWI_CR_MSEN;

  /* setup master for write operation: do not set TWI_MMR_MREAD */
  TWI->TWI_MMR = TWI_MMR_DADR(sla);
  

  return 1;
}

uint8_t u8g_i2c_send_byte(uint8_t data)
{
  uint32_t sr;
  volatile uint32_t cnt = 0;
  
  Twi* TWI = TWI0;
  
  if ( u8g_i2c_opt & U8G_I2C_OPT_DEV_1 )
  {
    TWI=TWI1;
  }
  
  //u8g_i2c_opt & U8G_I2C_OPT_NO_ACK
  TWI->TWI_THR = data;
  
  for(;;)
  {
    sr = TWI->TWI_SR;
    if ( (sr & TWI_SR_TXRDY) != 0 )
      break;
    /*
    if ( (sr & TWI_SR_NACK) != 0 )
      break;
    cnt++;
    if ( cnt > 10000UL )
      break;
      */
  }
  
  return 1;
}

void u8g_i2c_stop(void)
{
  Twi* TWI = TWI0;
  
  if ( u8g_i2c_opt & U8G_I2C_OPT_DEV_1 )
  {
    TWI=TWI1;
  }
  /* the stop condition would require to send one more byte */
  /* not sure how to deal with this */
  
}


#elif defined(U8G_RASPBERRY_PI)

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define I2C_SLA         0x3c

static int fd=-1;
static uint8_t i2cMode = 0;

void u8g_i2c_init(uint8_t options) {
   u8g_i2c_clear_error();
   u8g_i2c_opt = options;

   if (wiringPiSetup() == -1) {
      printf("wiringPi-Error\n");
      exit(1);
   }

   fd = wiringPiI2CSetup(I2C_SLA);
   if (fd < 0) {
      printf ("Unable to open I2C device 0: %s\n", strerror (errno)) ;
      exit (1) ;
   }
   //u8g_SetPIOutput(u8g, U8G_PI_RESET);
   //u8g_SetPIOutput(u8g, U8G_PI_A0);
}
uint8_t u8g_i2c_start(uint8_t sla) {
   u8g_i2c_send_mode(0);

   return 1;
}

void u8g_i2c_stop(void) {
}

uint8_t u8g_i2c_send_mode(uint8_t mode) {
   i2cMode = mode;
} 

uint8_t u8g_i2c_send_byte(uint8_t data) {
   wiringPiI2CWriteReg8(fd, i2cMode, data);

   return 1;
}

uint8_t u8g_i2c_wait(uint8_t mask, uint8_t pos)
{
  return 1;
}

#else

/* empty interface */

void u8g_i2c_init(uint8_t options)
{
  u8g_i2c_clear_error();
}

uint8_t u8g_i2c_wait(uint8_t mask, uint8_t pos)
{
  return 1;
}

uint8_t u8g_i2c_start(uint8_t sla)
{
  return 1;
}
uint8_t u8g_i2c_send_byte(uint8_t data)
{
  return 1;
}

void u8g_i2c_stop(void)
{
}


#endif

