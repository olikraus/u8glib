

#include "SDL.h"
#include "u8g_dogm128_api.h"
#include <stdlib.h>
#include <stdio.h>


// generic configuration values
uint8_t uiIncrement = 4;

// DOGS102 configuration values
uint8_t uiKeyUpPin = 5;
uint8_t uiKeyDownPin = 3;
uint8_t uiKeyFirePin = 4;

// output values
uint8_t shipLocation = 128;
uint8_t isAutoFire = 1;
uint8_t isFire = 0;

// internal values
uint8_t isKeyPad = 0;

// setup the user interface
void uiSetup(void) {
  
  // configure internal variables
  isKeyPad = 0;
  // assign some (more or less) useful values to the output variables
  shipLocation = 128;
  isAutoFire = 0;
}

// calculate new output values
void uiStep(void) {
  int key = u8g_sdl_get_key();
  isFire = 0;
  switch( key )
  {
    case ' ':
      isFire = 1;
      break;
    case 274:
    case 'x':
      if ( shipLocation >= 0+  uiIncrement )
	shipLocation -= uiIncrement;
      //printf("%d\n", shipLocation);
      break;
    case 273:
    case 's':
      if ( shipLocation <= 255 -  uiIncrement )
	shipLocation += uiIncrement;
      //printf("%d\n", shipLocation);
      break;
    case 'q':
      exit(0);
  }
}

int main(void)
{
  uint32_t x;
  
  u8g_InitDogm128API(&u8g_dev_sdl_1bit);
  //u8g_SetDogmRot90();
  
  uiSetup();
  
  for(x = 0; x < 2000; x++)
  {    
    dog_StartPage();
    do
    {
      st_Draw(0);
    } while( dog_NextPage() );
    SDL_Delay(10);
    uiStep();
    st_Step(shipLocation, isAutoFire, isFire);
    
  }  
  return 0;
}

