/*

  Many parts are taken over from m2tklib
  
*/


#include "u8g.h"
#include "SDL.h"
#include "SDL_video.h"
#include <assert.h>

#define HEIGHT (64)
#define WIDTH 128

SDL_Surface *u8g_sdl_screen;
int u8g_sdl_multiple = 2;
Uint32 u8g_sdl_color[256];

void u8g_sdl_set_pixel(int x, int y, int idx)
{
  Uint32  *ptr;
  Uint32 offset;
  int i, j;
  
  if ( y >= HEIGHT )
    return;
  if ( y < 0 )
    return;
  if ( x >= WIDTH )
    return;
  if ( x < 0 )
    return;
  
  for( i = 0; i < u8g_sdl_multiple; i++ )
    for( j = 0; j < u8g_sdl_multiple; j++ )
    {
      offset = 
	(y * u8g_sdl_multiple + j) * u8g_sdl_screen->w * u8g_sdl_screen->format->BytesPerPixel + 
	(x * u8g_sdl_multiple + i) * u8g_sdl_screen->format->BytesPerPixel;
      assert( offset < u8g_sdl_screen->w * u8g_sdl_screen->h * u8g_sdl_screen->format->BytesPerPixel );
      ptr = u8g_sdl_screen->pixels + offset;
      *ptr = u8g_sdl_color[idx];
    }
}

void u8g_sdl_set_hicolor(int x, int y, uint8_t low, uint8_t high)
{
  Uint32  *ptr;
  Uint32 offset;
  int i, j;
  unsigned int r, g, b;
  Uint32 color;

  if ( y >= HEIGHT )
    return;
  if ( y < 0 )
    return;
  if ( x >= WIDTH )
    return;
  if ( x < 0 )
    return;
  
  r = high & ~7;
  b = low & 31;
  b <<= 3;
  g = high & 7;
  g <<= 3;
  g |= (low>>5)&7;
  g <<= 2;
  
  color = SDL_MapRGB( u8g_sdl_screen->format, r, g, b );  
  for( i = 0; i < u8g_sdl_multiple; i++ )
    for( j = 0; j < u8g_sdl_multiple; j++ )
    {
      offset = 
	(y * u8g_sdl_multiple + j) * u8g_sdl_screen->w * u8g_sdl_screen->format->BytesPerPixel + 
	(x * u8g_sdl_multiple + i) * u8g_sdl_screen->format->BytesPerPixel;
      assert( offset < u8g_sdl_screen->w * u8g_sdl_screen->h * u8g_sdl_screen->format->BytesPerPixel );
      ptr = u8g_sdl_screen->pixels + offset;
      *ptr = color;
    }
  
}

void u8g_sdl_set_fullcolor(int x, int y, unsigned int r, unsigned int g, unsigned int b)
{
  Uint32  *ptr;
  Uint32 offset;
  int i, j;
  Uint32 color;

  if ( y >= HEIGHT )
    return;
  if ( y < 0 )
    return;
  if ( x >= WIDTH )
    return;
  if ( x < 0 )
    return;
  
  color = SDL_MapRGB( u8g_sdl_screen->format, r, g, b );  
  for( i = 0; i < u8g_sdl_multiple; i++ )
    for( j = 0; j < u8g_sdl_multiple; j++ )
    {
      offset = 
	(y * u8g_sdl_multiple + j) * u8g_sdl_screen->w * u8g_sdl_screen->format->BytesPerPixel + 
	(x * u8g_sdl_multiple + i) * u8g_sdl_screen->format->BytesPerPixel;
      assert( offset < u8g_sdl_screen->w * u8g_sdl_screen->h * u8g_sdl_screen->format->BytesPerPixel );
      ptr = u8g_sdl_screen->pixels + offset;
      *ptr = color;
    }
  
}

#define W(x,w) (((x)*(w))/100)

void u8g_sdl_init(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    printf("Unable to initialize SDL:  %s\n", SDL_GetError());
    exit(1);
  }
  
  /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_SetVideoMode */
  u8g_sdl_screen = SDL_SetVideoMode(WIDTH*u8g_sdl_multiple,HEIGHT*u8g_sdl_multiple,32,SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( u8g_sdl_screen == NULL ) 
  {
    printf("Couldn't set video mode: %s\n", SDL_GetError());
    exit(1);
  }
  printf("%d bits-per-pixel mode\n", u8g_sdl_screen->format->BitsPerPixel);
  printf("%d bytes-per-pixel mode\n", u8g_sdl_screen->format->BytesPerPixel);
  
  u8g_sdl_color[0] = SDL_MapRGB( u8g_sdl_screen->format, 0, 0, 0 );
  u8g_sdl_color[1] = SDL_MapRGB( u8g_sdl_screen->format, W(100, 50), W(255,50), 0 );
  u8g_sdl_color[2] = SDL_MapRGB( u8g_sdl_screen->format, W(100, 80), W(255,80), 0 );
  u8g_sdl_color[3] = SDL_MapRGB( u8g_sdl_screen->format, 100, 255, 0 );

  /*
  u8g_sdl_set_pixel(0,0);
  u8g_sdl_set_pixel(1,1);
  u8g_sdl_set_pixel(2,2);
  */

  /* update all */
  /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
  SDL_UpdateRect(u8g_sdl_screen, 0,0,0,0);

  atexit(SDL_Quit);
  return;
}

