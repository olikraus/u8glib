/*

  u8g2_byte.c 
  
*/

#include "u8g2.h"

uint8_t u8g2_byte_SetDC(u8g2_t *u8g2, uint8_t dc)
{
  return u8g2->byte_cb(u8g2, U8G2_MSG_BYTE_SET_DC, dc, NULL);
}

uint8_t u8g2_byte_Send(u8g2_t *u8g2, uint8_t byte)
{
  return u8g2->byte_cb(u8g2, U8G2_MSG_BYTE_SEND, byte, NULL);
}

uint8_t u8g2_byte_spi(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8G2_MSG_BYTE_SEND:
      break;
  }
  return 0;
}
