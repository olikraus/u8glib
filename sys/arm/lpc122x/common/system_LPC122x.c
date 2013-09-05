/**************************************************************************//**
 * $Id: system_LPC122x.c 6932 2011-03-23 19:01:26Z nxp28548 $
 *
 * @file     system_LPC12xx.c
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File
 *           for the NXP LPC122x Device Series
 * @version  1.1
 * @date     $Date:: 2011-03-23#$
 * @author   NXP MCU Team
 *
 * @note
 * Copyright (C) 2011 NXP Semiconductors(NXP). All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 ******************************************************************************/

#include <stdint.h>
#include "LPC122x.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//
// <e> Clock Configuration
//   <e1> Main Clock Setup
//     <e2> System Oscillator Enable
//       <o3.1> Select System Oscillator Frequency Range
//                     <0=> 1 - 20 MHz
//                     <1=> 15 - 25 MHz
//        <o4> Select System Oscillator Frequency <1000000-25000000>
//     </e2>
//     <o5.0..2> Select Input Clock for sys_pllclkin (Register: SYSPLLCLKSEL)
//                     <0=> IRC Oscillator
//                     <1=> System Oscillator
//     <e6> Use System PLL
//                     <i> F_pll = M * F_in
//                     <i> F_in must be in the range of 10 MHz to 25 MHz
//       <o7.0..4>   M: PLL Multiplier Selection
//                     <1-32><#-1>
//       <o7.5..6>   P: PLL Divider Selection
//                     <0=> 2
//                     <1=> 4
//                     <2=> 8
//                     <3=> 16
//     </e6>
//     <o7.0..2> Select Input Clock for Main clock (Register: MAINCLKSEL)
//                     <0=> IRC Oscillator
//                     <1=> Input Clock to System PLL
//                     <2=> WDT Oscillator
//                     <3=> System PLL Clock Out
//   </e1>
//     <e8> Watchdog Oscillator Enable
//       <o9.0..4> Select Divider for Fclkana
//                     <0=>   2 <1=>   4 <2=>   6 <3=>   8
//                     <4=>  10 <5=>  12 <6=>  14 <7=>  16
//                     <8=>  18 <9=>  20 <10=> 22 <11=> 24
//                     <12=> 26 <13=> 28 <14=> 30 <15=> 32
//                     <16=> 34 <17=> 36 <18=> 38 <19=> 40
//                     <20=> 42 <21=> 44 <22=> 46 <23=> 48
//                     <24=> 50 <25=> 52 <26=> 54 <27=> 56
//                     <28=> 58 <29=> 60 <30=> 62 <31=> 64
//       <o9.5..8> Select Watchdog Oscillator Analog Frequency (Fclkana)
//                     <0=> Disabled
//                     <1=> 0.5 MHz
//                     <2=> 0.8 MHz
//                     <3=> 1.1 MHz
//                     <4=> 1.4 MHz
//                     <5=> 1.6 MHz
//                     <6=> 1.8 MHz
//                     <7=> 2.0 MHz
//                     <8=> 2.2 MHz
//                     <9=> 2.4 MHz
//                     <10=> 2.6 MHz
//                     <11=> 2.7 MHz
//                     <12=> 2.9 MHz
//                     <13=> 3.1 MHz
//                     <14=> 3.2 MHz
//                     <15=> 3.4 MHz
//     </e8>
//   <o10.0..7> System AHB Clock Divider <0-255>    
//                     <i> 0 = is disabled
//   <o11.0..7> Select SSP PCLK Divider <0-255> 
//                     <i> 0 = is disabled
//   <o12.0..7> Select UART0 PCLK Divider <0-255> 
//                     <i> 0 = is disabled
//   <o13.0..7> Select UART1 PCLK Divider <0-255> 
//                     <i> 0 = is disabled
//   <o14.0..7> Select SysTick PCLK Divider <0-255> 
//                     <i> 0 = is disabled
//   <e15> CLKOUT Clock Setup
//      <o16.0..2> Select CLKOUT clock source
//                     <0=> IRC Oscillator
//                     <1=> System Oscillator
//                     <2=> WDT Oscillator
//                     <3=> Main clock
//      <o17.0..7> Select CLKOUT PCLK Divider <0-255> 
//                     <i> 0 = Gate
//   </e15>
// </e>
*/
#define CLOCK_SETUP           1
#define MAINCLK_SETUP         1
#define SYSOSC_SETUP          1
#define SYSOSCCTRL_Val        0x00000000
#define __XTAL                12000000
#define SYSPLLCLKSEL_Val      0x00000000
#define SYSPLL_SETUP          1
#define SYSPLLCTRL_Val        0x00000041
#define MAINCLKSEL_Val        0x00000003
#define WDTOSC_SETUP          0
#define WDTOSCCTRL_Val        0x00000001
#define SYSAHBCLKDIV_Val      0x00000001
#define SSPCLKDIV_Val         0x00000000
#define UART0CLKDIV_Val       0x00000000
#define UART1CLKDIV_Val       0x00000000
#define CLKOUTCLK_SETUP       0
#define CLKOUTCLKSEL_Val      0x00000000
#define CLKOUTCLKDIV_Val      0x00000001

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*----------------------------------------------------------------------------
  Check the register settings
 *----------------------------------------------------------------------------*/