void u8g_sdl_init_R3G3B2(void)
{
  int r, g, b, idx;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    printf("Unable to initialize SDL:  %s\n", SDL_GetError());
    exit(1);
  }
  
  /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_SetVideoMode */
  u8g_sdl_screen = SDL_SetVideoMode(WIDTH*u8g_sdl_multiple,HEIGHT*u8g_sdl_multiple,32,SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( u8g_sdl_screen == NULL ) 
  {
    printf("Couldn't set video mode: %s\n", SDL_GetError());
    exit(1);
  }
  printf("%d bits-per-pixel mode\n", u8g_sdl_screen->format->BitsPerPixel);
  printf("%d bytes-per-pixel mode\n", u8g_sdl_screen->format->BytesPerPixel);
  

  idx = 0;
  for( r = 0; r < 8; r++ )
    for( g = 0; g < 8; g++ )
      for( b = 0; b < 4; b++ )
        u8g_sdl_color[idx++] = SDL_MapRGB( u8g_sdl_screen->format, (r*255)/7, (g*255)/7, (b*255)/3 );

  /*
  u8g_sdl_set_pixel(0,0);
  u8g_sdl_set_pixel(1,1);
  u8g_sdl_set_pixel(2,2);
  */

  
  {
    int x, y;
    for ( x = 0; x < 128; x++ )
      for ( y = 0; y < 64; y++ )
        u8g_sdl_set_pixel(x, y, (x+y)&255);
  }

  /* update all */
  /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
  SDL_UpdateRect(u8g_sdl_screen, 0,0,0,0);
  

  atexit(SDL_Quit);
  return;
}

void u8g_sdl_start(void)
{
  Uint32 color = SDL_MapRGB( u8g_sdl_screen->format, 0, 0, 0 );
  /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_FillRect */
  SDL_FillRect(u8g_sdl_screen, NULL, color);
  
  /*
  u8g_sdl_set_pixel(0,0,3);
  u8g_sdl_set_pixel(10,0,3);
  u8g_sdl_set_pixel(20,0,3);
  u8g_sdl_set_pixel(30,0,3);
  u8g_sdl_set_pixel(40,0,3);
  u8g_sdl_set_pixel(50,0,3);
  */
}

void u8g_sdl_end(void)
{
}

/* return ascii key value or -1 */
int u8g_sdl_get_key(void)
{
  SDL_Event event;
	/* http://www.libsdl.org/cgi/docwiki.cgi/SDL_PollEvent */
  if ( SDL_PollEvent(&event) != 0 )
  {
    switch (event.type) 
    {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
          switch( event.key.keysym.sym )
          {
            /*     /usr/include/SDL/SDL_keysym.h */
            case SDLK_a: return 'a';
            case SDLK_b: return 'b';
            case SDLK_c: return 'c';
            case SDLK_d: return 'd';
            case SDLK_e: return 'e';
            case SDLK_f: return 'f';
            case SDLK_g: return 'g';
            case SDLK_h: return 'h';
            case SDLK_i: return 'i';
            case SDLK_j: return 'j';
            case SDLK_k: return 'k';
            case SDLK_l: return 'l';
            case SDLK_m: return 'm';
            case SDLK_n: return 'n';
            case SDLK_o: return 'o';
            case SDLK_p: return 'p';
            case SDLK_q: return 'q';
            case SDLK_r: return 'r';
            case SDLK_s: return 's';
            case SDLK_t: return 't';
            case SDLK_u: return 'u';
            case SDLK_v: return 'v';
            case SDLK_w: return 'w';
            case SDLK_x: return 'x';
            case SDLK_y: return 'y';
            case SDLK_z: return 'z';
            case SDLK_SPACE: return ' ';
            case SDLK_UP: return 273;
            case SDLK_DOWN: return 274;
            case SDLK_RIGHT: return 275;
            case SDLK_LEFT: return 276;
            
            default: return 0;
          }
    }
  }
  return -1;
}

