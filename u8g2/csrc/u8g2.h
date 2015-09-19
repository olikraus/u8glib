/*
  u8g2.h
  
  
  
  
  U8glib has several layers. Each layer is implemented with a callback function. 
  This callback function handels the messages for the layer.

  The topmost level is the display layer. It includes the following messages:
  
    U8G2_MSG_DISPLAY_INIT
    U8G2_MSG_DISPLAY_POWER_UP
    U8G2_MSG_DISPLAY_SET_CONTRAST
    U8G2_MSG_DISPLAY_DRAW_TILE
    U8G2_MSG_DISPLAY_GET_LAYOUT
    U8G2_MSG_DISPLAY_POWER_DOWN

  A display driver may decided to breakdown these messages to a lower level interface or
  implement this functionality directly.
  

  One layer is the Command/Arg/Data interface. It can be used by the display layer
  to communicate with the display hardware.
  This layer only deals with data, commands and arguments. D/C line is unknown.
    U8G2_MSG_CAD_INIT
    U8G2_MSG_CAD_SET_I2C_ADR
    U8G2_MSG_CAD_SET_DEVICE
    U8G2_MSG_CAD_START_TRANSFER
    U8G2_MSG_CAD_SEND_CMD
    U8G2_MSG_CAD_SEND_ARG
    U8G2_MSG_CAD_SEND_DATA
    U8G2_MSG_CAD_END_TRANSFER
    
  The byte interface is there to send 1 byte (8 bits) to the display hardware.
  This layer depends on the hardware of a microcontroller, if a specific hardware 
  should be used (I2C or SPI). 
  If this interface is implemented via software, it may use the GPIO level for sending
  bytes.
    U8G2_MSG_BYTE_INIT
    U8G2_MSG_BYTE_SEND 30
    U8G2_MSG_BYTE_SET_DC 31
    U8G2_MSG_BYTE_START_TRANSFER
    U8G2_MSG_BYTE_END_TRANSFER
    U8G2_MSG_BYTE_SET_I2C_ADR
    U8G2_MSG_BYTE_SET_DEVICE

  GPIO and Delay
    U8G2_MSG_GPIO_INIT
    U8G2_MSG_DELAY_MILLI
    U8G2_MSG_DELAY_10MICRO
    U8G2_MSG_DELAY_100NANO
  
*/

#ifndef _U8G2_H
#define _U8G2_H

/* global defines */


/* Undefine this to remove u8g2_display_SetFlipMode function */
#define U8G2_WITH_FLIP_MODE

/* Select 0 or 1 for the default flip mode. This is not affected by U8G2_WITH_FLIP_MODE */
#define U8G2_DEFAULT_FLIP_MODE 0



#include <stdint.h>
#include <stddef.h>

#if defined(__GNUC__) && defined(__AVR__)
#include <avr/pgmspace.h>
#endif 