#define CHECK_RANGE(val, min, max)                ((val < min) || (val > max))
#define CHECK_RSVD(val, mask)                     (val & mask)

/* Clock Configuration -------------------------------------------------------*/
#if (CHECK_RSVD((SYSOSCCTRL_Val),  ~0x00000003))
   #error "SYSOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((WDTOSCCTRL_Val),  ~0x000001FF))
   #error "WDTOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSPLLCLKSEL_Val), 0, 2))
   #error "SYSPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((SYSPLLCTRL_Val),  ~0x000001FF))
   #error "SYSPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((MAINCLKSEL_Val),  ~0x00000003))
   #error "MAINCLKSEL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSAHBCLKDIV_Val), 0, 255))
   #error "SYSAHBCLKDIV: Value out of range!"
#endif

#if (CHECK_RSVD((CLKOUTCLKSEL_Val),  ~0x00000003))
   #error "CLKOUTCLKSEL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((CLKOUTCLKDIV_Val), 0, 255))
   #error "CLKOUTCLKDIV: Value out of range!"
#endif

#if (CHECK_RANGE((SSPCLKDIV_Val), 0, 255))
   #error "SSPCLKDIV: Value out of range!"
#endif

#if (CHECK_RANGE((UART0CLKDIV_Val), 0, 255))
   #error "UART0CLKDIV: Value out of range!"
#endif

#if (CHECK_RANGE((UART1CLKDIV_Val), 0, 255))
   #error "UART1CLKDIV: Value out of range!"
#endif

#if (CHECK_RANGE((__XTAL), 1000000, 25000000))
   #error "__XTAL: Value out of range!"
#endif

#if ((SYSPLLCLKSEL_Val&0x3)==1 && (SYSOSC_SETUP==0))
  #error "Must enable SYSOSC_SETUP"
#endif

#if ((MAINCLKSEL_Val&0x3)==2 && (WDTOSC_SETUP==0))
  #error "Must enable WDTOSC_SETUP"
#endif

#if ((MAINCLKSEL_Val&0x3)==3 && (SYSPLL_SETUP==0))
  #error "Must enable SYSPLL_SETUP"
#endif

/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __SYS_OSC_CLK     (    __XTAL)    /* Main oscillator frequency        */
#define __IRC_OSC_CLK     (12000000UL)     /* Internal RC oscillator frequency */


#define __FREQSEL   ((WDTOSCCTRL_Val >> 5) & 0x0F)
#define __DIVSEL   (((WDTOSCCTRL_Val & 0x1F) << 1) + 2)