uint8_t u8g_dev_sdl_1bit_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_sdl_init();
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      u8g_sdl_start();
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        uint8_t i, j;
        uint8_t page_height;
        page_height = pb->p.page_y1;
        page_height -= pb->p.page_y0;
        page_height++;
        for( j = 0; j < page_height; j++ )
        {
          for( i = 0; i < WIDTH; i++ )
          {
            if ( (   ((uint8_t *)(pb->buf))[i] & (1<<j)) != 0 )
              u8g_sdl_set_pixel(i, j+pb->p.page_y0, 3);
          }
        }
      }
      /* update all */
      /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
      SDL_UpdateRect(u8g_sdl_screen, 0,0,0,0);
      break;    /* continue to base fn */
  }
  return u8g_dev_pb8v1_base_fn(u8g, dev, msg, arg);
}

uint8_t u8g_dev_sdl_1bit_h_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_sdl_init();
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      u8g_sdl_start();
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        uint8_t i, j;
        uint8_t page_height;
        page_height = pb->p.page_y1;
        page_height -= pb->p.page_y0;
        page_height++;
        for( j = 0; j < page_height; j++ )
        {
          for( i = 0; i < WIDTH; i++ )
          {
            if ( (   ((uint8_t *)(pb->buf))[i/8+j*WIDTH/8] & (128>>(i&7))) != 0 )
              u8g_sdl_set_pixel(i, j+pb->p.page_y0, 3);
          }
        }
      }
      /* update all */
      /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
      SDL_UpdateRect(u8g_sdl_screen, 0,0,0,0);
      break;    /* continue to base fn */
  }
  return u8g_dev_pb8h1_base_fn(u8g, dev, msg, arg);
}

uint8_t u8g_dev_sdl_2bit_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_sdl_init();
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      u8g_sdl_start();
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        uint8_t i, j, v;
        uint8_t page_height;
        page_height = pb->p.page_y1;
        page_height -= pb->p.page_y0;
        page_height++;
        for( j = 0; j < page_height; j++ )
        {
          for( i = 0; i < WIDTH; i++ )
          {
            v = ((uint8_t *)(pb->buf))[i];
            v >>= j*2;
            v &= 3;
            u8g_sdl_set_pixel(i, j+pb->p.page_y0, v);
          }
        }
      }
      /* update all */
      /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
      SDL_UpdateRect(u8g_sdl_screen, 0,0,0,0);
      break;    /* continue to base fn */
  }
  return u8g_dev_pb8v2_base_fn(u8g, dev, msg, arg);
}

uint8_t u8g_dev_sdl_2bit_double_mem_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  return 0;
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_sdl_init();
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      u8g_sdl_start();
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        uint8_t i, j, v;
        uint8_t page_height;
        page_height = pb->p.page_y1;
        page_height -= pb->p.page_y0;
        page_height++;
        for( j = 0; j < page_height; j++ )
        {
          if ( j <= 3 )
          {
            for( i = 0; i < WIDTH; i++ )
            {
              v = ((uint8_t *)(pb->buf))[i];
              v >>= j*2;
              v &= 3;
              u8g_sdl_set_pixel(i, j+pb->p.page_y0, v);
            }
          }
          else
          {
            for( i = 0; i < WIDTH; i++ )
            {
              v = (((uint8_t *)(pb->buf))+pb->width)[i];
              v >>= (j&3)*2;
              v &= 3;
              u8g_sdl_set_pixel(i, j+pb->p.page_y0, v);
            }
          }
        }
      }
      /* update all */
      /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
      SDL_UpdateRect(u8g_sdl_screen, 0,0,0,0);
      break;    /* continue to base fn */
  }
  return u8g_dev_pb16v2_base_fn(u8g, dev, msg, arg);
}


uint8_t u8g_dev_sdl_8bit_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  /*
  if ( msg == U8G_DEV_MSG_INIT )
  {
      u8g_sdl_init_R3G3B2();
  }
  return 1;
  */
  
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_sdl_init_R3G3B2();
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      u8g_sdl_start();
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        uint8_t i, j, v;
        uint8_t page_height;
        page_height = pb->p.page_y1;
        page_height -= pb->p.page_y0;
        page_height++;
        for( j = 0; j < page_height; j++ )
        {
          for( i = 0; i < WIDTH; i++ )
          {
            u8g_sdl_set_pixel(i, j+pb->p.page_y0, ((uint8_t *)(pb->buf))[i+j*WIDTH]);
          }
        }
      }
      /* update all */
      /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
      SDL_UpdateRect(u8g_sdl_screen, 0,0,0,0);
      break;    /* continue to base fn */
  }
  return u8g_dev_pb8h8_base_fn(u8g, dev, msg, arg);
}

