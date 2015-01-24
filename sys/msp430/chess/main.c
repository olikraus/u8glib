#include "u8g.h"
#include <msp430.h>


void sys_setup_keys(void)
{
  P1REN |= 0xF0;  
  P1OUT |= 0xF0;
}


uint8_t sys_get_key(void)
{
  uint8_t result = CHESS_KEY_NONE;
  if ( (P1IN & (1<<2)) == 0 )
    result = CHESS_KEY_NEXT;
  if ( (P1IN & (1<<3)) == 0 )
    result = CHESS_KEY_PREV;
  if ( (P1IN & (1<<4)) == 0 )
    result |= CHESS_KEY_SELECT;
  if ( (P1IN & (1<<5)) == 0 )
    result |= CHESS_KEY_BACK;
  return result;
}


uint8_t sys_key_first = CHESS_KEY_NONE;
uint8_t sys_key_second = CHESS_KEY_NONE;
uint8_t sys_key_code = CHESS_KEY_NONE;

void sys_debounce_key(void) 
{
  sys_key_second = sys_key_first;
  sys_key_first = sys_get_key();
    
  if ( sys_key_second == sys_key_first )
    sys_key_code = sys_key_first;
  else
    sys_key_code = CHESS_KEY_NONE;
}

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
  P3SEL |= BIT0|BIT2;                       // setup alternative mode
}

int main(void)
{
  
  uint8_t keyCode = CHESS_KEY_NONE;
  uint8_t is_redraw = 1;
  
  u8g_t u8g;
  
  sys_init();
  sys_setup_keys();
#if U8G_USE_USCI==1
  u8g_InitHWSPI(&u8g, &u8g_dev_sh1106_128x64_hw_spi, PN(9, 1) /*CSB*/, PN(9,2)/*CD*/, PN(9,3)/*RS*/);
#else
  u8g_InitHWSPI(&u8g, &u8g_dev_sh1106_128x64_hw_spi, PN(2, 0) /*CSB*/, PN(2,2)/*CD*/, PN(2,6)/*RS*/);
#endif


  u8g_FirstPage(&u8g);
  chess_Init(&u8g, 0);

  for(;;)
  {
    if ( is_redraw != 0 )
    {
        u8g_FirstPage(&u8g);
        do {
          chess_Draw();
        } while( u8g_NextPage(&u8g) );
      is_redraw--;
    }
    
    sys_debounce_key();
    keyCode = sys_key_code;
    if ( keyCode != CHESS_KEY_NONE )
    {
      is_redraw = 2;
      chess_Step(keyCode);
    }
    chess_Step(CHESS_KEY_NONE);
  }
}

