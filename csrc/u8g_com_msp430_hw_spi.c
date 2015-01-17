/*
  
  u8g_com_msp430_hw_spi.c

  Universal 8bit Graphics Library
  
  Copyright (c) 2012, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
 
*/ 
 
#include "u8g.h"

#if defined(__MSP430__)
#define U8G_MSP430_HW_SPI
#endif

#if defined(U8G_MSP430_HW_SPI)

#include <msp430.h>

#ifndef F_CPU
#error "Please specifiy actual master clock using F_CPU in HZ"
#endif
#define F_SPI  1000000UL

#define U8G_USE_USCIA2	1
#define U8G_USE_USCIA3	2
#define U8G_USE_USCIB0	3
#ifndef U8G_USE_USCI
#define U8G_USE_USCI	U8G_USE_USCIB0
#endif

static uint8_t u8g_msp430_spi_out(uint8_t data)
{
#if U8G_USE_USCI == U8G_USE_USCIB0
  UCB0TXBUF = data;
  while ((UCB0STAT&UCBUSY));
#elif U8G_USE_USCI == U8G_USE_USCIA2
  UCA2TXBUF = data;
  while ((UCA2STAT&UCBUSY));
#elif U8g_USE_USCI == U8G_USE_USCIA3
  UCA3TXBUF = data;
  while ((UCA3STAT&UCBUSY));
#endif
}

uint8_t u8g_com_msp430_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_STOP:
      break;
    
    case U8G_COM_MSG_INIT:
	/*
 	 * on MSP430 you need to set PSEL alternative function which
 	 * may not be required on other MCU's - should be handled
 	 * by a low level u8g_SetPinAlternate(pin_number)...
 	 */
#if U8G_USE_USCI == U8G_USE_USCIB0
      P2SEL |= BIT1|BIT3;                       // Assign P2.3 to UCB0CLK and P2.1 UCB0SIMO
      UCB0CTL1 |= UCSWRST;                      // **Put state machine in reset**
      UCB0CTL0 |= UCMST|UCSYNC|UCCKPL|UCMSB;    // 3-pin, 8-bit SPI master Clock polarity high, MSB
      UCB0CTL1 |= UCSSEL_2;                     // SMCLK
      UCB0BR0 = (unsigned char)(F_CPU/F_SPI);   // 
      UCB0BR1 = 0;                              //
      UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
#elif U8G_USE_USCI == U8G_USE_USCIA2
      P9SEL |= BIT0|BIT4;                     // Assign P9.0 to UCA2CLK and P9.4 UCA2SIMO
      UCA2CTL1 |= UCSWRST;                      // **Put state machine in reset**
      UCA2CTL0 |= UCMST|UCSYNC|UCCKPL|UCMSB;    // 3-pin, 8-bit SPI master Clock polarity high, MSB
      UCA2CTL1 |= UCSSEL_2;                     // SMCLK
      UCA2BR0 = (unsigned char)(F_CPU/F_SPI);   //
      UCA2BR1 = 0;                              //
      UCA2CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
#elif U8G_USE_USCI == U8G_USE_USCIA3
      P10SEL |= BIT0|BIT4;                     // Assign P10.0 to UCA3CLK and P10.4 UCA3SIMO
      UCA3CTL1 |= UCSWRST;                      // **Put state machine in reset**
      UCA3CTL0 |= UCMST|UCSYNC|UCCKPL|UCMSB;    // 3-pin, 8-bit SPI master Clock polarity high, MSB
      UCA3CTL1 |= UCSSEL_2;                     // SMCLK
      UCA3BR0 = (unsigned char)(F_CPU/F_SPI);   //
      UCA3BR1 = 0;                              //
      UCA3CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
#else
#error "Setup SPI failed!"
#endif
      u8g_SetPILevel(u8g, U8G_PI_CS, 1);
      u8g_SetPILevel(u8g, U8G_PI_A0, 1);
      u8g_SetPILevel(u8g, U8G_PI_RESET, 1);
      u8g_SetPIOutput(u8g, U8G_PI_CS);
      u8g_SetPIOutput(u8g, U8G_PI_A0);
      u8g_SetPIOutput(u8g, U8G_PI_RESET);

      break;
    
    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      u8g_SetPILevel(u8g, U8G_PI_A0, arg_val);
      break;

    case U8G_COM_MSG_CHIP_SELECT:
      
       u8g_SetPILevel(u8g, U8G_PI_CS, (arg_val ? 0 : 1));
      break;
      
    case U8G_COM_MSG_RESET:

      u8g_SetPILevel(u8g, U8G_PI_RESET, arg_val);
      break;
    
    case U8G_COM_MSG_WRITE_BYTE:
      u8g_msp430_spi_out(arg_val);
      break;
    
    case U8G_COM_MSG_WRITE_SEQ:
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
          u8g_msp430_spi_out(*ptr++);
          arg_val--;
        }
      }
      break;
    case U8G_COM_MSG_WRITE_SEQ_P:
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
          u8g_msp430_spi_out(u8g_pgm_read(ptr));
          ptr++;
          arg_val--;
        }
      }
      break;
  }
  return 1;
}

#else

uint8_t u8g_com_msp430_hw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  return 1;
}

#endif


