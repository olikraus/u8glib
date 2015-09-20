/*

  u8g2_byte.c 
  
*/

#include "u8g2.h"

uint8_t u8g2_byte_SetDC(u8g2_t *u8g2, uint8_t dc)
{
  return u8g2->byte_cb(u8g2, U8G2_MSG_BYTE_SET_DC, dc, NULL);
}

uint8_t u8g2_byte_SendBytes(u8g2_t *u8g2, uint8_t cnt, uint8_t *data)
{
  return u8g2->byte_cb(u8g2, U8G2_MSG_BYTE_SEND, cnt, (void *)data);
}

uint8_t u8g2_byte_SendByte(u8g2_t *u8g2, uint8_t byte)
{
  return u8g2_byte_SendBytes(u8g2, 1, &byte);
}



/*
  Uses:
    u8g2->display_info->sda_setup_time_ns
    u8g2->display_info->sck_pulse_width_ns
    u8g2->display_info->sck_takeover_edge
    u8g2->display_info->chip_disable_level
    u8g2->display_info->chip_enable_level
    u8g2->display_info->post_chip_enable_wait_ns
    u8g2->display_info->pre_chip_disable_wait_ns
  Calls to GPIO and DELAY:
    U8G2_MSG_DELAY_NANO
    U8G2_MSG_GPIO_DC
    U8G2_MSG_GPIO_CS
    U8G2_MSG_GPIO_CLOCK
    U8G2_MSG_GPIO_DATA
  Handles:
    U8G2_MSG_BYTE_INIT
    U8G2_MSG_BYTE_SEND
    U8G2_MSG_BYTE_SET_DC
    U8G2_MSG_BYTE_START_TRANSFER
    U8G2_MSG_BYTE_END_TRANSFER
    U8G2_MSG_BYTE_SET_I2C_ADR	(ignored)
    U8G2_MSG_BYTE_SET_DEVICE	(ignored)
*/
uint8_t u8g2_byte_8bit_sw_spi(u8g2_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  uint8_t i, b;
  uint8_t *data;
  uint8_t takeover_edge = u8g2->display_info->sck_takeover_edge;
  uint8_t not_takeover_edge = 1 - takeover_edge;
 
  switch(msg)
  {
    case U8G2_MSG_BYTE_SEND:
      data = (uint8_t *)arg_ptr;
      while( arg_int > 0 )
      {
	b = *data;
	data++;
	arg_int--;
	for( i = 0; i < 8; i++ )
	{
	  if ( b & 128 )
	    u8g2_gpio_SetData(u8g2, 1);
	  else
	    u8g2_gpio_SetData(u8g2, 0);
	  b <<= 1;
	  
	  u8g2_gpio_SetClock(u8g2, not_takeover_edge);
	  u8g2_gpio_Delay(u8g2, U8G2_MSG_DELAY_NANO, u8g2->display_info->sda_setup_time_ns);
	  u8g2_gpio_SetClock(u8g2, takeover_edge);
	  u8g2_gpio_Delay(u8g2, U8G2_MSG_DELAY_NANO, u8g2->display_info->sck_pulse_width_ns);
	}    
      }
      break;
      
    case U8G2_MSG_BYTE_INIT:
      /* disable chipselect */
      u8g2_gpio_SetCS(u8g2, u8g2->display_info->chip_disable_level);
      /* no wait required here */
      
      /* for SPI: setup correct level of the clock signal */
      u8g2_gpio_SetClock(u8g2, u8g2->display_info->sck_takeover_edge);
      break;
    case U8G2_MSG_BYTE_SET_DC:
      u8g2_gpio_SetDC(u8g2, arg_int);
      break;
    case U8G2_MSG_BYTE_START_TRANSFER:
      u8g2_gpio_SetCS(u8g2, u8g2->display_info->chip_enable_level);  
      u8g2->gpio_and_delay_cb(u8g2, U8G2_MSG_DELAY_NANO, u8g2->display_info->post_chip_enable_wait_ns, NULL);
      break;
    case U8G2_MSG_BYTE_END_TRANSFER:
      u8g2->gpio_and_delay_cb(u8g2, U8G2_MSG_DELAY_NANO, u8g2->display_info->pre_chip_disable_wait_ns, NULL);
      u8g2_gpio_SetCS(u8g2, u8g2->display_info->chip_disable_level);
      break;
    case U8G2_MSG_BYTE_SET_I2C_ADR:
      break;
    case U8G2_MSG_BYTE_SET_DEVICE:
      break;
    default:
      return 0;
  }
  return 1;
}

