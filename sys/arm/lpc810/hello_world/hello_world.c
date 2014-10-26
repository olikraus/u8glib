/*

  hello_world.c
  
  Universal 8bit Graphics Library
  
  Copyright (c) 2014, olikraus@gmail.com
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



#include "chip.h"
#include "u8g.h"



#define SYS_CORE_CLOCK 12000000UL
#define SYS_TICK_PERIOD_IN_MS 50



/*=======================================================================*/
/* delay */

void delay_system_ticks(uint32_t sys_ticks);		/* from lpc81x_system.c */

/*
  Delay by the provided number of micro seconds.
  Limitation: "us" * System-Freq in MHz must now overflow in 32 bit.
  Values between 0 and 1.000.000 (1 second) are ok.
*/
void delay_micro_seconds(uint32_t us)
{
  uint32_t sys_ticks;

  sys_ticks = SYS_CORE_CLOCK / 1000000UL;
  sys_ticks *= us;
  delay_system_ticks(sys_ticks);  
}


/*=======================================================================*/
/* system procedures and sys tick master task */

volatile uint32_t sys_tick_irq_cnt=0;


void __attribute__ ((interrupt)) SysTick_Handler(void)
{
  sys_tick_irq_cnt++;
  
}


/*=======================================================================*/
/* u8g delay procedures */

void u8g_Delay(uint16_t val)
{
    
  delay_micro_seconds(1000UL*(uint32_t)val);
}

void u8g_MicroDelay(void)
{
  delay_micro_seconds(1);
}

void u8g_10MicroDelay(void)
{
  delay_micro_seconds(10);
}

/*=======================================================================*/
/* generic  i2c (http://en.wikipedia.org/wiki/I%C2%B2C) */
/* SCL: 0_3 */
/* SDA: 0_0 */


uint8_t i2c_started = 0;

void i2c_delay(void)
{
  /* should be at least 4 */
  /* should be 5 for 100KHz transfer speed */
  
  delay_micro_seconds(5);
}

uint8_t i2c_read_scl(void)
{
  Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 3);
  return Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, 0, 3);
}

void i2c_clear_scl(void)
{
  Chip_IOCON_PinEnableOpenDrainMode(LPC_IOCON, IOCON_PIO3);	
  //Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 3);
  Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 3);
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 3);
}

uint8_t i2c_read_sda(void)
{
  Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 0);
  return Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, 0, 0);
  
}

void i2c_clear_sda(void)
{
  Chip_IOCON_PinEnableOpenDrainMode(LPC_IOCON, IOCON_PIO0);	
  //Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 0);
  Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 0);
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 0);
}

void i2c_start(void) 
{
  if ( i2c_started != 0 ) 
  { 
    /* if already started: do restart */
    i2c_read_sda();	/* SDA = 1 */
    i2c_delay();
    i2c_read_scl();
    /* clock stretching is not done */
    /* while (i2c_read_scl() == 0)   ; */
    i2c_delay();		/* another delay, just to be sure... */
  }
  i2c_read_sda();
  /*
  if (i2c_read_sda() == 0) 
  {
    // do something because arbitration is lost
  }
  */
  /* send the start condition, both lines go from 1 to 0 */
  i2c_clear_sda();
  i2c_delay();
  i2c_clear_scl();
  i2c_started = 1;
}


void i2c_stop(void)
{
  /* set SDA to 0 */
  i2c_clear_sda();  
  i2c_delay();
  
  /* now release all lines */
  i2c_read_scl();
  /* clock stretching is not done */
  /* while (i2c_read_scl() == 0)   ; */
  i2c_delay();		/* another delay, just to be sure... */
  
  /* set SDA to 1 */
  i2c_read_sda();
  /*
  if (i2c_read_sda() == 0) 
  {
    // do something because arbitration is lost
  }
  */
  i2c_delay();
  i2c_started = 0;
}

void i2c_write_bit(uint8_t val) 
{
  if (val)
    i2c_read_sda();
  else
    i2c_clear_sda();
  
  i2c_delay();
  i2c_read_scl();
  /* clock stretching is not done */
  /* while (i2c_read_scl() == 0)   ; */

  /* validation is skipped, because this will be the only master */  
  /* If SDA is high, check that nobody else is driving SDA */
  /*
  if (val && i2c_read_sda() == 0) 
  {
    arbitration_lost();
  }
  */
  i2c_delay();
  i2c_clear_scl();
}

