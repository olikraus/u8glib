
#include "u8g2.h"

void u8g2_gpio_Delay(u8g2_t *u8g2, uint8_t msg, uint8_t dly)
{
  u8g2->gpio_and_delay_cb(u8g2, msg, dly, NULL);
}