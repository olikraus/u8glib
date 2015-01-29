

#include "u8g.h"
#include <msp430.h>
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

void sys_init(void)
{
  UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
  UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

  __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
  UCSCTL2 = FLLD_1 + 488;                   // Set DCO Multiplier for 16MHz
  __bic_SR_register(SCG0);                  // Enable the FLL control loop
  __delay_cycles(250000);
  P1REN |= 0xF0;  
  P1OUT |= 0xF0;
  P2SEL |= BIT1|BIT3;
}

// setup the user interface
void uiSetup(void) 
{
  // configure internal variables
  isKeyPad = 0;
  // assign some (more or less) useful values to the output variables
  shipLocation = 128;
  isAutoFire = 0;
}

// calculate new output values
void uiStep(void)
{
  isFire = 0;
  if ( (P1IN & (1<<2)) == 0 )
  {
     isFire = 1;
  }
  else if ( (P1IN & (1<<3)) == 0 )
  {
      if ( shipLocation >= 0+  uiIncrement )
	shipLocation -= uiIncrement;
  }
  else if ( (P1IN & (1<<4)) == 0 )
  {
      if ( shipLocation <= 255 -  uiIncrement )
	shipLocation += uiIncrement;
  }
  else if ( (P1IN & (1<<5)) == 0 )
  {
     isAutoFire = !isAutoFire;
  }
}

u8g_t u8g;

int main(void)
{
  unsigned x;

  sys_init();
  u8g_InitHWSPI(&u8g, &u8g_dev_sh1106_128x64_hw_spi, PN(2, 0) /*CSB*/, PN(2,2)/*CD*/, PN(2,6)/*RS*/);
  
  uiSetup();
  st_Setup(&u8g);

  
  while (1)
  {
    u8g_FirstPage(&u8g);
    do
    {
      st_Draw(0);
    } while( u8g_NextPage(&u8g) );
    u8g_Delay(1);
    uiStep();
    st_Step(shipLocation, isAutoFire, isFire);
    
  }  
  return 0;
}