uint8_t i2c_read_bit(void) 
{
  uint8_t val;
  /* do not drive SDA */
  i2c_read_sda();
  i2c_delay();
  i2c_read_scl();
  /* clock stretching is not done */
  /* while (i2c_read_scl() == 0)   ; */
  
  i2c_delay();	/* may not be required... */
  val = i2c_read_sda();
  i2c_delay();
  i2c_clear_scl();
  return val;
}

uint8_t i2c_write_byte(uint8_t b)
{
  uint8_t i = 8;
  do
  {
    i2c_write_bit(b & 128);
    b <<= 1;
    i--;
  } while ( i != 0 );
  /* read ack from client */
  /* 0: ack was given by client */
  /* 1: nothing happend during ack cycle */  
  return i2c_read_bit();
}

/*=======================================================================*/
/* lpc810 i2c */

/*
taken from AN11329
*/
typedef struct
{
  __IO uint32_t  CFG;			  /* 0x00 */
  __IO uint32_t  STAT;
  __IO uint32_t  INTENSET;
  __O  uint32_t  INTENCLR;
  __IO uint32_t  TIMEOUT;		/* 0x10 */
  __IO uint32_t  DIV;
  __IO uint32_t  INTSTAT;
       uint32_t  Reserved0[1];  
  __IO uint32_t  MSTCTL;			  /* 0x20 */
  __IO uint32_t  MSTTIME;
  __IO uint32_t  MSTDAT;
       uint32_t  Reserved1[5];
  __IO uint32_t  SLVCTL;			  /* 0x40 */
  __IO uint32_t  SLVDAT;
  __IO uint32_t  SLVADR0;
  __IO uint32_t  SLVADR1;
  __IO uint32_t  SLVADR2;			  /* 0x50 */
  __IO uint32_t  SLVADR3;
  __IO uint32_t  SLVQUAL0;
       uint32_t  Reserved2[9];
  __I  uint32_t  MONRXDAT;			/* 0x80 */		
} LPC_I2C_TypeDef;

#define LPC_I2C               ((LPC_I2C_TypeDef    *) LPC_I2C_BASE   )

#define  I2C_CFG_MSTEN (0x1)
#define  I2C_CFG_SLVEN (0x2)
#define  I2C_STAT_MSTPENDING (0x1)
#define  I2C_STAT_MSTSTATE (0xe)
#define  I2C_STAT_MSTST_IDLE (0x0)
#define  I2C_STAT_MSTST_RX (0x2)
              
#define  I2C_STAT_MSTST_TX (0x4)
#define  I2C_STAT_MSTST_NACK_ADDR (0x6)
#define  I2C_STAT_MSTST_NACK_TX (0x8)
#define  I2C_STAT_SLVPENDING (0x100)
#define  I2C_STAT_SLVSTATE (0x600)
#define  I2C_STAT_SLVST_ADDR (0x000)
#define  I2C_STAT_SLVST_RX (0x200)
#define  I2C_STAT_SLVST_TX (0x400)
#define  I2C_MSTCTL_MSTCONTINUE (0x1)
#define  I2C_MSTCTL_MSTSTART (0x2)
#define  I2C_MSTCTL_MSTSTOP (0x4)
#define  I2C_SLVCTL_SLVCONTINUE (0x1)
#define  I2C_SLVCTL_SLVNACK (0x2)

uint8_t __attribute__ ((noinline))  lpc81x_i2c_wait(void)
{
  volatile static unsigned long cnt;
  cnt = 0;
  while(!(LPC_I2C->STAT & I2C_STAT_MSTPENDING))
  {    
    cnt++;
    if ( cnt > 100000UL )
    {
      return 0;      
    }
  }
  return 1;
}

void lpc81x_i2c_init(uint8_t options)
{
   Chip_I2C_Init();
  
  //LPC_I2C->DIV = 30;		/* 12 MHz / 30 = 400KHz , not sure, user manual not clear */
  LPC_I2C->DIV = 30*8;		
  LPC_I2C->MSTTIME = 0;		/* Low / High = 2 clocks each, 400KHz / 4 = 100KHz */
  
  
  /* code from the lpc810 user manual */
  LPC_I2C->CFG = I2C_CFG_MSTEN;
  
  lpc81x_i2c_wait();
  
  /* I2C_STAT_MSTSTATE = 0x0e, bits 1,2 & 3 */
  /* I2C_STAT_MSTST_IDLE = 0 */
  /* result not checked, idle is assumed */
  /*
  if ((LPC_I2C->STAT & I2C_STAT_MSTSTATE) != I2C_STAT_MSTST_IDLE) 
    return 0;
  */
}

