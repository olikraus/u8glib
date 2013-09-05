/******************************************************************************
 * @file:    system_LPC13xx.c
 * @purpose: CMSIS Cortex-M3 Device Peripheral Access Layer Source File
 *           for the NXP LPC13xx Device Series 
 * @version: V1.0
 * @date:    3. Sept. 2009
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2008 ARM Limited. All rights reserved.
 *
 * ARM Limited (ARM) is supplying this software for use with Cortex-M3 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#include <stdint.h>
#include "LPC13xx.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//
// <e> Clock Configuration
//   <e1> System Clock Setup
//     <e2> System Oscillator Enable
//       <o3.1> Select System Oscillator Frequency Range
//                     <0=> 1 - 20 MHz
//                     <1=> 15 - 25 MHz
//     </e2>
//     <o4> Select Input Clock for sys_pllclkin (Register: SYSPLLCLKSEL)
//                     <0=> IRC Oscillator
//                     <1=> System Oscillator
//                     <2=> WDT Oscillator
//                     <3=> Invalid
//     <e5> Use System PLL
//                     <i> F_pll = M * F_in
//                     <i> F_in must be in the range of 10 MHz to 25 MHz
//       <o6.0..4>   M: PLL Multiplier Selection
//                     <1-32><#-1>
//       <o6.5..6>   P: PLL Divider Selection
//                     <0=> 2
//                     <1=> 4
//                     <2=> 8
//                     <3=> 16
//       <o6.7>      DIRECT: Direct CCO Clock Output Enable
//       <o6.8>      BYPASS: PLL Bypass Enable
//     </e5>
//     <o7> Select Input Clock for Main clock (Register: MAINCLKSEL)
//                     <0=> IRC Oscillator
//                     <1=> Input Clock to System PLL
//                     <2=> WDT Oscillator
//                     <3=> System PLL Clock Out
//   </e1>
//   <e8> USB Clock Setup
//     <e9> Use USB PLL
//                     <i> F_pll = M * F_in
//                     <i> F_in must be in the range of 10 MHz to 25 MHz
//       <o10.0..1> Select Input Clock for usb_pllclkin (Register: USBPLLCLKSEL)
//                     <0=> IRC Oscillator
//                     <1=> System Oscillator
//       <o11.0..4>   M: PLL Multiplier Selection
//                     <1-32><#-1>
//       <o11.5..6>   P: PLL Divider Selection
//                     <0=> 2
//                     <1=> 4
//                     <2=> 8
//                     <3=> 16
//       <o11.7>      DIRECT: Direct CCO Clock Output Enable
//       <o11.8>      BYPASS: PLL Bypass Enable
//     </e9>
//   </e8>
//   <o12.0..7> System AHB Divider <0-255>
//                     <i> 0 = is disabled
//   <o13.0>   SYS Clock Enable
//   <o13.1>   ROM Clock Enable
//   <o13.2>   RAM Clock Enable
//   <o13.3>   FLASH1 Clock Enable
//   <o13.4>   FLASH2 Clock Enable
//   <o13.5>   I2C Clock Enable
//   <o13.6>   GPIO Clock Enable
//   <o13.7>   CT16B0 Clock Enable
//   <o13.8>   CT16B1 Clock Enable
//   <o13.9>   CT32B0 Clock Enable
//   <o13.10>  CT32B1 Clock Enable
//   <o13.11>  SSP Clock Enable
//   <o13.12>  UART Clock Enable
//   <o13.13>  ADC Clock Enable
//   <o13.14>  USB_REG Clock Enable
//   <o13.15>  SWDT Clock Enable
//   <o13.16>  IOCON Clock Enable
// </e>
*/
#define CLOCK_SETUP           1
#define SYSCLK_SETUP          1
#define SYSOSC_SETUP          1
#define SYSOSCCTRL_Val        0x00000000
#define SYSPLLCLKSEL_Val      0x00000001
#define SYSPLL_SETUP          1
#define SYSPLLCTRL_Val        0x00000005
#define MAINCLKSEL_Val        0x00000003
#define USBCLK_SETUP          1
#define USBPLL_SETUP          1
#define USBPLLCLKSEL_Val      0x00000001
#define USBPLLCTRL_Val        0x00000003
#define SYSAHBCLKDIV_Val      0x00000001
#define AHBCLKCTRL_Val        0x0001005F

/*--------------------- Memory Mapping Configuration -------------------------
//
// <e> Memory Mapping
//   <o1.0..1> System Memory Remap (Register: SYSMEMREMAP)
//                     <0=> Bootloader mapped to address 0
//                     <1=> RAM mapped to address 0
//                     <2=> Flash mapped to address 0
//                     <3=> Flash mapped to address 0
// </e>
*/
#define MEMMAP_SETUP          0
#define SYSMEMREMAP_Val       0x00000001

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

#if (CHECK_RANGE((SYSPLLCLKSEL_Val), 0, 2))
   #error "SYSPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((SYSPLLCTRL_Val),  ~0x000001FF))
   #error "SYSPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((MAINCLKSEL_Val),  ~0x00000003))
   #error "MAINCLKSEL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((USBPLLCLKSEL_Val), 0, 1))
   #error "USBPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((USBPLLCTRL_Val),  ~0x000001FF))
   #error "USBPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((USBPLLUEN_Val),   ~0x00000001))
   #error "USBPLLUEN: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSAHBCLKDIV_Val), 0, 255))
   #error "SYSAHBCLKDIV: Value out of range!"
