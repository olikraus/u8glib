/*
    
  startup_lpc81x.c

  System & U8glib Code for the LPC81x ARM Controller.
  No assembly file required.

  Universal 8bit Graphics Library
  
  Copyright (c) 2013, olikraus@gmail.com
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
  
  
  
  ACMP reqires LPC810M021JN8 Marking 4C or later.

*/

#include "chip.h"
#include "lpc81x_system.h"


/*=======================================================================*/
/* delay procedures */

/*
  Delay by the provided number of system ticks.
  The delay must be smaller than the RELOAD value.
  This delay has an imprecision of about +/- 20 system ticks.   
*/
static void _delay_system_ticks_sub(uint32_t sys_ticks)
{
  uint32_t start_val, end_val, curr_val;
  uint32_t load;
  
  start_val = SysTick->VAL;
  start_val &= 0x0ffffffUL;
  end_val = start_val;
  
  if ( end_val < sys_ticks )
  {
    /* check, if the operation after this if clause would lead to a negative result */
    /* if this would be the case, then add the reload value first */
    load = SysTick->LOAD;
    load &= 0x0ffffffUL;
    end_val += load;
  }
  /* counter goes towards zero, so end_val is below start value */
  end_val -= sys_ticks;		
  
  
  /* wait until interval is left */
  if ( start_val >= end_val )
  {
    for(;;)
    {
      curr_val = SysTick->VAL;
      curr_val &= 0x0ffffffUL;
      if ( curr_val <= end_val )
	break;
      if ( curr_val > start_val )
	break;
    }
  }
  else
  {
    for(;;)
    {
      curr_val = SysTick->VAL;
      curr_val &= 0x0ffffffUL;
      if ( curr_val <= end_val && curr_val > start_val )
	break;
    }
  }
}

/*
  Delay by the provided number of system ticks.
  Any values between 0 and 0x0ffffffff are allowed.
*/
void delay_system_ticks(uint32_t sys_ticks)
{
  uint32_t load4;
  load4 = SysTick->LOAD;
  load4 &= 0x0ffffffUL;
  load4 >>= 2;
  
  while ( sys_ticks > load4 )
  {
    sys_ticks -= load4;
    _delay_system_ticks_sub(load4);
  }
  _delay_system_ticks_sub(sys_ticks);
}




/*=======================================================================*/
/* delay */

/*
  Delay by the provided number of micro seconds.
  Limitation: "us" * System-Freq in MHz must now overflow in 32 bit.
  Values between 0 and 1.000.000 (1 second) are ok.
*/
void delay_micro_seconds(uint32_t us)
{
  uint32_t sys_ticks;

  sys_ticks = SYS_CORE_CLOCK / 1000000UL;
  sys_ticks *= us;
  delay_system_ticks(sys_ticks);  
}


/*=======================================================================*/
/* system procedures and sys tick master task */

volatile uint32_t sys_tick_irq_cnt=0;


void __attribute__ ((interrupt)) SysTick_Handler(void)
{
  sys_tick_irq_cnt++;
  
}


/*=======================================================================*/
/* u8g delay procedures */

void u8g_Delay(uint16_t val)
{
    
  delay_micro_seconds(1000UL*(uint32_t)val);
}

void u8g_MicroDelay(void)
{
  delay_micro_seconds(1);
}

void u8g_10MicroDelay(void)
{
  delay_micro_seconds(10);
}

/*=======================================================================*/
/* generic  i2c (http://en.wikipedia.org/wiki/I%C2%B2C) */
/* SCL: 0_3 */
/* SDA: 0_0 */


uint8_t i2c_started = 0;

void i2c_delay(void)
{
  /* should be at least 4 */
  /* should be 5 for 100KHz transfer speed */
  
  delay_micro_seconds(5);
}

void __attribute__ ((noinline)) i2c_init(void)
{
  Chip_IOCON_PinSetMode(LPC_IOCON,IOCON_PIO0,PIN_MODE_INACTIVE);	/* no pullup/-down */
  Chip_IOCON_PinSetMode(LPC_IOCON,IOCON_PIO3,PIN_MODE_INACTIVE);	/* no pullup/-down */
  Chip_IOCON_PinEnableOpenDrainMode(LPC_IOCON, IOCON_PIO3);	
  Chip_IOCON_PinEnableOpenDrainMode(LPC_IOCON, IOCON_PIO0);	
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 3);
  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 0);
}

uint8_t __attribute__ ((noinline)) i2c_read_scl(void)
{
  Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 3);
  return Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, 0, 3);
}