#ifdef __cplusplus
extern "C" {
#endif





#ifdef __GNUC__
#  define U8G2_NOINLINE __attribute__((noinline))
#else
#  define U8G2_NOINLINE
#endif

#if defined(__GNUC__) && defined(__AVR__)
#  define U8G2_SECTION(name) __attribute__ ((section (name)))
#  define U8G2_FONT_SECTION(name) U8G2_SECTION(".progmem." name)
#  define u8g2_pgm_read(adr) pgm_read_byte_near(adr)
#endif

#ifndef U8G2_SECTION
#  define U8G2_SECTION(name) __attribute__ ((section (name)))
#  define U8G2_FONT_SECTION(name) 
#  define u8g2_pgm_read(adr) (*(const uint8_t *)(adr)) 
#endif



typedef struct u8g2_struct u8g2_t;
typedef struct u8g2_display_info_struct u8g2_display_info_t;

typedef struct u8g2_tile_struct u8g2_tile_t;



typedef uint8_t (*u8g2_msg_cb)(u8g2_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr);


//struct u8g2_mcd_struct
//{
//  u8g2_msg_cb cb;		/* current callback function */
//  u8g2_t *u8g2;		/* pointer to the u8g2 parent to minimize the number of args */
//  u8g2_mcd_t *next;
//};

struct u8g2_tile_struct
{
  uint8_t *tile_ptr;	/* pointer to one or more tiles */
  uint8_t cnt;		/* number of tiles */
  uint8_t x_pos;	/* tile x position */
  uint8_t y_pos;	/* tile x position */
};


struct u8g2_display_info_struct
{
  /* == general == */

  uint8_t chip_enable_level;			/* UC1601: 0 */
  uint8_t chip_disable_level;			/* opposite of chip_enable_level */
  
  uint8_t post_chip_enable_wait_ns;		/* UC1601: 5ns */
  uint8_t pre_chip_disable_wait_ns;		/* UC1601: 5ns */
  uint8_t reset_pulse_width_ms;		/* UC1601: 0.003ms --> 1ms */ 
  uint8_t post_reset_wait_ms;			/* UC1601: 6ms  */ 
  
  
  /* == SPI interface == */
  
  /* after SDA has been applied, wait this much time for the SCK data takeover edge */
  uint8_t sda_setup_time_ns;		/* UC1601: 12ns */
  /* the pulse width of the the clock signal, cycle time is twice this value */
  /* max freq is 1/(2*sck_pulse_width_ns) */
  uint8_t sck_pulse_width_ns;		/* UC1601: 15ns */
  /* data takeover edge:  0=falling edge, 1=rising edge*/
  /* initial default value for sck is low (0) for falling edge and high for rising edge */
  uint8_t sck_takeover_edge;		/* UC1601: rising edge (1) */
  
  /* == I2C == */
  uint8_t i2c_bus_clock_100kHz;		/* UC1601: 1000000000/275 = 37 *100k */

  
  /* == 8 bit interface == */
  
  /* how long to wait after all data line are set */
  uint8_t data_setup_time_ns;		/* UC1601: 30ns */
  /* write enable pulse width */
  uint8_t write_pulse_width_ns;		/* UC1601: 40ns */
  
  /* == layout == */
  uint8_t tile_width;
  uint8_t tile_height;

  uint8_t default_x_offset;	/* default x offset for the display */

};

struct u8g2_struct
{
  //u8g2_t *u8g2_root;	/* root of the message call chain */
  u8g2_display_info_t *display_info;
  u8g2_msg_cb display_cb;
  u8g2_msg_cb cad_cb;
  u8g2_msg_cb byte_cb;
  u8g2_msg_cb gpio_and_delay_cb;
  const uint8_t *font;
  uint8_t x_offset;	/* copied from info struct, can be modified in flip mode */
};


/*==========================================*/
/* Display Interface */

/*
  Name: 	U8G2_MSG_DISPLAY_INIT
  Args:	None
  Tasks:
    1) setup u8g2->display_info
    2) put interface into default state
    3) execute display reset (gpio interface)
    4) send setup sequence to display, do not activate display, "power on" will follow 
*/
#define U8G2_MSG_DISPLAY_INIT 10

/* no args */
#define U8G2_MSG_DISPLAY_POWER_DOWN 11

/* no args */
#define U8G2_MSG_DISPLAY_POWER_UP 12

/* arg_int: 0 normal, 1: flip */
#define U8G2_MSG_DISPLAY_SET_FLIP_MODE 13

/*  arg_int: 0..255 contrast value */
#define U8G2_MSG_DISPLAY_SET_CONTRAST 14

/*  arg_ptr: u8g2_tile_t */
#define U8G2_MSG_DISPLAY_DRAW_TILE 15

/*  arg_ptr: layout struct */
#define U8G2_MSG_DISPLAY_GET_LAYOUT 16

/* u8g2_display.c */
uint8_t u8g2_display_DrawTile(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t cnt, uint8_t *tile_ptr);

/* Init display, but keep display in power save mode. Usually this command must be followed by u8g2_display_PowerUp() */
void u8g2_display_Init(u8g2_t *u8g2);
/* wake up display from power save mode */
void u8g2_display_PowerUp(u8g2_t *u8g2);
void u8g2_display_PowerDown(u8g2_t *u8g2);
void u8g2_display_SetFlipMode(u8g2_t *u8g2, uint8_t mode);
void u8g2_display_ClearScreen(u8g2_t *u8g2);



/*==========================================*/
/* Command Arg Data (CAD) Interface */

/*
  U8G2_MSG_CAD_INIT
    no args
    call U8G2_MSG_BYTE_INIT
    setup default values for the I/O lines
*/
#define U8G2_MSG_CAD_INIT 20


#define U8G2_MSG_CAD_SEND_CMD 21
/*  arg_int: cmd byte */
#define U8G2_MSG_CAD_SEND_ARG 22
/*  arg_int: arg byte */
#define U8G2_MSG_CAD_SEND_DATA 23
/* arg_int: expected cs level after processing this msg */
#define U8G2_MSG_CAD_START_TRANSFER 24
/* arg_int: expected cs level after processing this msg */
#define U8G2_MSG_CAD_END_TRANSFER 25
/* arg_int = 0: disable chip, arg_int = 1: enable chip */
#define U8G2_MSG_CAD_SET_I2C_ADR 26
#define U8G2_MSG_CAD_SET_DEVICE 27



/* u8g_cad.c */

#define u8g2_cad_Init(u8g2) ((u8g2)->cad_cb((u8g2), U8G2_MSG_CAD_INIT, 0, NULL ))

uint8_t u8g2_cad_SendCmd(u8g2_t *u8g2, uint8_t cmd) U8G2_NOINLINE;
uint8_t u8g2_cad_SendArg(u8g2_t *u8g2, uint8_t arg) U8G2_NOINLINE;
uint8_t u8g2_cad_SendData(u8g2_t *u8g2, uint8_t cnt, uint8_t *data) U8G2_NOINLINE;
uint8_t u8g2_cad_StartTransfer(u8g2_t *u8g2) U8G2_NOINLINE;
uint8_t u8g2_cad_EndTransfer(u8g2_t *u8g2) U8G2_NOINLINE;

/*
#define U8G2_C(c0)				(0x04), (c0)
#define U8G2_CA(c0,a0)			(0x05), (c0), (a0)
#define U8G2_CAA(c0,a0,a1)		(0x06), (c0), (a0), (a1)
#define U8G2_DATA()			(0x10)
#define U8G2_D1(d0)			(0x11), (d0)
*/

#define U8G2_C(c0)				(U8G2_MSG_CAD_SEND_CMD), (c0)
#define U8G2_CA(c0,a0)			(U8G2_MSG_CAD_SEND_CMD), (c0), (U8G2_MSG_CAD_SEND_ARG), (a0)
#define U8G2_CAA(c0,a0,a1)		(U8G2_MSG_CAD_SEND_CMD), (c0), (U8G2_MSG_CAD_SEND_ARG), (a0), (U8G2_MSG_CAD_SEND_ARG), (a1)
#define U8G2_D1(d0)			(U8G2_MSG_CAD_SEND_DATA), (d0)


#define U8G2_START_TRANSFER()	(U8G2_MSG_CAD_START_TRANSFER)
#define U8G2_END_TRANSFER()	(U8G2_MSG_CAD_END_TRANSFER)
#define U8G2_DLY(m)			(0xfe),(m)
#define U8G2_END()			(0xff)

void u8g2_cad_SendSequence(u8g2_t *u8g2, uint8_t const *data);
uint8_t u8g2_cad_110(u8g2_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8g2_cad_001(u8g2_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr);


/*==========================================*/
/* Byte Interface */

#define U8G2_MSG_BYTE_INIT U8G2_MSG_CAD_INIT
#define U8G2_MSG_BYTE_SET_DC 32

#define U8G2_MSG_BYTE_SEND U8G2_MSG_CAD_SEND_DATA

#define U8G2_MSG_BYTE_START_TRANSFER U8G2_MSG_CAD_START_TRANSFER
#define U8G2_MSG_BYTE_END_TRANSFER U8G2_MSG_CAD_END_TRANSFER

#define U8G2_MSG_BYTE_SET_I2C_ADR U8G2_MSG_CAD_SET_I2C_ADR
#define U8G2_MSG_BYTE_SET_DEVICE U8G2_MSG_CAD_SET_DEVICE


uint8_t u8g2_byte_SetDC(u8g2_t *u8g2, uint8_t dc) U8G2_NOINLINE;
uint8_t u8g2_byte_SendByte(u8g2_t *u8g2, uint8_t byte) U8G2_NOINLINE;
uint8_t u8g2_byte_SendBytes(u8g2_t *u8g2, uint8_t cnt, uint8_t *data) U8G2_NOINLINE;

/*==========================================*/
/* GPIO Interface */


/*
  U8G2_MSG_GPIO_AND_DELAY_INIT
  no args
  setup port directions, do not set IO levels, this is done with BYTE/CAD_INIT
*/
#define U8G2_MSG_GPIO_AND_DELAY_INIT 40

/* arg_int: milliseconds */
#define U8G2_MSG_DELAY_MILLI		41

#define U8G2_MSG_DELAY_10MICRO		42
#define U8G2_MSG_DELAY_100NANO		43
#define U8G2_MSG_DELAY_NANO		44

#define U8G2_MSG_GPIO_DC 45
#define U8G2_MSG_GPIO_CS 46		
#define U8G2_MSG_GPIO_RESET 47

#define u8g2_gpio_Init(u8g2) ((u8g2)->gpio_and_delay_cb((u8g2), U8G2_MSG_GPIO_AND_DELAY_INIT, 0, NULL ))

/*
#define u8g2_gpio_SetDC(u8g2, v) ((u8g2)->gpio_and_delay_cb((u8g2), U8G2_MSG_GPIO_DC, (v), NULL ))
#define u8g2_gpio_SetCS(u8g2, v) ((u8g2)->gpio_and_delay_cb((u8g2), U8G2_MSG_GPIO_CS, (v), NULL ))
#define u8g2_gpio_SetReset(u8g2, v) ((u8g2)->gpio_and_delay_cb((u8g2), U8G2_MSG_GPIO_RESET, (v), NULL ))
*/

#define u8g2_gpio_SetDC(u8g2, v) u8g2_gpio_call(u8g2, U8G2_MSG_GPIO_DC, (v))
#define u8g2_gpio_SetCS(u8g2, v) u8g2_gpio_call(u8g2, U8G2_MSG_GPIO_CS, (v))
#define u8g2_gpio_SetReset(u8g2, v) u8g2_gpio_call(u8g2, U8G2_MSG_GPIO_CS, (v))

void u8g2_gpio_call(u8g2_t *u8g2, uint8_t msg, uint8_t arg) U8G2_NOINLINE;

#define u8g2_gpio_Delay(u8g2, msg, dly) u8g2_gpio_call((u8g2), (msg), (dly))
//void u8g2_gpio_Delay(u8g2_t *u8g2, uint8_t msg, uint8_t dly) U8G2_NOINLINE;


/*==========================================*/
/* u8g2.c */
void u8g2_SetupDefaults(u8g2_t *u8g2);


/*==========================================*/
/* u8g2_d_stdio.c */
void u8g2_SetupStdio(u8g2_t *u8g2);

/*==========================================*/
/* u8g2_d_uc1701_dogs102.c */
uint8_t u8g2_d_uc1701_dogs102(u8g2_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr);

/*==========================================*/
/* u8g2_d_ssd1306_128x64_noname.c */
uint8_t u8g2_d_ssd1306_128x64_noname(u8g2_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr);

/*==========================================*/
/* u8g2_8x8.c */
void u8g2_Set8x8Font(u8g2_t *u8g2, const uint8_t *font_8x8);
void u8g2_Draw8x8Glyph(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t encoding);
void u8g2_Draw8x8String(u8g2_t *u8g2, uint8_t x, uint8_t y, const char *s);


#ifdef __cplusplus
}
#endif


#endif  /* _U8G2_H */

