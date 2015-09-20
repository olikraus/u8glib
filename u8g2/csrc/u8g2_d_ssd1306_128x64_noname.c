
#include "u8g2.h"




static const uint8_t u8g2_d_ssd1306_128x64_noname_init_seq[] = {
    
  U8G2_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  
  
  U8G2_C(0x0ae),		                /* display off */
  U8G2_CA(0x0d5, 0x080),		/* clock divide ratio (0x00=1) and oscillator frequency (0x8) */
  U8G2_CA(0x0a8, 0x03f),		/* multiplex ratio */
  U8G2_CA(0x0d3, 0x000),		/* display offset */
  U8G2_C(0x040),		                /* set display start line to 0 */
  U8G2_CA(0x08d, 0x014),		/* [2] charge pump setting (p62): 0x014 enable, 0x010 disable */
  U8G2_CA(0x020, 0x000),		/* page addressing mode */
  
#if U8G2_DEFAULT_FLIP_MODE == 0 
  U8G2_C(0x0a1),				/* segment remap a0/a1*/
  U8G2_C(0x0c8),				/* c0: scan dir normal, c8: reverse */
#else
  U8G2_C(0x0a0),				/* segment remap a0/a1*/
  U8G2_C(0x0c0),				/* c0: scan dir normal, c8: reverse */
#endif
  
  U8G2_CA(0x0da, 0x012),		/* com pin HW config, sequential com pin config (bit 4), disable left/right remap (bit 5) */
  U8G2_CA(0x081, 0x0cf),		/* [2] set contrast control */
  U8G2_CA(0x0d9, 0x0f1),		/* [2] pre-charge period 0x022/f1*/
  U8G2_CA(0x0db, 0x040),		/* vcomh deselect level */
  
  U8G2_C(0x02e),				/* Deactivate scroll */ 
  U8G2_C(0x0a4),				/* output ram to display */
  U8G2_C(0x0a6),				/* none inverted normal display mode */
    
  U8G2_END_TRANSFER(),             	/* disable chip */
  U8G2_END()             			/* end of sequence */
};

static const uint8_t u8g2_d_ssd1306_128x64_noname_powersave0_seq[] = {
  U8G2_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  U8G2_C(0x0af),		                /* display on */
  U8G2_END_TRANSFER(),             	/* disable chip */
  U8G2_END()             			/* end of sequence */
};

static const uint8_t u8g2_d_ssd1306_128x64_noname_powersave1_seq[] = {
  U8G2_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  U8G2_C(0x0ae),		                /* display off */
  U8G2_END_TRANSFER(),             	/* disable chip */
  U8G2_END()             			/* end of sequence */
};

#ifdef U8G2_WITH_SET_FLIP_MODE
static const uint8_t u8g2_d_ssd1306_128x64_noname_flip0_seq[] = {
  U8G2_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  U8G2_C(0x0a1),				/* segment remap a0/a1*/
  U8G2_C(0x0c8),				/* c0: scan dir normal, c8: reverse */
  U8G2_END_TRANSFER(),             	/* disable chip */
  U8G2_END()             			/* end of sequence */
};

static const uint8_t u8g2_d_ssd1306_128x64_noname_flip1_seq[] = {
  U8G2_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  U8G2_C(0x0a0),				/* segment remap a0/a1*/
  U8G2_C(0x0c0),				/* c0: scan dir normal, c8: reverse */
  U8G2_END_TRANSFER(),             	/* disable chip */
  U8G2_END()             			/* end of sequence */
};
#endif

static u8g2_display_info_t u8g2_ssd1306_128x64_noname_display_info =
{
  /* chip_enable_level = */ 0,
  /* chip_disable_level = */ 1,
  
  /* post_chip_enable_wait_ns = */ 20,
  /* pre_chip_disable_wait_ns = */ 10,
  /* reset_pulse_width_ms = */ 100, 	/* SSD1306: 3 us */
  /* post_reset_wait_ms = */ 100, /* far east OLEDs need much longer setup time */
  /* sda_setup_time_ns = */ 15,
  /* sck_pulse_width_ns = */ 50,	/* SSD1306: 20ns, but cycle time is 100ns, so use 100/50 */
  /* sck_takeover_edge = */ 1,		/* rising edge */
  /* i2c_bus_clock_100kHz = */ 4,
  /* data_setup_time_ns = */ 40,
  /* write_pulse_width_ns = */ 150,	/* SSD1306: cycle time is 300ns, so use 300/2 = 150 */
  /* tile_width = */ 16,
  /* tile_hight = */ 8,
  /* default_x_offset = */ 0
};

