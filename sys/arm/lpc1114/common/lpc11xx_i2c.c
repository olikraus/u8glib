
#include <stdint.h>
#include "u8g_arm.h"


#define I2C_TIMEOUT_LIMIT 20000

#define I2C_STATE_NONE	0
#define I2C_STATE_ERROR	1
#define I2C_STATE_MT_GENERATE_START 10
#define I2C_STATE_MT_WAIT_START 11
#define I2C_STATE_MT_WAIT_SLA 12
#define I2C_STATE_MT_WAIT_DATA 13

#define I2C_STATE_MR_GENERATE_START 20
#define I2C_STATE_MR_WAIT_START 21
#define I2C_STATE_MR_WAIT_SLA 22
#define I2C_STATE_MR_WAIT_DATA 23

void i2c_hw_init(void)
{
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	/* enable IOCON clock */
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<5;	/* enable clock for I2C sub system */
  // LPC_SYSCON->PRESETCTRL |= 1;		/* deassert I2C (bug?) */
  LPC_SYSCON->PRESETCTRL |= 2;		/* deassert I2C */
  LPC_IOCON->PIO0_4 = 0x01;			/* I2C mode */
  LPC_IOCON->PIO0_5 = 0x01;			/* I2C mode */
  LPC_I2C->CONSET = 1<<6;		/* enable I2EN */
  LPC_I2C->SCLL = 2500;
  LPC_I2C->SCLH = 2500;
}

void i2c_clear_error(i2c_struct *i2c)
{
  i2c->err_code = I2C_ERR_NONE;
  i2c->err_state = I2C_STATE_NONE;
  i2c->err_hw_stat = 0x0ff;
}

static void _i2c_error_sub(i2c_struct *i2c)
{
  i2c->err_state = i2c->state;
  i2c->err_hw_stat = LPC_I2C->STAT;
  LPC_I2C->CONCLR = 0x004;		/* clear AA bit */
  LPC_I2C->CONCLR = 0x020;		/* clear STA bit */
  LPC_I2C->CONSET = 0x010;		/* set STO flag */
  LPC_I2C->CONCLR = 0x008;		/* clear SI bit */ 
  i2c->state = I2C_STATE_ERROR;
}

void i2c_set_bus_error(i2c_struct *i2c)
{
  i2c->err_code = I2C_ERR_BUS;  
  _i2c_error_sub(i2c);
}

void i2c_set_timeout_error(i2c_struct *i2c)
{
  i2c->err_code = I2C_ERR_TIMEOUT;  
  _i2c_error_sub(i2c);
}

