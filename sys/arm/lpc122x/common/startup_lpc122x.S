/* File: startup_lpc11xx.S, derived from startup_ARMCM0.S
 * Purpose: startup file for Cortex-M0 devices. Should use with 
 *   GCC for ARM Embedded Processors
 * Version: V1.4
 * Date: 09 July 2012
 * 
 * Copyright (c) 2011, 2012, ARM Limited
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the ARM Limited nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ARM LIMITED BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
    .syntax unified
    .arch armv6-m

    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0xc00
#endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .if    Heap_Size
    .space    Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit
    
    .section .isr_vector
    .align 2
    .globl __isr_vector
__isr_vector:
    .long    __StackTop            /* Top of Stack */
    .long    Reset_Handler         /* Reset Handler */
    .long    NMI_Handler           /* NMI Handler */
    .long    HardFault_Handler     /* Hard Fault Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    SVC_Handler           /* SVCall Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    PendSV_Handler        /* PendSV Handler */
    .long    SysTick_Handler       /* SysTick Handler */

    /* External interrupts */
    /* .long    Default_Handler */
    .long    WAKEUP0_Handler        /*!< All I/O pins can be used as wakeup source.       */
    .long    WAKEUP1_Handler		/*!< There are 13 pins in total for LPC11xx           */
    .long    WAKEUP2_Handler
    .long    WAKEUP3_Handler
    .long    WAKEUP4_Handler   
    .long    WAKEUP5_Handler        
    .long    WAKEUP6_Handler
    .long    WAKEUP7_Handler       
    .long    WAKEUP8_Handler
    .long    WAKEUP9_Handler
    .long    WAKEUP10_Handler
    .long    WAKEUP11_Handler
    .long    I2C_Handler				/*!< I2C Interrupt                                    */
    .long    TIMER_16_0_Handler		/*!< 16-bit Timer0 Interrupt                          */
    .long    TIMER_16_1_Handler		/*!< 16-bit Timer1 Interrupt                          */
    .long    TIMER_32_0_Handler		/*!< 32-bit Timer0 Interrupt                          */
    .long    TIMER_32_1_Handler		/*!< 32-bit Timer1 Interrupt                          */
    .long    SSP_Handler				/*!< SSP Interrupt                                   */
    .long    UART0_Handler				/*!< UART Interrupt                                   */
    .long    UART1_Handler				/*!< UART Interrupt                                   */
    .long    CMP_Handler				/*!< CMP Interrupt                                    */
    .long    ADC_Handler				/*!< A/D Converter Interrupt                          */
    .long    WDT_Handler				/*!< Watchdog timer Interrupt                         */  
    .long    BOD_Handler				/*!< Brown Out Detect(BOD) Interrupt                  */
    .long    EINT0_Handler			/*!< External Interrupt 0 Interrupt                   */
    .long    EINT1_Handler			/*!< External Interrupt 1 Interrupt                   */
    .long    EINT2_Handler			/*!< External Interrupt 2 Interrupt                   */
    .long    0
    .long    DMA_Handler			
    .long    RTC_Handler			
    
    .size    __isr_vector, . - __isr_vector

    .text
    .thumb
    .thumb_func
    .align 1
    .globl    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in 
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

    subs    r3, r2
    ble     .LC0

.LC1:
    subs    r3, 4
    ldr    r0, [r1,r3]
    str    r0, [r2,r3]
    bgt    .LC1
.LC0:

#ifdef __STARTUP_CLEAR_BSS
/*     This part of work usually is done in C library startup code. Otherwise,
 *     define this macro to enable it in this startup.
 *
 *     Loop to zero out BSS section, which uses following symbols
 *     in linker script:
 *      __bss_start__: start of BSS section. Must align to 4
 *      __bss_end__: end of BSS section. Must align to 4
 */
    ldr r1, =__bss_start__
    ldr r2, =__bss_end__

    subs    r2, r1
    ble .LC3

    movs    r0, 0
.LC2:
    str r0, [r1, r2]
    subs    r2, 4
    bge .LC2
.LC3:
#endif

#ifndef __NO_SYSTEM_INIT
    bl	SystemInit
#endif

#ifndef __START
#define __START _start
#endif
    bl	__START

    .pool
    .size Reset_Handler, . - Reset_Handler
    
/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_default_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
    b    .
    .size    \handler_name, . - \handler_name
    .endm
    
    def_default_handler    NMI_Handler
    def_default_handler    HardFault_Handler
    def_default_handler    SVC_Handler
    def_default_handler    PendSV_Handler
    def_default_handler    SysTick_Handler

    def_default_handler    WAKEUP0_Handler        /*!< All I/O pins can be used as wakeup source.       */
    def_default_handler    WAKEUP1_Handler		/*!< There are 13 pins in total for LPC11xx           */
    def_default_handler    WAKEUP2_Handler
    def_default_handler    WAKEUP3_Handler
    def_default_handler    WAKEUP4_Handler   
    def_default_handler    WAKEUP5_Handler        
    def_default_handler    WAKEUP6_Handler
    def_default_handler    WAKEUP7_Handler       
    def_default_handler    WAKEUP8_Handler
    def_default_handler    WAKEUP9_Handler
    def_default_handler    WAKEUP10_Handler
    def_default_handler    WAKEUP11_Handler
    def_default_handler    I2C_Handler				/*!< I2C Interrupt                                    */
    def_default_handler    TIMER_16_0_Handler		/*!< 16-bit Timer0 Interrupt                          */
    def_default_handler    TIMER_16_1_Handler		/*!< 16-bit Timer1 Interrupt                          */
    def_default_handler    TIMER_32_0_Handler		/*!< 32-bit Timer0 Interrupt                          */
    def_default_handler    TIMER_32_1_Handler		/*!< 32-bit Timer1 Interrupt                          */
    def_default_handler    SSP_Handler				/*!< SSP Interrupt                                   */
    def_default_handler    UART0_Handler				/*!< UART Interrupt                                   */
    def_default_handler    UART1_Handler				/*!< UART Interrupt                                   */
    def_default_handler    CMP_Handler				/*!< CMP Interrupt                                    */
    def_default_handler    ADC_Handler				/*!< A/D Converter Interrupt                          */
    def_default_handler    WDT_Handler				/*!< Watchdog timer Interrupt                         */  
    def_default_handler    BOD_Handler				/*!< Brown Out Detect(BOD) Interrupt                  */
    def_default_handler    EINT0_Handler			/*!< External Interrupt 0 Interrupt                   */
    def_default_handler    EINT1_Handler			/*!< External Interrupt 1 Interrupt                   */
    def_default_handler    EINT2_Handler			/*!< External Interrupt 2 Interrupt                   */
    def_default_handler    DMA_Handler			
    def_default_handler    RTC_Handler			
    

    def_default_handler    Default_Handler

    .weak    DEF_IRQHandler
    .set    DEF_IRQHandler, Default_Handler

    .end
