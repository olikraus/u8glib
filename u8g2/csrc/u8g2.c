/*

  u8g2.c
  
*/


#include "u8g2.h"

uint8_t u8g2_dummy_cb(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr)
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
void u8g2_SetupDefaults(u8g2_t *u8g2)
{
    u8g2->display_info = NULL;
    u8g2->display_cb = u8g2_dummy_cb;
    u8g2->cad_cb = u8g2_dummy_cb;
    u8g2->byte_cb = u8g2_dummy_cb;
    u8g2->gpio_and_delay_cb = u8g2_dummy_cb;
}

