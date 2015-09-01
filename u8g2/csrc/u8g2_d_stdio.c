
#include "u8g2.h"

#include <stdio.h>

#define W 4
#define H 2

uint8_t bitmap[4*2*8];

void bitmap_place_tile(uint8_t x, uint8_t y, uint8_t *tile)
{
  uint8_t i;
  for(i = 0; i < 8; i++ )
    bitmap[x+y*W*8+i*W] = tile[i];
}

void bitmap_show(void)
{
  int x, y;
  for( y = 0; y < H*8; y++ )
  {
    for( x = 0; x < W*8; x++ )
    {
      if ( (bitmap[x/8+y*W] & (1<<(7-(x&7)))) != 0 )
      {
	printf("*");
      }
      else
      {
	printf(".");
      }
    }
    printf("\n");
  }
}

uint8_t u8g2_byte_stdio(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr)
{
  static uint8_t x,y,i;
  static uint8_t dc;
  static uint8_t buf[8];
 
  switch(msg)
  {
    case U8G2_MSG_BYTE_SEND:
      if ( dc == 0 )
      {
	buf[i] = arg_int;
	i++;
	if ( i >= 8 )
	{
	  bitmap_place_tile(x, y, buf);
	  i = 0;
	}
      }
      else
      {
	if ( arg_int <= 15 )
	  x = arg_int;
	else
	  y = arg_int & 0x0f;
      }
      break;
    case U8G2_MSG_BYTE_SET_DC:
      dc = arg_int;
      break;
    case U8G2_MSG_BYTE_RESET:
      break;
    case U8G2_MSG_BYTE_START_TRANSFER:
      break;
    case U8G2_MSG_BYTE_END_TRANSFER:
      bitmap_show();
      break;
    case U8G2_MSG_BYTE_SET_I2C_ADR:
      break;
    case U8G2_MSG_BYTE_SET_DEVICE:
      break;
    default:
      break;
  }
  return 1;
}


uint8_t u8g2_cad_stdio(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr)
{
  uint8_t i;
  
  switch(msg)
  {
    case U8G2_MSG_CAD_SEND_CMD:
      u8g2_byte_SetDC(u8g2, 1);
      u8g2_byte_Send(u8g2, arg_int);
      break;
    case U8G2_MSG_CAD_SEND_ARG:
      u8g2_byte_SetDC(u8g2, 1);
      u8g2_byte_Send(u8g2, arg_int);
      break;
    case U8G2_MSG_CAD_SEND_DATA:
      u8g2_byte_SetDC(u8g2, 0);
      for( i = 0; i < 8; i++ )
	u8g2_byte_Send(u8g2, ((uint8_t *)arg_ptr)[i]);
      break;
    case U8G2_MSG_CAD_RESET:
      return u8g2->byte_cb(u8g2, msg, arg_int, arg_ptr);
    case U8G2_MSG_CAD_START_TRANSFER:
      return u8g2->byte_cb(u8g2, msg, arg_int, arg_ptr);
    case U8G2_MSG_CAD_END_TRANSFER:
      return u8g2->byte_cb(u8g2, msg, arg_int, arg_ptr);
    case U8G2_MSG_CAD_SET_I2C_ADR:
      return u8g2->byte_cb(u8g2, msg, arg_int, arg_ptr);
    case U8G2_MSG_CAD_SET_DEVICE:
      return u8g2->byte_cb(u8g2, msg, arg_int, arg_ptr);
    default:
      break;
  }
  return 1;
}


uint8_t u8g2_d_stdio(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8G2_MSG_DISPLAY_INIT:
      break;
    case U8G2_MSG_DISPLAY_POWER_DOWN:
      break;
    case U8G2_MSG_DISPLAY_POWER_UP:
      break;
    case U8G2_MSG_DISPLAY_SET_CONTRAST:
      break;
    case U8G2_MSG_DISPLAY_DRAW_TILE:
      u8g2_cad_StartTransfer(u8g2, 0);
      u8g2_cad_SendCmd(u8g2, ((u8g2_tile_t *)arg_ptr)->x_pos);
      u8g2_cad_SendCmd(u8g2, 0xf0 | ((u8g2_tile_t *)arg_ptr)->y_pos);
      u8g2_cad_SendData(u8g2, 8, ((u8g2_tile_t *)arg_ptr)->tile_ptr);
      u8g2_cad_EndTransfer(u8g2, 1);
      break;
    case U8G2_MSG_DISPLAY_GET_LAYOUT:
      break;
    default:
      break;
  }
  return 1;
}



void u8g2_InitStdio(u8g2_t *u8g2)
{
  u8g2_Init(u8g2);
  u8g2->display_cb = u8g2_d_stdio;
  u8g2->cad_cb = u8g2_cad_stdio;
  u8g2->byte_cb = u8g2_byte_stdio;  
}