static void i2c_step(i2c_struct *i2c)
{
  uint32_t stat = LPC_I2C->STAT;
  switch(i2c->state)
  {
    case I2C_STATE_MT_GENERATE_START:
      i2c_hw_init();
      i2c_clear_error(i2c);
    
      i2c->data_pos = 0;
      i2c->timeout_cnt = 0;
      i2c->state = I2C_STATE_MT_WAIT_START;
    
      LPC_I2C->CONCLR = 0x004;		/* clear AA bit */ 
      LPC_I2C->CONSET = 0x020;		/* generate start condition */
      break;
    case I2C_STATE_MT_WAIT_START:
      if ( stat == 0x08 ||  stat == 0x10 )
      {
	/* start condition successful, transmit slave address */
	i2c->timeout_cnt = 0;
	i2c->state = I2C_STATE_MT_WAIT_SLA;
	LPC_I2C->CONCLR = 0x020;		/* clear STA bit */ 
	LPC_I2C->DAT = (i2c->adr << 1 ) | 0;
	LPC_I2C->CONCLR = 0x008;		/* clear SI bit */ 
      }
      else if ( stat == 0x020 || stat == 0x038 )
      {
	i2c_set_bus_error(i2c);
      }
      else
      {
	i2c->timeout_cnt++;
	if ( i2c->timeout_cnt > I2C_TIMEOUT_LIMIT )
	{
	  i2c_set_timeout_error(i2c);
	}
      }
      break;      
    case I2C_STATE_MT_WAIT_SLA:
    case I2C_STATE_MT_WAIT_DATA:
      if ( stat == 0x018 ||  stat == 0x028 )
      {
	/* slave available or byte has been transmitted, transmit another byte */
	if ( i2c->data_pos >= i2c->pre_data_cnt + i2c->data_cnt )
	{
	  /* generate stop condition */
	  if ( i2c->is_send_stop != 0 )
	  {
	    LPC_I2C->CONSET = 0x010;		/* set STO flag */
	  }
	  LPC_I2C->CONCLR = 0x008;		/* clear SI bit */ 
	  i2c->state = I2C_STATE_NONE;
	}
	else
	{
	  if ( i2c->data_pos < i2c->pre_data_cnt )
	  {
	    LPC_I2C->DAT = i2c->pre_data_buf[i2c->data_pos];
	  }
	  else
	  {
	    LPC_I2C->DAT = i2c->data_buf[i2c->data_pos-i2c->pre_data_cnt];
	  }
	  LPC_I2C->CONCLR = 0x008;		/* clear SI bit */ 
	  i2c->data_pos++;
	  i2c->timeout_cnt = 0;
	  i2c->state = I2C_STATE_MT_WAIT_DATA;
	}
      }
      else if ( stat == 0x020 || stat == 0x030 || stat == 0x038 )
      {
	i2c_set_bus_error(i2c);
      }
      else
      {
	i2c->timeout_cnt++;
	if ( i2c->timeout_cnt > I2C_TIMEOUT_LIMIT )
	{
	  i2c_set_timeout_error(i2c);
	}
      }
      break;
    case I2C_STATE_MR_GENERATE_START:
      i2c_hw_init();
      i2c_clear_error(i2c);
      i2c->data_pos = 0;
      i2c->timeout_cnt = 0;
      i2c->state = I2C_STATE_MR_WAIT_START;
      LPC_I2C->CONSET = 0x020;		/* generate start condition */
      LPC_I2C->CONCLR = 0x004;		/* clear AA bit */ 
      break;
    case I2C_STATE_MR_WAIT_START:
      if ( stat == 0x08 ||  stat == 0x10 )
      {
	/* start condition successful, transmit slave address */
	i2c->timeout_cnt = 0;
	i2c->state = I2C_STATE_MR_WAIT_SLA;
	LPC_I2C->DAT = (i2c->adr << 1 ) | 1;
	LPC_I2C->CONCLR = 0x020;		/* clear STA bit */ 
	LPC_I2C->CONCLR = 0x008;		/* clear SI bit */ 
      }
      else if ( stat == 0x020 || stat == 0x038 )
      {
	i2c_set_bus_error(i2c);
      }
      else
      {
	i2c->timeout_cnt++;
	if ( i2c->timeout_cnt > I2C_TIMEOUT_LIMIT )
	{
	  i2c_set_timeout_error(i2c);
	}
      }
      break;      
    case I2C_STATE_MR_WAIT_SLA:
    case I2C_STATE_MR_WAIT_DATA:
      if ( stat == 0x40 || stat == 0x50 || stat == 0x58 )
      {
	if ( i2c->data_pos >= i2c->data_cnt )
	{
	  if ( i2c->is_send_stop != 0 )
	  {
	    LPC_I2C->CONSET = 0x010;		/* set STO flag */
	  }
	  LPC_I2C->CONCLR = 0x008;		/* clear SI bit */ 
	  i2c->state = I2C_STATE_NONE;
	}
	else
	{
	  if ( i2c->data_pos+1 == i2c->data_cnt )
	  {
	    /* this is the last byte, do NOT send ack after this byte */
	    LPC_I2C->CONCLR = 0x004;		/* clear AA bit */ 
	  }
	  else
	  {
	    LPC_I2C->CONSET = 0x004;		/* set AA bit */ 
	  }
	  LPC_I2C->CONCLR = 0x020;		/* clear STA bit */
	  
	  if ( i2c->state != I2C_STATE_MR_WAIT_SLA )
	  {
	    i2c->data_buf[i2c->data_pos]  = LPC_I2C->DAT;
	    i2c->data_pos++;
	  }
	  i2c->state = I2C_STATE_MR_WAIT_DATA;
	  LPC_I2C->CONCLR = 0x008;		/* clear SI bit */ 
	}
      }
      else if ( stat == 0x038 || stat == 0x048 )
      {
	i2c_set_bus_error(i2c);
      }
      else
      {
	i2c->timeout_cnt++;
	if ( i2c->timeout_cnt > I2C_TIMEOUT_LIMIT )
	{
	  i2c_set_timeout_error(i2c);
	}
      }
      break;
    default:
      if ( i2c->state != I2C_STATE_ERROR )
	i2c->state = I2C_STATE_NONE;
      break;
  }
}