#if (CLOCK_SETUP)                         /* Clock Setup              */
  #if (MAINCLK_SETUP)                      /* Main Clock Setup       */
    #if (WDTOSC_SETUP)                    /* Watchdog Oscillator Setup*/
        #if  (__FREQSEL ==  0)
          #define __WDT_OSC_CLK        ( 400000 / __DIVSEL)
        #elif (__FREQSEL ==  1)
          #define __WDT_OSC_CLK        ( 500000 / __DIVSEL)
        #elif (__FREQSEL ==  2)
          #define __WDT_OSC_CLK        ( 800000 / __DIVSEL)
        #elif (__FREQSEL ==  3)
          #define __WDT_OSC_CLK        (1100000 / __DIVSEL)
        #elif (__FREQSEL ==  4)
          #define __WDT_OSC_CLK        (1400000 / __DIVSEL)
        #elif (__FREQSEL ==  5)
          #define __WDT_OSC_CLK        (1600000 / __DIVSEL)
        #elif (__FREQSEL ==  6)
          #define __WDT_OSC_CLK        (1800000 / __DIVSEL)
        #elif (__FREQSEL ==  7)
          #define __WDT_OSC_CLK        (2000000 / __DIVSEL)
        #elif (__FREQSEL ==  8)
          #define __WDT_OSC_CLK        (2200000 / __DIVSEL)
        #elif (__FREQSEL ==  9)
          #define __WDT_OSC_CLK        (2400000 / __DIVSEL)
        #elif (__FREQSEL == 10)
          #define __WDT_OSC_CLK        (2600000 / __DIVSEL)
        #elif (__FREQSEL == 11)
          #define __WDT_OSC_CLK        (2700000 / __DIVSEL)
        #elif (__FREQSEL == 12)
          #define __WDT_OSC_CLK        (2900000 / __DIVSEL)
        #elif (__FREQSEL == 13)
          #define __WDT_OSC_CLK        (3100000 / __DIVSEL)
        #elif (__FREQSEL == 14)
          #define __WDT_OSC_CLK        (3200000 / __DIVSEL)
        #else
          #define __WDT_OSC_CLK        (3400000 / __DIVSEL)
        #endif
    #else
          #define __WDT_OSC_CLK        (1600000 / 2)
    #endif  // WDTOSC_SETUP

    /* sys_pllclkin calculation */
    #if   ((SYSPLLCLKSEL_Val & 0x03) == 0)
      #define __SYS_PLLCLKIN           (__IRC_OSC_CLK)
    #elif ((SYSPLLCLKSEL_Val & 0x03) == 1)
      #define __SYS_PLLCLKIN           (__SYS_OSC_CLK)
    #elif ((SYSPLLCLKSEL_Val & 0x03) == 2)
      #define __SYS_PLLCLKIN           (__WDT_OSC_CLK)
    #else
      #define __SYS_PLLCLKIN           (0)
    #endif

    #if (SYSPLL_SETUP)                    /* System PLL Setup         */
      #define  __SYS_PLLCLKOUT         (__SYS_PLLCLKIN * ((SYSPLLCTRL_Val & 0x01F) + 1))
    #else
      #define  __SYS_PLLCLKOUT         (__SYS_PLLCLKIN * (1))
    #endif  // SYSPLL_SETUP

    /* main clock calculation */
    #if   ((MAINCLKSEL_Val & 0x03) == 0)
      #define __MAIN_CLOCK             (__IRC_OSC_CLK)
    #elif ((MAINCLKSEL_Val & 0x03) == 1)
      #define __MAIN_CLOCK             (__SYS_PLLCLKIN)
    #elif ((MAINCLKSEL_Val & 0x03) == 2)
      #define __MAIN_CLOCK             (__WDT_OSC_CLK)
    #elif ((MAINCLKSEL_Val & 0x03) == 3)
      #define __MAIN_CLOCK             (__SYS_PLLCLKOUT)
    #else
      #define __MAIN_CLOCK             (0)
    #endif

    #define __SYSTEM_CLOCK             (__MAIN_CLOCK / SYSAHBCLKDIV_Val)

  #else // SYSCLK_SETUP
    #if (SYSAHBCLKDIV_Val == 0)
      #define __SYSTEM_CLOCK           (0)
    #else
      #define __SYSTEM_CLOCK           (__XTAL / SYSAHBCLKDIV_Val)
    #endif
  #endif // SYSCLK_SETUP

#else
  #define __SYSTEM_CLOCK               (__XTAL)
#endif  // CLOCK_SETUP


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = __SYSTEM_CLOCK; /*!< System Clock Frequency (Core Clock)*/
uint32_t MainClock = __MAIN_CLOCK;  /*!< Main Clock Frequency (Main Clock)*/

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  uint32_t wdt_osc = 0;

  /* Determine clock frequency according to clock register values             */
  switch ((LPC_SYSCON->WDTOSCCTRL >> 5) & 0x0F) {
    case 0:  wdt_osc =  400000; break;
    case 1:  wdt_osc =  500000; break;
    case 2:  wdt_osc =  800000; break;
    case 3:  wdt_osc = 1100000; break;
    case 4:  wdt_osc = 1400000; break;
    case 5:  wdt_osc = 1600000; break;
    case 6:  wdt_osc = 1800000; break;
    case 7:  wdt_osc = 2000000; break;
    case 8:  wdt_osc = 2200000; break;
    case 9:  wdt_osc = 2400000; break;
    case 10: wdt_osc = 2600000; break;
    case 11: wdt_osc = 2700000; break;
    case 12: wdt_osc = 2900000; break;
    case 13: wdt_osc = 3100000; break;
    case 14: wdt_osc = 3200000; break;
    case 15: wdt_osc = 3400000; break;
  }
  wdt_osc /= ((LPC_SYSCON->WDTOSCCTRL & 0x1F) << 1) + 2;

  switch (LPC_SYSCON->MAINCLKSEL & 0x03) {
    case 0:                             /* Internal RC oscillator             */
      SystemCoreClock = __IRC_OSC_CLK;
      break;
    case 1:                             /* Input Clock to System PLL          */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                       /* Internal RC oscillator             */
            SystemCoreClock = __IRC_OSC_CLK;
            break;
          case 1:                       /* System oscillator                  */
            SystemCoreClock = __SYS_OSC_CLK;
            break;
          case 2:                       /* WDT Oscillator                     */
            SystemCoreClock = wdt_osc;
            break;
          case 3:                       /* Reserved                           */
            SystemCoreClock = 0;
            break;
      }
      break;
    case 2:                             /* WDT Oscillator                     */
      SystemCoreClock = wdt_osc;
      break;
    case 3:                             /* System PLL Clock Out               */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                       /* Internal RC oscillator             */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = __IRC_OSC_CLK;
            } else {
              SystemCoreClock = __IRC_OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 1:                       /* System oscillator                  */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = __SYS_OSC_CLK;
            } else {
              SystemCoreClock = __SYS_OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 2:                       /* WDT Oscillator                     */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = wdt_osc;
            } else {
              SystemCoreClock = wdt_osc * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 3:                       /* Reserved                           */
            SystemCoreClock = 0;
            break;
      }
      break;
  }
  
  MainClock = SystemCoreClock;  /* Update MainClock */
  
  SystemCoreClock /= LPC_SYSCON->SYSAHBCLKDIV;  /* Update SystemCoreClock */

}

