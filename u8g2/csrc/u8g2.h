/*
  u8g2.h
  
  
  
  
  U8glib has several layers. Each layer is implemented with a callback function. 
  This callback function handels the messages for the layer.

  The topmost level is the display layer. It includes the following messages:
  
    U8G2_MSG_DISPLAY_INIT
    U8G2_MSG_DISPLAY_POWER_DOWN
    U8G2_MSG_DISPLAY_POWER_UP
    U8G2_MSG_DISPLAY_SET_CONTRAST
    U8G2_MSG_DISPLAY_DRAW_TILE
    U8G2_MSG_DISPLAY_GET_LAYOUT

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

#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct u8g2_struct u8g2_t;
typedef struct u8g2_display_info_struct u8g2_display_info_t;

typedef struct u8g2_tile_struct u8g2_tile_t;



typedef uint8_t (*u8g2_msg_cb)(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr);


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
};

struct u8g2_struct
{
  //u8g2_t *u8g2_root;	/* root of the message call chain */
  u8g2_display_info_t *display_info;
  u8g2_msg_cb display_cb;
  u8g2_msg_cb cad_cb;
  u8g2_msg_cb byte_cb;
  u8g2_msg_cb gpio_and_delay_cb;
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

/*  arg_int: 0..255 contrast value */
#define U8G2_MSG_DISPLAY_SET_CONTRAST 13

/*  arg_ptr: u8g2_tile_t */
#define U8G2_MSG_DISPLAY_DRAW_TILE 14

/*  arg_ptr: layout struct */
#define U8G2_MSG_DISPLAY_GET_LAYOUT 15

/* u8g2_display.c */
uint8_t u8g2_display_DrawTile(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t cnt, uint8_t *tile_ptr);
void u8g2_display_Init(u8g2_t *u8g2);



/*==========================================*/
/* Command Arg Data (CAD) Interface */

#define U8G2_MSG_CAD_SEND_CMD 20
/*  arg_int: cmd byte */
#define U8G2_MSG_CAD_SEND_ARG 21
/*  arg_int: arg byte */
#define U8G2_MSG_CAD_SEND_DATA 22
/*  arg_int: # of data, arg_ptr = uint8_t * with data */
//#define U8G2_MSG_CAD_RESET 23
/* arg_int: expected cs level after processing this msg */
#define U8G2_MSG_CAD_START_TRANSFER 24
/* arg_int: expected cs level after processing this msg */
#define U8G2_MSG_CAD_END_TRANSFER 25
/* arg_int = 0: disable chip, arg_int = 1: enable chip */
#define U8G2_MSG_CAD_SET_I2C_ADR 26
#define U8G2_MSG_CAD_SET_DEVICE 27

/* u8g_cad.c */
uint8_t u8g2_cad_SendCmd(u8g2_t *u8g2, uint8_t cmd);
uint8_t u8g2_cad_SendArg(u8g2_t *u8g2, uint8_t arg);
uint8_t u8g2_cad_SendData(u8g2_t *u8g2, uint8_t cnt, uint8_t *data);
//uint8_t u8g2_cad_Reset1(u8g2_t *u8g2);
//uint8_t u8g2_cad_Reset0(u8g2_t *u8g2);
uint8_t u8g2_cad_StartTransfer(u8g2_t *u8g2, uint8_t cs);
uint8_t u8g2_cad_EndTransfer(u8g2_t *u8g2, uint8_t cs);

#define U8G2_C(c0)		(0x04), (c0)
#define U8G2_CA(c0,a0)		(0x05), (c0), (a0)
#define U8G2_CAA(c0,a0,a1)		(0x06), (c0), (a0), (a1)
#define U8G2_DATA()		(0x10)
#define U8G2_D1(d0)		(0x11), (d0)
#define U8G2_START_CS0()	(0xf0)
#define U8G2_START_CS1()	(0xf1)
#define U8G2_END_CS0()	(0xf2)
#define U8G2_END_CS1()	(0xf3)
#define U8G2_DLY(m)		(0xfe),(m)
#define U8G2_END()		(0xff)

void u8g2_cad_SendSequence(u8g2_t *u8g2, uint8_t const *data);
uint8_t u8g2_cad_110(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr);
uint8_t u8g2_cad_001(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr);


/*==========================================*/
/* Byte Interface */
#define U8G2_MSG_BYTE_SEND 30
#define U8G2_MSG_BYTE_SET_DC 31


#define U8G2_MSG_BYTE_START_TRANSFER U8G2_MSG_CAD_START_TRANSFER
#define U8G2_MSG_BYTE_END_TRANSFER U8G2_MSG_CAD_END_TRANSFER

#define U8G2_MSG_BYTE_SET_I2C_ADR U8G2_MSG_CAD_SET_I2C_ADR
#define U8G2_MSG_BYTE_SET_DEVICE U8G2_MSG_CAD_SET_DEVICE

uint8_t u8g2_byte_SetDC(u8g2_t *u8g2, uint8_t dc);
uint8_t u8g2_byte_Send(u8g2_t *u8g2, uint8_t byte);

/*==========================================*/
/* GPIO Interface */

/* arg_int: milliseconds */

#define U8G2_MSG_GPIO_AND_DELAY_INIT 40

#define U8G2_MSG_DELAY_MILLI		41

#define U8G2_MSG_DELAY_10MICRO		42
#define U8G2_MSG_DELAY_100NANO		43

#define U8G2_MSG_GPIO_DC 45
#define U8G2_MSG_GPIO_CS 46		
#define U8G2_MSG_GPIO_RESET 47

#define u8g2_gpio_Init(u8g2) ((u8g2)->gpio_and_delay_cb((u8g2), U8G2_MSG_GPIO_AND_DELAY_INIT, 0, NULL ))

#define u8g2_gpio_SetDC(u8g2, v) ((u8g2)->gpio_and_delay_cb((u8g2), U8G2_MSG_GPIO_DC, (v), NULL ))
#define u8g2_gpio_SetCS(u8g2, v) ((u8g2)->gpio_and_delay_cb((u8g2), U8G2_MSG_GPIO_CS, (v), NULL ))
#define u8g2_gpio_SetReset(u8g2, v) ((u8g2)->gpio_and_delay_cb((u8g2), U8G2_MSG_GPIO_RESET, (v), NULL ))

/*==========================================*/
/* u8g2.c */
void u8g2_Init(u8g2_t *u8g2);
//void u8g2_Chain(u8g2_t *u8g2, u8g2_t *u8g2, u8g2_msg_cb cb); OBSOLETE


/*==========================================*/
/* u8g2_d_stdio.c */
void u8g2_InitStdio(u8g2_t *u8g2);

/*==========================================*/
/* u8g2_d_uc1701_dogs102.c */
uint8_t u8g2_d_uc1701_dogs102(u8g2_t *u8g2, uint8_t msg, uint16_t arg_int, void *arg_ptr);


#ifdef __cplusplus
}
#endif


#endif  /* _U8G2_H */