uint8_t i2c_do(i2c_struct *i2c)
{
  for(;;)
  {
    i2c_step(i2c);
    if ( i2c->state == I2C_STATE_NONE )
      return 1;
    if ( i2c->state == I2C_STATE_ERROR )
      return 0;
  }
}

/*

  uint8_t i2c_send_data(i2c_struct *i2c, uint8_t adr, uint32_t cnt, uint8_t *buf, uint8_t send_stop)
  
  adr
    address of the device

  cnt
    number of bytes to transmit

  buf
    pointer to buffer with the data to transmit

  send_stop
    0: does not send stop condition after successful transmit. Another transmit
	after this transmit will generate a repeated start condition
    1:	send stop codition after successful transmit.

  note: in the case of any errors, a stop condition is sent.

*/
uint8_t i2c_send_data(i2c_struct *i2c, uint8_t adr, uint32_t cnt, uint8_t *buf, uint8_t send_stop)
{
  i2c->adr = adr;
  i2c->is_send_stop = send_stop;
  i2c->pre_data_cnt = 0;
  i2c->pre_data_buf = NULL;
  i2c->data_cnt = cnt;
  i2c->data_buf = buf;
  
  i2c_clear_error(i2c);  
  i2c->state = I2C_STATE_MT_GENERATE_START;
  return i2c_do(i2c);
}

uint8_t i2c_send_pre_data(i2c_struct *i2c, uint8_t adr, uint32_t pre_cnt, uint8_t *pre_buf, uint32_t cnt, uint8_t *buf)
{
  i2c->adr = adr;
  i2c->is_send_stop = 1;
  i2c->pre_data_cnt = pre_cnt;
  i2c->pre_data_buf = pre_buf;
  i2c->data_cnt = cnt;
  i2c->data_buf = buf;
  
  i2c_clear_error(i2c);  
  i2c->state = I2C_STATE_MT_GENERATE_START;
  return i2c_do(i2c);
}

/*

  uint8_t i2c_receive_data(i2c_struct *i2c, uint8_t adr, uint32_t cnt, uint8_t *buf, uint8_t send_stop)
  
  adr
    address of the device

  cnt
    number of bytes to receive

  buf
    pointer to buffer with the data from the i2c device

  send_stop
    0: does not send stop condition after successful data receive. Another transmit/receive
	after this transmit will generate a repeated start condition
    1:	send stop codition after successful receive of data.

  note: in the case of any errors, a stop condition is sent.

*/
uint8_t i2c_receive_data(i2c_struct *i2c, uint8_t adr, uint32_t cnt, uint8_t *buf, uint8_t send_stop)
{
  i2c->adr = adr;
  i2c->is_send_stop = send_stop;
  i2c->data_cnt = cnt;
  i2c->data_buf = buf;
  i2c->pre_data_cnt = 0;
  i2c->pre_data_buf = NULL;
  i2c_clear_error(i2c);  
  i2c->state = I2C_STATE_MR_GENERATE_START;
  return i2c_do(i2c);
}
 

uint8_t i2c_send_2byte(i2c_struct *i2c, uint8_t adr, uint8_t b1, uint8_t b2, uint8_t send_stop)
{
  uint8_t buf[2];
  buf[0] = b1;
  buf[1] = b2;
  
  return i2c_send_data(i2c, adr, 2, buf, send_stop);
}

uint8_t i2c_send_3byte(i2c_struct *i2c, uint8_t adr, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t send_stop)
{
  uint8_t buf[2];
  buf[0] = b1;
  buf[1] = b2;
  buf[2] = b3;
  
  return i2c_send_data(i2c, adr, 3, buf, send_stop);
}