void WWDT_Disable(void)
{
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<15);
  LPC_WWDT->MOD = 0x00;
  LPC_WWDT->FEED = 0xAA;
  LPC_WWDT->FEED = 0x55;
  LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<15);  
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
#if (SYSOSC_SETUP)
  uint32_t i;
#endif

#if (__DEBUG_RAM)       /* Memory Mapping Setup               */
  LPC_SYSCON->SYSMEMREMAP = 0x1;    /* remap to internal RAM */
#else
  LPC_SYSCON->SYSMEMREMAP = 0x2;    /* remap to internal FLASH */
#endif

  /* System clock to the IOCON needs to be enabled or
  most of the I/O related peripherals won't work. */
  LPC_SYSCON->SYSAHBCLKCTRL = 0x0001001FUL;

#if (CLOCK_SETUP)                                 /* Clock Setup              */

#if (__SYSTEM_CLOCK > 30000000)
  /*
  Enable 2 cycle reads for high frequency operation
  Must be done prior to setting up PLL    
  */
  LPC_FLASHCTRL->FLASHCFG = 0;
  LPC_SYSCON->PRESETCTRL &= ~(1<<15);
#endif  
  
#if (MAINCLK_SETUP)                                /* System Clock Setup       */

#if (SYSOSC_SETUP)                                /* System Oscillator Setup  */
  /* bit 0 default is crystal bypass, 
  bit1 0=0~20Mhz crystal input, 1=15~50Mhz crystal input. */
  LPC_SYSCON->SYSOSCCTRL = 0x00;
  /* main system OSC run is cleared, bit 5 in PDRUNCFG register */
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          /* Power-up System Osc      */
  LPC_SYSCON->SYSOSCCTRL    = SYSOSCCTRL_Val;
    /* Wait 200us for OSC to be stablized, no status indication, dummy wait. */
  for (i = 0; i < 200; i++) __NOP();
#endif  // #if (SYSOSC_SETUP)

#if (SYSPLL_SETUP)
  LPC_SYSCON->SYSPLLCLKSEL  = SYSPLLCLKSEL_Val;   /* Select PLL Input         */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
  while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));     /* Wait Until Updated       */
                                /* System PLL Setup         */
  LPC_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
  while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      /* Wait Until PLL Locked    */
#endif // #if (SYSPLL_SETUP)

  LPC_SYSCON->MAINCLKSEL    = MAINCLKSEL_Val;     /* Select PLL Clock Output  */
  LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
  LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */

#endif  // #if (MAINCLK_SETUP)

#if (WDTOSC_SETUP)                                /* Watchdog Oscillator Setup*/
  LPC_SYSCON->WDTOSCCTRL    = WDTOSCCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 6);          /* Power-up WDT Clock       */
#endif

  LPC_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;
  LPC_SYSCON->SSPCLKDIV  = SSPCLKDIV_Val;
  LPC_SYSCON->UART0CLKDIV= UART0CLKDIV_Val;
  LPC_SYSCON->UART1CLKDIV= UART1CLKDIV_Val;

#if (CLKOUTCLK_SETUP)
  LPC_SYSCON->CLKOUTCLKSEL = CLKOUTCLKSEL_Val;
  LPC_SYSCON->CLKOUTDIV = CLKOUTCLKDIV_Val;
#endif

#endif  // #if (CLOCK_SETUP)
}