void __attribute__ ((noinline)) i2c_clear_scl(void)
{
  /* set open collector and drive low */
  //Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 3);
  //LPC_GPIO_PORT->DIR[0] &= ~(1UL << 3);
  LPC_GPIO_PORT->DIR[0] |= 1UL << 3;

}

uint8_t __attribute__ ((noinline)) i2c_read_sda(void)
{
  Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 0);
  return Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, 0, 0);  
}

void __attribute__ ((noinline)) i2c_clear_sda(void)
{
  /* set open collector and drive low */
  Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 0);
}

void __attribute__ ((noinline)) i2c_start(void) 
{
  if ( i2c_started != 0 ) 
  { 
    /* if already started: do restart */
    i2c_read_sda();	/* SDA = 1 */
    i2c_delay();
    i2c_read_scl();
    /* clock stretching is not done */
    /* while (i2c_read_scl() == 0)   ; */
    i2c_delay();		/* another delay, just to be sure... */
  }
  i2c_read_sda();
  /*
  if (i2c_read_sda() == 0) 
  {
    // do something because arbitration is lost
  }
  */
  /* send the start condition, both lines go from 1 to 0 */
  i2c_clear_sda();
  i2c_delay();
  i2c_clear_scl();
  i2c_started = 1;
}


void __attribute__ ((noinline)) i2c_stop(void)
{
  /* set SDA to 0 */
  i2c_clear_sda();  
  i2c_delay();
  
  /* now release all lines */
  i2c_read_scl();
  /* clock stretching is not done */
  /* while (i2c_read_scl() == 0)   ; */
  i2c_delay();		/* another delay, just to be sure... */
  
  /* set SDA to 1 */
  i2c_read_sda();
  /*
  if (i2c_read_sda() == 0) 
  {
    // do something because arbitration is lost
  }
  */
  i2c_delay();
  i2c_started = 0;
}

void i2c_write_bit(uint8_t val) 
{
  if (val)
    i2c_read_sda();
  else
    i2c_clear_sda();
  
  i2c_delay();
  i2c_read_scl();
  /* clock stretching is not done */
  /* while (i2c_read_scl() == 0)   ; */

  /* validation is skipped, because this will be the only master */  
  /* If SDA is high, check that nobody else is driving SDA */
  /*
  if (val && i2c_read_sda() == 0) 
  {
    arbitration_lost();
  }
  */
  i2c_delay();
  i2c_clear_scl();
}

uint8_t i2c_read_bit(void) 
{
  uint8_t val;
  /* do not drive SDA */
  i2c_read_sda();
  i2c_delay();
  i2c_read_scl();
  /* clock stretching is not done */
  /* while (i2c_read_scl() == 0)   ; */
  
  i2c_delay();	/* may not be required... */
  val = i2c_read_sda();
  i2c_delay();
  i2c_clear_scl();
  return val;
}

uint8_t i2c_write_byte(uint8_t b)
{
  uint8_t i = 8;
  do
  {
    i2c_write_bit(b & 128);
    b <<= 1;
    i--;
  } while ( i != 0 );
  /* read ack from client */
  /* 0: ack was given by client */
  /* 1: nothing happend during ack cycle */  
  return i2c_read_bit();
}

/*=======================================================================*/
/* u8glib com callback */


#define I2C_SLA         (0x3c*2)
//#define I2C_CMD_MODE  0x080
#define I2C_CMD_MODE    0x000
#define I2C_DATA_MODE   0x040

uint8_t u8g_a0_state;
uint8_t u8g_set_a0;

static void u8g_com_ssd_start_sequence(u8g_t *u8g)
{
  /* are we requested to set the a0 state? */
  if ( u8g_set_a0 == 0 )
    return;

  i2c_start();
  i2c_write_byte(I2C_SLA);		// address and 0 for RWn bit
  
  if ( u8g_a0_state == 0 )
  {
    i2c_write_byte(I2C_CMD_MODE);
  }
  else
  {
    i2c_write_byte(I2C_DATA_MODE);
  }

  u8g_set_a0 = 0;
}

