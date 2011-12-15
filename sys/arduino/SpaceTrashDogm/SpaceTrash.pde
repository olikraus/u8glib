

#include "u8g_dogm128_api.h"

u8g_t u8g;

// frames per second
unsigned long next_sec_time;
uint8_t fps, frame_cnt;


void setup(void)
{
  // u8g_InitDogm128API(&u8g_dev_pcf8812_sw_spi);
  u8g_InitDogm128API(&u8g_dev_uc1701_dogs102_hw_spi);
  
  next_sec_time = millis() + 1000UL;
  fps = 0;
  frame_cnt = 0;
   
}

void loop(void)
{
  uint16_t adc = 128;
  
  dog_StartPage();
  do
  {
    st_Draw(fps);
  } while( dog_NextPage() );
  //adc = sys_adc();
  //adc >>= 2;
  //dog_Delay(10);
  //delay(10);
  st_Step(adc, 1, 0);

  frame_cnt++;
  if ( next_sec_time < millis() )
  {
    fps = frame_cnt;
    frame_cnt = 0;
    next_sec_time = millis() + 1000UL;
  }
  
}

