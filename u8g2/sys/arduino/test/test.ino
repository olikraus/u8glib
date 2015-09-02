


#include <Arduino.h>
#include <SPI.h>
#include "u8g2.h"

uint8_t u8g2_gpio_and_delay_arduino(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8G2_MSG_DELAY_MILLI:
      delay(arg_int);
      break;
      
  case U8G2_MSG_GPIO_DC:
      digitalWrite(9, arg_int);
      break;
      
  case U8G2_MSG_GPIO_CS:
      digitalWrite(10, arg_int);
      break;
      
  case U8G2_MSG_GPIO_RESET:
      digitalWrite(8, arg_int);
      break;
      
    default:
      return 0;
  }
  return 1;
}



uint8_t u8g2_byte_arduino_hw_spi(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr)
{
  //uint8_t i;
 
  switch(msg)
  {
    case U8G2_MSG_BYTE_SEND:
      SPI.begin();
      
      //for( i = 0; i < arg_int; i++ )
	// SPI.transfer(((uint8_t *)arg_ptr)[i]);
      SPI.transfer((uint8_t)arg_int);
      SPI.end();
      break;
    case U8G2_MSG_BYTE_SET_DC:
      digitalWrite(9, arg_int);
      break;
    case U8G2_MSG_BYTE_RESET:
      digitalWrite(8, arg_int);
      break;
    case U8G2_MSG_BYTE_START_TRANSFER:
      pinMode(8, OUTPUT);
      pinMode(9, OUTPUT);
      pinMode(10, OUTPUT);
      digitalWrite(10, arg_int);
      break;
    case U8G2_MSG_BYTE_END_TRANSFER:
      digitalWrite(10, arg_int);
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


uint8_t u8g2_byte_arduino_sw_spi(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr)
{
  uint8_t i;
 
  switch(msg)
  {
    case U8G2_MSG_BYTE_SEND:
      for( i = 0; i < 8; i++ )
      {
	if ( arg_int & 128 )
	  digitalWrite(11, 1);
	else
	  digitalWrite(11, 0);
        arg_int <<= 1;
	delay(1);
	digitalWrite(13, 0);
	delay(1);
	digitalWrite(13, 1);
	delay(1);
	
      }
    
    
      //SPI.begin();
      
      //for( i = 0; i < arg_int; i++ )
	// SPI.transfer(((uint8_t *)arg_ptr)[i]);
      //SPI.transfer((uint8_t)arg_int);
      //SPI.end();
      break;
    case U8G2_MSG_BYTE_SET_DC:
      digitalWrite(9, arg_int);
      break;
    case U8G2_MSG_BYTE_RESET:
      digitalWrite(8, arg_int);
      break;
    case U8G2_MSG_BYTE_START_TRANSFER:
      pinMode(8, OUTPUT);
      pinMode(9, OUTPUT);
      pinMode(10, OUTPUT);
      pinMode(11, OUTPUT);
      pinMode(13, OUTPUT);
      digitalWrite(13, 1);      
      digitalWrite(10, arg_int);			// TODO: call gpio cb
      break;
    case U8G2_MSG_BYTE_END_TRANSFER:
      digitalWrite(10, arg_int);			// TODO: call gpio cb
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

void u8g2_Setup_UC1701_DOGS102(u8g2_t *u8g2)
{
  u8g2_Init(u8g2);
  u8g2->display_cb = u8g2_d_uc1701_dogs102;
  u8g2->cad_cb = u8g2_cad_001;
  u8g2->byte_cb = u8g2_byte_arduino_sw_spi;
  u8g2->gpio_and_delay_cb = u8g2_gpio_and_delay_arduino;
}


u8g2_t u8g2;
uint8_t tile[8] = { 0x0f, 0x0f, 0x0f, 0x0f, 0xf0, 0xf0, 0xf0, 0xf0 };

void setup(void)
{
  u8g2_Setup_UC1701_DOGS102(&u8g2);  
  //u8g2_display_DrawTile(&u8g2, 1, 1, 1, tile);
}

void loop(void)
{
  u8g2_display_Init(&u8g2);  
  u8g2_display_DrawTile(&u8g2, 1, 1, 1, tile);
  u8g2_display_DrawTile(&u8g2, 2, 2, 1, tile);
  u8g2_display_DrawTile(&u8g2, 3, 3, 1, tile);
  u8g2_display_DrawTile(&u8g2, 4, 4, 1, tile);
  u8g2_display_DrawTile(&u8g2, 5, 5, 1, tile);
  u8g2_display_DrawTile(&u8g2, 6, 6, 1, tile);
  delay(1000);
  for(;;)
    ;
}