uint8_t u8g_com_ssd_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_INIT:
      //u8g_com_arduino_digital_write(u8g, U8G_PI_SCL, HIGH);
      //u8g_com_arduino_digital_write(u8g, U8G_PI_SDA, HIGH);
      //u8g_a0_state = 0;       /* inital RS state: unknown mode */
    
      i2c_init();
      break;
    
    case U8G_COM_MSG_STOP:
      break;

    case U8G_COM_MSG_RESET:
     break;
      
    case U8G_COM_MSG_CHIP_SELECT:
      u8g_a0_state = 0;
      u8g_set_a0 = 1;		/* force a0 to set again, also forces start condition */
      if ( arg_val == 0 )
      {
        /* disable chip, send stop condition */
	i2c_stop();
     }
      else
      {
        /* enable, do nothing: any byte writing will trigger the i2c start */
      }
      break;

    case U8G_COM_MSG_WRITE_BYTE:
      //u8g_set_a0 = 1;
      u8g_com_ssd_start_sequence(u8g);
      i2c_write_byte(arg_val);
      break;
    
    case U8G_COM_MSG_WRITE_SEQ_P:
    case U8G_COM_MSG_WRITE_SEQ:
      //u8g_set_a0 = 1;
      u8g_com_ssd_start_sequence(u8g);
      {
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
	  i2c_write_byte(*ptr++);
          arg_val--;
        }
      }
      // lpc81x_i2c_stop();
      break;

    case U8G_COM_MSG_ADDRESS:                     /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
      u8g_a0_state = arg_val;
      u8g_set_a0 = 1;		/* force a0 to set again */
    
      break;
  }
  return 1;
}




/*=======================================================================*/
/* 
  Reserve some space for the stack. This is used to check if global variables + stack exceed RAM size.
  If -Wl,--gc-sections is used, then also define -Wl,--undefined=arm_stack_area to keep the variable in RAM.
  The name of the variable (here: arm_stack_area) does not matter.

  Heap (=dynamic memory allocation) is not supported
*/
#ifndef __STACK_SIZE
#define __STACK_SIZE 0x100
#endif
unsigned char arm_stack_area[__STACK_SIZE] __attribute__ ((section(".stack"))) __attribute__ ((aligned(8)));

/* declaration of the main procedure to avoid the gcc warning */
int main(void);

/*=======================================================================*/
/* isr system procedures */

/* make the top of the stack known to the c compiler, value will be calculated by the linker script */
void __StackTop(void);

void __attribute__ ((interrupt)) __attribute__ ((noreturn)) Reset_Handler(void)
{
  register unsigned long *ptr;
  register unsigned long *start;
  register unsigned long *end;

  /*     
  Loop to copy data from read only memory to RAM. The ranges
  of copy from/to are specified by following symbols evaluated in 
  linker script.
  __etext: End of code section, i.e., begin of data sections to copy from.
  __data_start__/__data_end__: RAM address range that data should be
  copied to. Both must be aligned to 4 bytes boundary.  
  */
  extern unsigned long __data_start__[];
  extern unsigned long __data_end__[];
  extern unsigned long __etext[];
  ptr = __etext;
  start = __data_start__;
  end = __data_end__;
  while( start < end )
  {
    *start = *ptr;
    start++;
    ptr++;
  }
  
  /*
  Loop to zero out BSS section, which uses following symbols
  in linker script:
  __bss_start__: start of BSS section. Must align to 4
  __bss_end__: end of BSS section. Must align to 4
  */
  extern unsigned long __bss_start__[];
  extern unsigned long __bss_end__[];
  ptr = __bss_start__;
  end = __bss_end__;
  while( ptr < end )
  {
    *ptr = 0;
    ptr++;
  }

  /* Call main procedure */  
  main();
  
  /* finished, do nothing. */
  for(;;)
    ;
}

/* declare the SysTick_Handler only. It must be defined in the user code */
void __attribute__ ((interrupt)) SysTick_Handler(void);


/* "NMI_Handler" is used in the ld script to calculate the checksum */
void __attribute__ ((interrupt)) NMI_Handler(void)
{
}

/* "HardFault_Handler" is used in the ld script to calculate the checksum */
void __attribute__ ((interrupt)) HardFault_Handler(void)
{
}

/* make the checksum known to the c compiler, value will be calculated by the linker script */
void LPC_checksum(void);

/*=======================================================================*/
/* isr vector */