#endif

#if (CHECK_RSVD((AHBCLKCTRL_Val),  ~0x0001FFFF))
   #error "AHBCLKCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((SYSMEMREMAP_Val), ~0x00000003))
   #error "SYSMEMREMAP: Invalid values of reserved bits!"
#endif


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/
    
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define XTAL        (12000000UL)        /* Oscillator frequency               */
#define OSC_CLK     (      XTAL)        /* Main oscillator frequency          */
#define WDT_OSC     (  250000UL)        /* WDT oscillator frequency           */
#define IRC_OSC     (12000000UL)        /* Internal RC oscillator frequency   */


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemFrequency = IRC_OSC; /*!< System Clock Frequency (Core Clock)  */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemFrequency variable.
 */
void SystemInit (void)
{
  uint32_t i;

#if (CLOCK_SETUP)                                 /* Clock Setup              */
  LPC_SYSCON->SYSOSCCTRL    = 0;                  /* Reset Clock Settings     */
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          /* Power-up System Osc      */
  for (i = 0; i < 200; i++);

#if (SYSCLK_SETUP)                                /* System Clock Setup       */
#if (SYSOSC_SETUP)                                /* System Oscillator Setup  */
  LPC_SYSCON->SYSOSCCTRL    = SYSOSCCTRL_Val;
#if (SYSPLL_SETUP)                                /* System PLL Setup         */
  LPC_SYSCON->SYSPLLCLKSEL  = SYSPLLCLKSEL_Val;   /* Select PLL Input         */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
  while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));     /* Wait Until Updated       */
  LPC_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
  while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      /* Wait Until PLL Locked    */
#endif
#endif
  if ((SYSPLLCLKSEL_Val & 3) == 2) {              /* If WDT Clock Selected    */
    LPC_SYSCON->PDRUNCFG   &= ~(1 << 6);          /* Power-up WDT Clock       */
  }
  LPC_SYSCON->MAINCLKSEL    = MAINCLKSEL_Val;     /* Select PLL Clock Output  */
  LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
  LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
#endif

#if (USBCLK_SETUP)                                /* USB Clock Setup          */
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 10);         /* Power-up USB PHY         */
#if (USBPLL_SETUP)                                /* USB PLL Setup            */
  LPC_SYSCON->PDRUNCFG     &= ~(1 <<  8);         /* Power-up USB PLL         */
  LPC_SYSCON->USBPLLCLKSEL  = USBPLLCLKSEL_Val;   /* Select PLL Input         */
  LPC_SYSCON->USBPLLCLKUEN  = 0x01;               /* Update Clock Source      */
  LPC_SYSCON->USBPLLCLKUEN  = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->USBPLLCLKUEN  = 0x01;
  while (!(LPC_SYSCON->USBPLLCLKUEN & 0x01));     /* Wait Until Updated       */
  LPC_SYSCON->USBPLLCTRL    = USBPLLCTRL_Val;
  while (!(LPC_SYSCON->USBPLLSTAT   & 0x01));     /* Wait Until PLL Locked    */
  LPC_SYSCON->USBCLKSEL     = 0x00;               /* Select USB PLL           */
#else
  LPC_SYSCON->USBCLKSEL     = 0x01;               /* Select Main Clock        */
#endif
#else
  LPC_SYSCON->PDRUNCFG     |=  (1 << 10);         /* Power-down USB PHY       */
  LPC_SYSCON->PDRUNCFG     |=  (1 <<  8);         /* Power-down USB PLL       */
#endif

  LPC_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;
  LPC_SYSCON->SYSAHBCLKCTRL = AHBCLKCTRL_Val;
#endif

  /* Determine clock frequency according to clock register values             */
  switch (LPC_SYSCON->MAINCLKSEL & 0x03) {
    case 0:                             /* Internal RC oscillator             */
      SystemFrequency = IRC_OSC;
      break;
    case 1:                             /* Input Clock to System PLL          */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                       /* Internal RC oscillator             */
            SystemFrequency = IRC_OSC;
            break;
          case 1:                       /* System oscillator                  */
            SystemFrequency = OSC_CLK;
            break;
          case 2:                       /* WDT Oscillator                     */
            SystemFrequency = WDT_OSC;
            break;
          case 3:                       /* Reserved                           */
            SystemFrequency = 0;
            break;
      }
      break;
    case 2:                             /* WDT Oscillator                     */
      SystemFrequency = WDT_OSC;
      break;
    case 3:                             /* System PLL Clock Out               */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                       /* Internal RC oscillator             */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemFrequency = IRC_OSC;
            } else {
              SystemFrequency = IRC_OSC * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 1:                       /* System oscillator                  */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemFrequency = OSC_CLK;
            } else {
              SystemFrequency = OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 2:                       /* WDT Oscillator                     */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemFrequency = WDT_OSC;
            } else {
              SystemFrequency = WDT_OSC * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 3:                       /* Reserved                           */
            SystemFrequency = 0;
            break;
      }
      break;
  }

#if (MEMMAP_SETUP || MEMMAP_INIT)       /* Memory Mapping Setup               */
  LPC_SYSCON->SYSMEMREMAP = SYSMEMREMAP_Val;
#endif
}
