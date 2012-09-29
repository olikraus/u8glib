/*

  u8g_clip.c
  
  procedures for clipping
  taken over from procs in u8g_pb.c

  Universal 8bit Graphics Library
  
  Copyright (c) 2012, olikraus@gmail.com
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
  
  
*/

#include "u8g.h"

/*
  intersection assumptions:
    a1 <= a2 is always true    
*/
  /*
    minimized version
    ---1----0 1             b1 <= a2 && b1 > b2
    -----1--0 1             b2 >= a1 && b1 > b2
    ---1-1--- 1             b1 <= a2 && b2 >= a1
  */

uint8_t u8g_is_intersection(u8g_uint_t a0, u8g_uint_t a1, u8g_uint_t v0, u8g_uint_t v1)
{
  uint8_t c1, c2, c3, tmp;
  c1 = v0 <= a1;
  c2 = v1 >= a0;
  c3 = v0 > v1;
  
  tmp = c1;
  c1 &= c2;
  c2 &= c3;
  c3 &= tmp;
  c1 |= c2;
  c1 |= c3;
  return c1 & 1;
}

uint8_t u8g_is_box_bbx_intersection(u8g_box_t *box, u8g_dev_arg_bbx_t *bbx)
{
  if ( u8g_is_intersection(box->y0, box->y1, bbx->y, bbx->y + bbx->h - 1) == 0 )
    return 0; 
  
  return u8g_is_intersection(box->x0, box->x1, bbx->x, bbx->x + bbx->w - 1);
}
