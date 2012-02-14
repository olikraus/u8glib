/*

  u8g_pb8h8.c
  
  8 bits per pixel, horizontal
  
  

#define WIDTH 128
#define PAGE_HEIGHT 8
#define HEIGHT 128

uint8_t u8g_index_color_8h8_buf[WIDTH*PAGE_HEIGHT] U8G_NOCOMMON ; 
u8g_pb_t u8g_index_color_8h8_pb = { {PAGE_HEIGHT, HEIGHT, 0, 0, 0},  WIDTH, u8g_index_color_8h8_buff}; 
u8g_dev_t name = { dev_fn, &u8g_index_color_8h8_pb, com_fn }

*/