typedef void (*isr_handler_t)(void);
isr_handler_t __isr_vector[48] __attribute__ ((section(".isr_vector"))) __attribute__ ((aligned(4)))= 
{
  __StackTop,			/* Top of Stack, calculated by the linker script */
  Reset_Handler,		/* Reset Handler, DO NOT CHANGE THE ISR NAME (used for LPC_checksum calculation) */
  NMI_Handler,			/* NMI Handler, DO NOT CHANGE THE ISR NAME (used for LPC_checksum calculation) */
  HardFault_Handler,         /* Hard Fault Handler, DO NOT CHANGE THE ISR NAME (used for LPC_checksum calculation) */
  0,                                /* MemManage_Handler, must be 0 */
  0,                                /* BusFault_Handler, must be 0 */
  0,                                /* UsageFault_Handler, must be 0 */
  LPC_checksum,           /* Checksum, calculated by the linker script or the flash utility */
  0,                                /* Reserved */
  0,                                /* Reserved */
  0,                                /* Reserved */
  0,                                /* SVCall Handler */
  0,                                /* Reserved */
  0,                                /* Reserved */
  0,                                /* PendSV Handler */
  SysTick_Handler,         /* SysTick Handler */            
  
  0,  					/* SPI0 controller */
  0, 					/* SPI1 controller */
  0,					/* Reserved */
  0,					/* UART0 */
  0,					/* UART1 */
  0, 					/* UART2 */
  0,					/* Reserved */
  0,					/* Reserved */
  0,					/* I2C controller */
  0,					/* SCT */
  0,					/* Multi-Rate Timer */
  0,					/* Comparator */
  0,					/* WDT */
  0,					/* BOD Brown Out Detect */
  0,					/* Reserved */
  0,					/* WKT Self wake-up timer */
  0,					/* Reserved */
  0,					/* Reserved */
  0,					/* Reserved */
  0,					/* Reserved */
  0,					/* Reserved */
  0,					/* Reserved */
  0,					/* Reserved */
  0,					/* Reserved */
  0,					/* PIO INT0 */
  0,					/* PIO INT1 */
  0,					/* PIO INT2 */
  0,					/* PIO INT3 */
  0,					/* PIO INT4 */
  0,					/* PIO INT5 */
  0,					/* PIO INT6 */
  0					/* PIO INT7 */                      
};



/* the following .ld file is required for this c-code */
#ifdef THIS_IS_JUST_A_COMMENT
/* source: gcc-arm-none-eabi-4_7-2013q1/share/gcc-arm-none-eabi/samples/ldscripts/mem.ld */

/* Linker script to configure memory regions. 
 * Need modifying for a specific board. 
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   RAM.ORIGIN: starting address of RAM bank 0
 *   RAM.LENGTH: length of RAM bank 0
 */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x1000 /* 4K */
  RAM (rwx) : ORIGIN = 0x10000000, LENGTH = 0x0400 /* 1K */
}

/* source: gcc-arm-none-eabi-4_7-2013q1/share/gcc-arm-none-eabi/samples/ldscripts/sections.ld */

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 * 
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */
 
/* entry point */
ENTRY(Reset_Handler)

/* extern declaration so that the value appears correctly for the LPC checksum calculation */
EXTERN(NMI_Handler)
EXTERN(HardFault_Handler)

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text*)

		KEEP(*(.init))
		KEEP(*(.fini))

		/* .ctors */
		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)

		/* .dtors */
 		*crtbegin.o(.dtors)
 		*crtbegin?.o(.dtors)
 		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
 		*(SORT(.dtors.*))
 		*(.dtors)

		*(.rodata*)

		KEEP(*(.eh_frame*))
	} > FLASH

	.ARM.extab : 
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > FLASH

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH
	__exidx_end = .;

	__etext = .;
		
	.data : AT (__etext)
	{
		__data_start__ = .;
		*(vtable)
		*(.data*)

		. = ALIGN(4);
		/* preinit data */
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);

		. = ALIGN(4);
		/* init data */
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);


		. = ALIGN(4);
		/* finit data */
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);

		KEEP(*(.jcr*))
		. = ALIGN(4);
		/* All data end */
		__data_end__ = .;

	} > RAM

	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM
	
	.heap (COPY):
	{
		__end__ = .;
		end = __end__;
		*(.heap*)
		__HeapLimit = .;
	} > RAM

	/* .stack_dummy section doesn't contains any symbols. It is only
	 * used for linker to calculate size of stack sections, and assign
	 * values to stack symbols later */
	.stack_dummy (COPY):
	{
		*(.stack*)
	} > RAM

	/* Set stack top to end of RAM, and stack limit move down by
	 * size of stack_dummy section */
	__StackTop = ORIGIN(RAM) + LENGTH(RAM);
	__StackLimit = __StackTop - SIZEOF(.stack_dummy);
	PROVIDE(__stack = __StackTop);
	
	/* Check if data + heap + stack exceeds RAM limit */
	ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
	
	/* http://www.lpcware.com/content/forum/lpc1788-flash-signature-generation */
	LPC_checksum = 0- (__StackTop + Reset_Handler + NMI_Handler + HardFault_Handler + 3 /* three entries */);
}
#endif /* COMMENT */