uint8_t u8g2_d_ssd1306_128x64_noname(u8g2_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  uint8_t x, c;
  uint8_t *ptr;
  switch(msg)
  {
    case U8G2_MSG_DISPLAY_INIT:
      /* 1) set display info struct */
      u8g2->display_info = &u8g2_ssd1306_128x64_noname_display_info;
      u8g2->x_offset = u8g2->display_info->default_x_offset;
    
      /* 2) apply port directions to the GPIO lines and apply default values for the IO lines*/
      u8g2_gpio_Init(u8g2);
      u8g2_cad_Init(u8g2);

      /* 3) apply default value for chip select */
      u8g2_gpio_SetCS(u8g2, u8g2->display_info->chip_disable_level);
      /* no wait required here */
    
      /* 4) do reset */
      u8g2_gpio_SetReset(u8g2, 1);
      u8g2_gpio_Delay(u8g2, U8G2_MSG_DELAY_MILLI, u8g2->display_info->reset_pulse_width_ms);
      u8g2_gpio_SetReset(u8g2, 0);
      u8g2_gpio_Delay(u8g2, U8G2_MSG_DELAY_MILLI, u8g2->display_info->reset_pulse_width_ms);
      u8g2_gpio_SetReset(u8g2, 1);
      u8g2_gpio_Delay(u8g2, U8G2_MSG_DELAY_MILLI, u8g2->display_info->post_reset_wait_ms);
    
      /* 5) send startup code */
      u8g2_cad_SendSequence(u8g2, u8g2_d_ssd1306_128x64_noname_init_seq);
    
      break;
    case U8G2_MSG_DISPLAY_SET_POWER_SAVE:
      if ( arg_int == 0 )
	u8g2_cad_SendSequence(u8g2, u8g2_d_ssd1306_128x64_noname_powersave0_seq);
      else
	u8g2_cad_SendSequence(u8g2, u8g2_d_ssd1306_128x64_noname_powersave1_seq);
      break;
#ifdef U8G2_WITH_SET_FLIP_MODE
    case U8G2_MSG_DISPLAY_SET_FLIP_MODE:
      if ( arg_int == 0 )
	u8g2_cad_SendSequence(u8g2, u8g2_d_ssd1306_128x64_noname_flip0_seq);
      else
	u8g2_cad_SendSequence(u8g2, u8g2_d_ssd1306_128x64_noname_flip1_seq);
      break;
#endif
#ifdef U8G2_WITH_SET_CONTRAST
    case U8G2_MSG_DISPLAY_SET_CONTRAST:
      u8g2_cad_StartTransfer(u8g2);
      u8g2_cad_SendCmd(u8g2, 0x081 );
      u8g2_cad_SendArg(u8g2, arg_int );	/* ssd1306 has range from 0 to 255 */
      u8g2_cad_EndTransfer(u8g2);
      break;
#endif
    case U8G2_MSG_DISPLAY_DRAW_TILE:
      u8g2_cad_StartTransfer(u8g2);
      x = ((u8g2_tile_t *)arg_ptr)->x_pos;    
      x *= 8;
      x += u8g2->x_offset;
      u8g2_cad_SendCmd(u8g2, 0x010 | (x>>4) );
      u8g2_cad_SendCmd(u8g2, 0x000 | ((x&15)));
      u8g2_cad_SendCmd(u8g2, 0x0b0 | (((u8g2_tile_t *)arg_ptr)->y_pos));
      
      do
      {
	c = ((u8g2_tile_t *)arg_ptr)->cnt;
	ptr = ((u8g2_tile_t *)arg_ptr)->tile_ptr;
	do
	{
	  u8g2_cad_SendData(u8g2, 8, ptr);
	  ptr += 8;
	  c--;
	} while( c > 0 );
	arg_int--;
      } while( arg_int > 0 );
      
      u8g2_cad_EndTransfer(u8g2);
      break;
    default:
      return 0;
  }
  return 1;
}