uint8_t u8g_dev_sdl_hicolor_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_sdl_init_R3G3B2();
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      u8g_sdl_start();
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        uint8_t i, j, v;
        uint8_t page_height;
	uint8_t low;
	uint8_t high;
	
        page_height = pb->p.page_y1;
        page_height -= pb->p.page_y0;
        page_height++;
        for( j = 0; j < page_height; j++ )
        {
          for( i = 0; i < WIDTH; i++ )
          {
	    low = ((uint8_t *)(pb->buf))[(i+j*WIDTH)*2];
	    high = ((uint8_t *)(pb->buf))[(i+j*WIDTH)*2+1];
            u8g_sdl_set_hicolor(i, j+pb->p.page_y0, low, high);
          }
        }
      }
      /* update all */
      /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
      SDL_UpdateRect(u8g_sdl_screen, 0,0,0,0);
      break;    /* continue to base fn */
  }
  return u8g_dev_pbxh16_base_fn(u8g, dev, msg, arg);
}

uint8_t u8g_dev_sdl_fullcolor_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  unsigned int r,g,b;
  switch(msg)
  {
    case U8G_DEV_MSG_INIT:
      u8g_sdl_init_R3G3B2();
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      u8g_sdl_start();
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
      {
        u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);
        uint8_t i, j, v;
        uint8_t page_height;
	uint8_t low;
	uint8_t high;
	
        page_height = pb->p.page_y1;
        page_height -= pb->p.page_y0;
        page_height++;
        for( j = 0; j < page_height; j++ )
        {
          for( i = 0; i < WIDTH; i++ )
          {
	    r = ((uint8_t *)(pb->buf))[(i+j*WIDTH)*3];
	    g = ((uint8_t *)(pb->buf))[(i+j*WIDTH)*3+1];
	    b = ((uint8_t *)(pb->buf))[(i+j*WIDTH)*3+2];
            u8g_sdl_set_fullcolor(i, j+pb->p.page_y0, r,g,b);
          }
        }
      }
      /* update all */
      /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
      SDL_UpdateRect(u8g_sdl_screen, 0,0,0,0);
      break;    /* continue to base fn */
  }
  return u8g_dev_pbxh24_base_fn(u8g, dev, msg, arg);
}


U8G_PB_DEV(u8g_dev_sdl_1bit, WIDTH, HEIGHT, 8, u8g_dev_sdl_1bit_fn, NULL);
U8G_PB_DEV(u8g_dev_sdl_1bit_h, WIDTH, HEIGHT, 8, u8g_dev_sdl_1bit_h_fn, NULL);
U8G_PB_DEV(u8g_dev_sdl_2bit, WIDTH, HEIGHT, 4, u8g_dev_sdl_2bit_fn, NULL);

uint8_t u8g_index_color_8h8_buf[WIDTH*8] U8G_NOCOMMON ; 
u8g_pb_t u8g_index_color_8h8_pb = { {8, HEIGHT, 0, 0, 0},  WIDTH, u8g_index_color_8h8_buf}; 
u8g_dev_t u8g_dev_sdl_8bit = { u8g_dev_sdl_8bit_fn, &u8g_index_color_8h8_pb, NULL };

uint8_t u8g_hicolor_xh16_buf[WIDTH*8*2] U8G_NOCOMMON ; 
u8g_pb_t u8g_hicolor_xh16_pb = { {8, HEIGHT, 0, 0, 0},  WIDTH, u8g_hicolor_xh16_buf}; 
u8g_dev_t u8g_dev_sdl_hicolor = { u8g_dev_sdl_hicolor_fn, &u8g_hicolor_xh16_pb, NULL };

uint8_t u8g_fullcolor_xh24_buf[WIDTH*8*3] U8G_NOCOMMON ; 
u8g_pb_t u8g_fullcolor_xh24_pb = { {8, HEIGHT, 0, 0, 0},  WIDTH, u8g_fullcolor_xh24_buf}; 
u8g_dev_t u8g_dev_sdl_fullcolor = { u8g_dev_sdl_fullcolor_fn, &u8g_fullcolor_xh24_pb, NULL };

uint8_t u8g_dev_sdl_16v2_buf[WIDTH*2] U8G_NOCOMMON ; 
u8g_pb_t u8g_dev_sdl_16v2_pb = { {8, HEIGHT, 0, 0, 0},  WIDTH, u8g_dev_sdl_16v2_buf}; 
u8g_dev_t u8g_dev_sdl_2bit_double_mem = { u8g_dev_sdl_2bit_double_mem_fn, &u8g_dev_sdl_16v2_pb, NULL };


