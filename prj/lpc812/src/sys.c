/*
    
  sys.c

  System Code for the LPC81x ARM Controller.
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
#include "sys.h"
#include "port.h"
#include "clk.h"
#include "key.h"

/* SDA bit position in port 0 */
//#define I2C_SDA_PIN 0
#define I2C_SDA_PIN 11
/* register index within LPC_IOCON */
//#define I2C_SDA_IDX 0x011
#define I2C_SDA_IDX 0x07

/* SCL bit position in port 0 */
//#define I2C_SCL_PIN 3
#define I2C_SCL_PIN 10
/* register index within LPC_IOCON */
//#define I2C_SCL_IDX 0x05
#define I2C_SCL_IDX 0x08


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



/*=======================================================================*/
/* generic  i2c (http://en.wikipedia.org/wiki/I%C2%B2C) */
/* SCL: 0_3 */
/* SDA: 0_0 */

#define I2C_DLY 1

uint8_t i2c_started = 0;

static void i2c_delay(void)
{
  /* should be at least 4 */
  /* should be 5 for 100KHz transfer speed */
  
  delay_micro_seconds(4);
}

const uint16_t pcs_i2c_init[] = 
{
  PCS_BASE(LPC_IOCON_BASE),
  
  /* SDA */
  /* Chip_IOCON_PinSetMode(LPC_IOCON,IOCON_PIO0,PIN_MODE_INACTIVE); */
  /* PIO0 is at index 0x11, Clear both mode bits to disable pull up/down */
  PCS_CLRB(3, I2C_SDA_IDX),
  PCS_CLRB(4, I2C_SDA_IDX),

  /* SCL */
  /* Chip_IOCON_PinSetMode(LPC_IOCON,IOCON_PIO3,PIN_MODE_INACTIVE); */
  /* PIO3 is at index 0x5, Clear both mode bits to disable pull up/down */
  PCS_CLRB(3, I2C_SCL_IDX),
  PCS_CLRB(4, I2C_SCL_IDX),
  
  /* Chip_IOCON_PinEnableOpenDrainMode(LPC_IOCON, IOCON_PIO0); */
  /* PIO0 is at index 0x11, Open Drain is bit 10 */
  PCS_SETB(10, I2C_SDA_IDX),
  /* Chip_IOCON_PinEnableOpenDrainMode(LPC_IOCON, IOCON_PIO3); */
  /* PIO3 is at index 0x5, Open Drain is bit 10 */
  PCS_SETB(10, I2C_SCL_IDX),
  
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  // SCL
  //Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 3);
  PCS_SETB(I2C_SCL_PIN, 0x280/4),

  // SDA
  //Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 0, 0);
  PCS_SETB(I2C_SDA_PIN, 0x280/4),
  // delay
  PCS_DLY(I2C_DLY) | PCS_END
};


/* maybe this can be optimized */
void i2c_init(void)
{
  pcs(pcs_i2c_init);
}


/* actually, the scl line is not observed, so this procedure does not return a value */
const uint16_t pcs_i2c_read_scl_and_delay[] = 
{  
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
//Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 3);
  PCS_CLRB(I2C_SCL_PIN, 0x000/4),
  PCS_DLY(I2C_DLY) | PCS_END
};

/* actually, the scl line is not observed, so this procedure does not return a value */
void i2c_read_scl_and_delay(void)
{
  pcs(pcs_i2c_read_scl_and_delay);
}

const uint16_t pcs_i2c_clear_scl[] = 
{  
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
//Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 3);
//LPC_GPIO_PORT->DIR[0] |= 1UL << 3;
  PCS_SETB(I2C_SCL_PIN, 0x000/4) | PCS_END
};


void __attribute__ ((noinline)) i2c_clear_scl(void)
{
  /* set open collector and drive low */
  pcs(pcs_i2c_clear_scl);
}

const uint16_t pcs_i2c_read_sda[] = 
{  
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
//Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 3);
  PCS_CLRB(I2C_SDA_PIN, 0x000/4), 
  PCS_GETB(I2C_SDA_PIN, 0x100/4) | PCS_END
};


uint8_t __attribute__ ((noinline)) i2c_read_sda(void)
{
  //Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 0, 0);
  return pcs(pcs_i2c_read_sda);
  //return Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, 0, 0);  
}

const uint16_t pcs_i2c_clear_sda[] = 
{  
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
//Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 3);
//LPC_GPIO_PORT->DIR[0] |= 1UL << 3;
  PCS_SETB(I2C_SDA_PIN, 0x000/4) | PCS_END
};

void __attribute__ ((noinline)) i2c_clear_sda(void)
{
  /* set open collector and drive low */
  pcs(pcs_i2c_clear_sda);
  // Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 0);
}

const uint16_t pcs_i2c_restart[] = 
{
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  // read sda / set high
  PCS_CLRB(I2C_SDA_PIN, 0x000/4), 
  // delay
  PCS_DLY(I2C_DLY),
  // read scl
  PCS_CLRB(I2C_SCL_PIN, 0x000/4),
  PCS_DLY(I2C_DLY) | PCS_END
};

const uint16_t pcs_i2c_start[] = 
{
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  // read sda / set high
  PCS_CLRB(I2C_SDA_PIN, 0x000/4), 
  // clear sda / set low
  PCS_SETB(I2C_SDA_PIN, 0x000/4),
  // delay
  PCS_DLY(I2C_DLY),
  // clear scl
  PCS_SETB(I2C_SCL_PIN, 0x000/4) | PCS_END
};

