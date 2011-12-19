

#include "u8g_dogm128_api.h"

u8g_t u8g;

// frames per second
unsigned long next_sec_time;
uint8_t fps, frame_cnt;

// generic configuration values
uint8_t uiIncrement = 2;

// DOGS102 configuration values
uint8_t uiKeyUpPin = 5;
uint8_t uiKeyDownPin = 3;
uint8_t uiKeyFirePin = 4;

// DOGM132 configuration values
uint8_t uiKeyUpPin2 = 7;
uint8_t uiKeyDownPin2 = 3;
uint8_t uiKeyFirePin2 = 2;

// output values
uint8_t shipLocation = 127;
uint8_t isFire = 0;

// setup the user interface
void uiSetup(void) {
  // configure input keys 
  
  pinMode(uiKeyUpPin, INPUT);           // set pin to input
  digitalWrite(uiKeyUpPin, HIGH);       // turn on pullup resistors
  pinMode(uiKeyDownPin, INPUT);           // set pin to input
  digitalWrite(uiKeyDownPin, HIGH);       // turn on pullup resistors
  pinMode(uiKeyFirePin, INPUT);           // set pin to input
  digitalWrite(uiKeyFirePin, HIGH);       // turn on pullup resistors

  pinMode(uiKeyUpPin2, INPUT);           // set pin to input
  digitalWrite(uiKeyUpPin2, HIGH);       // turn on pullup resistors
  pinMode(uiKeyDownPin2, INPUT);           // set pin to input
  digitalWrite(uiKeyDownPin2, HIGH);       // turn on pullup resistors
  pinMode(uiKeyFirePin2, INPUT);           // set pin to input
  digitalWrite(uiKeyFirePin2, HIGH);       // turn on pullup resistors
  
  
  // assign some (more or less) useful values to the output variables
  shipLocation = 127;
}

// calculate new output values
void uiStep(void) {
  if ( digitalRead(uiKeyUpPin) == LOW || digitalRead(uiKeyUpPin2) == LOW )
    if ( shipLocation <= 255 -  uiIncrement )
      shipLocation += uiIncrement;
  if ( digitalRead(uiKeyDownPin) == LOW || digitalRead(uiKeyDownPin2) == LOW )
    if ( shipLocation >= 0+  uiIncrement )
      shipLocation -= uiIncrement;
  isFire = 0;
  if ( digitalRead(uiKeyFirePin) == LOW || digitalRead(uiKeyFirePin2) == LOW )
    isFire = 1;
}


void setup(void)
{
  // u8g_InitDogm128API(&u8g_dev_pcf8812_sw_spi);
  u8g_InitDogm128API(&u8g_dev_uc1701_dogs102_hw_spi);
  
  uiSetup();
  next_sec_time = millis() + 1000UL;
  fps = 0;
  frame_cnt = 0;
   
}

void loop(void)
{
  dog_StartPage();
  do
  {
    st_Draw(fps);
  } while( dog_NextPage() );
  
  uiStep();
  st_Step(shipLocation, 0, isFire);

  frame_cnt++;
  if ( next_sec_time < millis() )
  {
    fps = frame_cnt;
    frame_cnt = 0;
    next_sec_time = millis() + 1000UL;
  }
  
}

