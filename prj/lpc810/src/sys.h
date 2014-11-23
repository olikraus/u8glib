/*
    
  sys.h

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



#ifndef _LPC81X_SYSTEM_H
#define _LPC81X_SYSTEM_H

#include "stdint.h"


#define SYS_CORE_CLOCK 30000000UL
#define SYS_TICK_PERIOD_IN_MS 10


void delay_system_ticks(uint32_t sys_ticks);
void delay_micro_seconds(uint32_t us);

void i2c_init(void);
void i2c_start(void) ;
void i2c_stop(void);
unsigned i2c_write_byte(unsigned b);

/*
  nack must be 0 if the data reading continues
  nack should be 1 after the last byte. send stop after this
*/
unsigned i2c_read_byte(unsigned nack);


#endif