void lpc81x_i2c_deinit(uint8_t options)
{
   Chip_I2C_DeInit();
}


uint8_t lpc81x_i2c_start(uint8_t sla)
{
  LPC_I2C->MSTDAT = (sla << 1) | 0; // address and 0 for RWn bit
  LPC_I2C->MSTCTL = I2C_MSTCTL_MSTSTART; // 0x02, send start
  
  lpc81x_i2c_wait();
  
  /* I2C_STAT_MSTS_TX = 0x04 */
  /* The state is either I2C_STAT_MSTS_TX or I2C_STAT_MSTST_NACK_ADDR */
  /* For the SSD1306 it is better to ignore this */
  /*
  if((LPC_I2C->STAT & I2C_STAT_MSTSTATE) != I2C_STAT_MSTS_TX)
    return 0;
  */
  return 1;
}

uint8_t lpc81x_i2c_send_byte(uint8_t data)
{
  LPC_I2C->MSTDAT = data; // send data
  LPC_I2C->MSTCTL = I2C_MSTCTL_MSTCONTINUE; // 0x01, continue transaction
  
  lpc81x_i2c_wait();
  
  /* I2C_STAT_MSTS_TX = 0x04 */
  /* The state is either I2C_STAT_MSTS_TX or I2C_STAT_MSTST_NACK_TX */
  /* For the SSD1306 it is better to ignore this */
  /*
  if ((LPC_I2C->STAT & I2C_STAT_MSTSTATE) != I2C_STAT_MSTS_TX) 
    return 0;
  */
  return 1;
}

void lpc81x_i2c_stop(void)
{
  LPC_I2C->MSTCTL = I2C_MSTCTL_MSTSTOP; // send stop
  
  lpc81x_i2c_wait();
  
  // if((LPC_I2C->STAT & I2C_STAT_MSTSTATE) != I2C_STAT_MSTST_IDLE) abort();
}


/*=======================================================================*/
/* u8glib com callback */


#define I2C_SLA         (0x3c*2)
//#define I2C_CMD_MODE  0x080
#define I2C_CMD_MODE    0x000
#define I2C_DATA_MODE   0x040

uint8_t u8g_a0_state;
uint8_t u8g_set_a0;

static uint8_t lpc810_u8g_com_ssd_start_sequence(u8g_t *u8g)
{
  /* are we requested to set the a0 state? */
  if ( u8g_set_a0 == 0 )
    return 1;

  /* setup bus, might be a repeated start */
  if ( lpc81x_i2c_start(I2C_SLA) == 0 )
    return 0;
  if ( u8g_a0_state == 0 )
  {
    if ( lpc81x_i2c_send_byte(I2C_CMD_MODE) == 0 )
      return 0;
  }
  else
  {
    if ( lpc81x_i2c_send_byte(I2C_DATA_MODE) == 0 )
      return 0;
  }

  u8g_set_a0 = 0;
  return 1;
}

static void u8g_com_ssd_start_sequence(u8g_t *u8g)
{
  /* are we requested to set the a0 state? */
  if ( u8g_set_a0 == 0 )
    return;

  i2c_start();
  i2c_write_byte(I2C_SLA);		// address and 0 for RWn bit
  
  if ( u8g_a0_state == 0 )
  {
    i2c_write_byte(I2C_CMD_MODE);
  }
  else
  {
    i2c_write_byte(I2C_DATA_MODE);
  }

  u8g_set_a0 = 0;
}