void i2c_start(void) 
{
  if ( i2c_started != 0 ) 
  { 
    /* if already started: do restart */
    //i2c_read_sda();	/* SDA = 1 */
    //i2c_delay();
    //i2c_read_scl_and_delay();
    pcs(pcs_i2c_restart);
  }
  //i2c_read_sda();
  /* send the start condition, both lines go from 1 to 0 */
  //i2c_clear_sda();
  //i2c_delay();
  //i2c_clear_scl();
  
  pcs(pcs_i2c_start);
  i2c_started = 1;
}

const uint16_t pcs_i2c_stop[] = 
{
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  // clear sda / set low
  PCS_SETB(I2C_SDA_PIN, 0x000/4),
  // delay
  PCS_DLY(I2C_DLY),
  // read scl */
  PCS_CLRB(I2C_SCL_PIN, 0x000/4),
  // delay
  PCS_DLY(I2C_DLY),
  // read sda
  PCS_CLRB(I2C_SDA_PIN, 0x000/4), 
  // delay
  PCS_DLY(I2C_DLY) | PCS_END
};

void i2c_stop(void)
{
  /* set SDA to 0 */
  //i2c_clear_sda();  
  //i2c_delay();
  
  /* now release all lines */
  //i2c_read_scl_and_delay();
  
  /* set SDA to 1 */
  //i2c_read_sda();
  //i2c_delay();
  pcs(pcs_i2c_stop);
  i2c_started = 0;
}

const uint16_t pcs_i2c_write_1[] = 
{
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  // read sda
  PCS_CLRB(I2C_SDA_PIN, 0x000/4), 
  // delay
  //PCS_DLY(I2C_DLY),
  // read scl */
  PCS_CLRB(I2C_SCL_PIN, 0x000/4),
  // delay
  //PCS_DLY(I2C_DLY),
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),		// use BASE command for delay --> 90KHz
  // clear scl
  PCS_SETB(I2C_SCL_PIN, 0x000/4) | PCS_END
};

const uint16_t pcs_i2c_write_0[] = 
{
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  // clear sda / set low
  PCS_SETB(I2C_SDA_PIN, 0x000/4),
  // delay
  //PCS_DLY(I2C_DLY),
  // read scl */
  PCS_CLRB(I2C_SCL_PIN, 0x000/4),
  // delay
  //PCS_DLY(I2C_DLY),
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),		// use BASE command for delay --> 90KHz
  // clear scl
  PCS_SETB(I2C_SCL_PIN, 0x000/4) | PCS_END
};

void __attribute__ ((noinline)) i2c_write_bit(uint8_t val) 
{
  if ( val )
    pcs(pcs_i2c_write_1);
  else
    pcs(pcs_i2c_write_0);
  /*
  if (val)
    i2c_read_sda();
  else
    i2c_clear_sda();
  
  i2c_delay();
  i2c_read_scl_and_delay();
  i2c_clear_scl();
  */
}

const uint16_t pcs_i2c_read_bit[] = 
{
  PCS_BASE(LPC_GPIO_PORT_BASE+0x2000),
  // read sda
  PCS_CLRB(I2C_SDA_PIN, 0x000/4), 
  // delay
  PCS_DLY(I2C_DLY),
  // read scl */
  PCS_CLRB(I2C_SCL_PIN, 0x000/4),
  // delay
  PCS_DLY(I2C_DLY),
  // really read value from sda
  PCS_GETB(I2C_SDA_PIN, 0x100/4),
  // delay
  PCS_DLY(I2C_DLY),
  // clear scl
  PCS_SETB(I2C_SCL_PIN, 0x000/4) | PCS_END
};

unsigned __attribute__ ((noinline)) i2c_read_bit(void) 
{
  return pcs(pcs_i2c_read_bit);
  //uint8_t val;
  /* do not drive SDA */
  /*
  i2c_read_sda();
  i2c_delay();
  i2c_read_scl_and_delay();
  val = i2c_read_sda();
  i2c_delay();
  i2c_clear_scl();
  return val;
  */
}

unsigned __attribute__ ((noinline)) i2c_write_byte(unsigned b)
{
  unsigned i = 8;
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

/*
  nack must be 0 if the data reading continues
  nack should be 1 after the last byte. send stop after this
*/
unsigned __attribute__ ((noinline)) i2c_read_byte(unsigned nack)
{
  unsigned i = 8;
  unsigned b = 0;
  do
  {
    b <<= 1;
    b |= i2c_read_bit();
    i--;
  } while ( i != 0 );
  i2c_write_bit(nack);
  return b;
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
void __attribute__ ((interrupt)) SysTick_Handler(void)
{
  clk_irq();
  key_irq();
}


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

		/* remove _init and _fini prcedures */
		/*
		KEEP(*(.init))
		KEEP(*(.fini))
		*/
  
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

		/* remove __EH_FRAME_BEGIN__ */
		/* KEEP(*(.eh_frame*)) */
		. = ALIGN(4);
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
		/*
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
		*/


		. = ALIGN(4);
		/* finit data */
		/*
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);
		*/

		/* KEEP(*(.jcr*)) */
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

