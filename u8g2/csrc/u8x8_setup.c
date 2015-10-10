/*

  u8g2_setup.c
  
*/


#include "u8x8.h"

uint8_t u8x8_dummy_cb(u8x8_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  /* the dummy callback will not handle any message and will fail for all messages */
  return 0;
}


/*
  Description:
    Setup u8g2
  Args:
    u8g2	An empty u8g2 structure
*/
void u8x8_SetupDefaults(u8x8_t *u8g2)
{
    u8g2->display_info = NULL;
    u8g2->display_cb = u8x8_dummy_cb;
    u8g2->cad_cb = u8x8_dummy_cb;
    u8g2->byte_cb = u8x8_dummy_cb;
    u8g2->gpio_and_delay_cb = u8x8_dummy_cb;
}