uint8_t lpc810_u8g_com_ssd_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_INIT:
      //u8g_com_arduino_digital_write(u8g, U8G_PI_SCL, HIGH);
      //u8g_com_arduino_digital_write(u8g, U8G_PI_SDA, HIGH);
      //u8g_a0_state = 0;       /* inital RS state: unknown mode */
    
      lpc81x_i2c_init(u8g->pin_list[U8G_PI_I2C_OPTION]);

      break;
    
    case U8G_COM_MSG_STOP:
      break;

    case U8G_COM_MSG_RESET:
      /* Currently disabled, but it could be enable. Previous restrictions have been removed */
      /* u8g_com_arduino_digital_write(u8g, U8G_PI_RESET, arg_val); */
      break;
      
    case U8G_COM_MSG_CHIP_SELECT:
      u8g_a0_state = 0;
      u8g_set_a0 = 1;		/* force a0 to set again, also forces start condition */
      if ( arg_val == 0 )
      {
        /* disable chip, send stop condition */
	lpc81x_i2c_stop();
     }
      else
      {
        /* enable, do nothing: any byte writing will trigger the i2c start */
      }
      break;

    case U8G_COM_MSG_WRITE_BYTE:
      //u8g_set_a0 = 1;
      if ( lpc810_u8g_com_ssd_start_sequence(u8g) == 0 )
	return lpc81x_i2c_stop(), 0;
      if ( lpc81x_i2c_send_byte(arg_val) == 0 )
	return lpc81x_i2c_stop(), 0;
      // lpc81x_i2c_stop();
      break;
    
    case U8G_COM_MSG_WRITE_SEQ:
      //u8g_set_a0 = 1;
      if ( lpc810_u8g_com_ssd_start_sequence(u8g) == 0 )
	return lpc81x_i2c_stop(), 0;
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
	  if ( lpc81x_i2c_send_byte(*ptr++) == 0 )
	    return lpc81x_i2c_stop(), 0;
          arg_val--;
        }
      }
      // lpc81x_i2c_stop();
      break;

    case U8G_COM_MSG_WRITE_SEQ_P:
      //u8g_set_a0 = 1;
      if ( lpc810_u8g_com_ssd_start_sequence(u8g) == 0 )
	return lpc81x_i2c_stop(), 0;
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
	  if ( lpc81x_i2c_send_byte(u8g_pgm_read(ptr)) == 0 )
	    return 0;
          ptr++;
          arg_val--;
        }
      }
      // lpc81x_i2c_stop();
      break;
      
    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      u8g_a0_state = arg_val;
      u8g_set_a0 = 1;		/* force a0 to set again */
    
      break;
  }
  return 1;
}

uint8_t u8g_com_ssd_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_INIT:
      //u8g_com_arduino_digital_write(u8g, U8G_PI_SCL, HIGH);
      //u8g_com_arduino_digital_write(u8g, U8G_PI_SDA, HIGH);
      //u8g_a0_state = 0;       /* inital RS state: unknown mode */
    
      break;
    
    case U8G_COM_MSG_STOP:
      break;

    case U8G_COM_MSG_RESET:
     break;
      
    case U8G_COM_MSG_CHIP_SELECT:
      u8g_a0_state = 0;
      u8g_set_a0 = 1;		/* force a0 to set again, also forces start condition */
      if ( arg_val == 0 )
      {
        /* disable chip, send stop condition */
	i2c_stop();
     }
      else
      {
        /* enable, do nothing: any byte writing will trigger the i2c start */
      }
      break;

    case U8G_COM_MSG_WRITE_BYTE:
      //u8g_set_a0 = 1;
      u8g_com_ssd_start_sequence(u8g);
      i2c_write_byte(arg_val);
      break;
    
    case U8G_COM_MSG_WRITE_SEQ_P:
    case U8G_COM_MSG_WRITE_SEQ:
      //u8g_set_a0 = 1;
      u8g_com_ssd_start_sequence(u8g);
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
	  i2c_write_byte(*ptr++);
          arg_val--;
        }
      }
      // lpc81x_i2c_stop();
      break;

    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      u8g_a0_state = arg_val;
      u8g_set_a0 = 1;		/* force a0 to set again */
    
      break;
  }
  return 1;
}


/*========================================================================*/
/* main */

u8g_t u8g;

void draw(uint8_t pos)
{
  u8g_SetFont(&u8g, u8g_font_5x8r);
  u8g_DrawStr(&u8g,  0, 12+pos, "Hello World!");
}

void u8g_main()
{
  uint8_t pos = 0;
  /*
    Please uncomment one of the displays below
    Notes:
      - "2x", "4x": high speed version, which uses more RAM
      - "hw_spi": All hardware SPI devices can be used with software SPI also.
	Access type is defined by u8g_com_hw_spi_fn
  */

  // u8g_InitComFn(&u8g, &u8g_dev_uc1701_dogs102_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1701_dogs102_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1701_mini12864_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1701_mini12864_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_dogm132_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_dogm128_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_dogm128_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_lm6059_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_lm6059_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_lm6063_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_lm6063_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_nhd_c12864_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_nhd_c12864_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_nhd_c12832_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_64128n_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_st7565_64128n_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1601_c128032_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1601_c128032_2x_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1610_dogxl160_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1610_dogxl160_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1610_dogxl160_2x_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_uc1610_dogxl160_2x_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_pcd8544_84x48_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_pcf8812_96x65_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_2x_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1325_nhd27oled_2x_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1327_96x96_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1327_96x96_2x_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1322_nhd31oled_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1322_nhd31oled_2x_bw_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1322_nhd31oled_gr_hw_spi, u8g_com_hw_spi_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1322_nhd31oled_2x_gr_hw_spi, u8g_com_hw_spi_fn);
  u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_hw_spi, u8g_com_ssd_i2c_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_2x_hw_spi, u8g_com_ssd_i2c_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1309_128x64_hw_spi, u8g_com_ssd_i2c_fn);
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x32_hw_spi, u8g_com_ssd_i2c_fn);
  
  // u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x32_2x_hw_spi, u8g_com_hw_spi_fn);
  
  
  u8g_SetDefaultForegroundColor(&u8g);

  for(;;)
  {
    /* picture loop */
    Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 0, 2); 	
    u8g_FirstPage(&u8g);
    do
    {
      draw(pos);
    } while ( u8g_NextPage(&u8g) );
    
    Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 2);    
    
    /* refresh screen after some delay */
    u8g_Delay(100);
    
    /* update position */
    pos++;
    pos &= 15;
  }  
}



/*=======================================================================*/
/* main procedure, called by "Reset_Handler" */

int __attribute__ ((noinline)) main(void)
{

  /* set systick and start systick interrupt */
  SysTick_Config(SYS_CORE_CLOCK/1000UL*(unsigned long)SYS_TICK_PERIOD_IN_MS);
  
  /* turn on GPIO */
  Chip_GPIO_Init(LPC_GPIO_PORT);

  /* disable SWCLK and SWDIO, after reset, boot code may activate this */
  Chip_SWM_DisableFixedPin(2);
  Chip_SWM_DisableFixedPin(3);
  
  /* turn on IOCON */
  Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);
  
  /* turn on switch matrix */
  Chip_SWM_Init();
  
  /* activate analog comperator */
  Chip_ACMP_Init(LPC_CMP);

  /* let LED on pin 4 of the DIP8 blink */
  Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 2);  
  
  /* configure I2C pins */
  /* use IOCON pin position macros, IOCON_PIO0 = 0_0,  IOCON_PIO1 = 0_1, etc */
  Chip_IOCON_PinSetMode(LPC_IOCON,IOCON_PIO0,PIN_MODE_INACTIVE);	/* no pullup/-down */
  Chip_IOCON_PinEnableOpenDrainMode(LPC_IOCON, IOCON_PIO0);	
  Chip_IOCON_PinSetMode(LPC_IOCON,IOCON_PIO3,PIN_MODE_INACTIVE);	/* no pullup/-down */
  Chip_IOCON_PinEnableOpenDrainMode(LPC_IOCON, IOCON_PIO3);	
  
  /* I2C modes are only available for the I2C Pins 10 & 11*/
  /* Chip_IOCON_PinSetI2CMode(LPC_IOCON,IOCON_PIO10,0);	*/
  /* Chip_IOCON_PinSetI2CMode(LPC_IOCON,IOCON_PIO11,0);	*/
  
  /* connect I2C to GPIO Pins */
  /* use plain pin numbers: 0_0 = 0, 0_1 = 1, etc */
  //Chip_SWM_MovablePinAssign(SWM_I2C_SCL_IO, 3);	/* 0_3 */
  //Chip_SWM_MovablePinAssign(SWM_I2C_SDA_IO, 0);	/* 0_0 */

  delay_micro_seconds(100000UL);

  //lpc81x_i2c_init(0);
  
  u8g_main();
    
     
  for(;;)
  {

    Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 0, 2); 	
    i2c_start();
    i2c_write_byte(0x00f);
    i2c_write_byte(0x00f);
    i2c_write_byte(0x00f);
    i2c_write_byte(0x00f);
    i2c_write_byte(0x00f);
    i2c_stop();
    
    //delay_micro_seconds(5000UL);
    
    Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 2);    
    i2c_start();
    i2c_write_byte(0x00f);
    i2c_write_byte(0x00f);
    i2c_write_byte(0x00f);
    i2c_write_byte(0x00f);
    i2c_write_byte(0x00f);
    i2c_stop();
    
    //delay_micro_seconds(5000UL);
  }
  
  
  /* enter sleep mode: Reduce from 1.4mA to 0.8mA with 12MHz */  
  while (1)
  {
    SCB->SCR |= (1UL << SCB_SCR_SLEEPONEXIT_Pos);		/* enter sleep mode after interrupt */ 
    Chip_PMU_SleepState(LPC_PMU);						/* enter sleep mode now */
  }
}

