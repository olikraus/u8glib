#
#  Generic and Simple GNU Makefile
#
#  Desinged for the msp430 gnu tool chain
#
#   Universal 8bit Graphics Library
#   
#   Copyright (c) 2015, olikraus@gmail.com
#   All rights reserved.
# 
#   Redistribution and use in source and binary forms, with or without modification, 
#   are permitted provided that the following conditions are met:
# 
#   * Redistributions of source code must retain the above copyright notice, this list 
#     of conditions and the following disclaimer.
#     
#   * Redistributions in binary form must reproduce the above copyright notice, this 
#     list of conditions and the following disclaimer in the documentation and/or other 
#     materials provided with the distribution.
# 
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
#   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
#   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
#   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
#   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
#   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
#   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
#   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
#   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
#   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
#   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
#   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
#   ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
#
# 	Features
#		- upload
#		- create exe from library
#		- create assembler listing (.dis)
#
#	Limitations
#		- only C-files supported
#		- no automatic dependency checking (call 'make clean' if any .h files are changed)
#
#	Targets:
#		make
#			create hex file, no upload
#		make upload
#			create and upload hex file
#		make clean
#			delete all generated files
#
#  Note:
#  	Display list make database: make -p -f/dev/null | less

#================================================
# Project Information
TARGETNAME = u8g_hello_world
MCU:=msp430f5529
# DMCU:=__MSP430F5529__
F_CPU:=1000000
MSRC = hello_world.c
U8GDIR = ../../../csrc/
FONTDIR = ../../../sfntsrc/


#================================================
# System/Environment Information
# This Makefile requires two tools: 1) MSP430 GCC and 2) MSP430Flasher
# MSP430 GCC must be here $(TIPATH)gcc/bin
TIPATH:=/home/kraus/prg/ti/

# MSP430Flasher must be here: $(TIPATH)MSP430Flasher_1.3.3/
MSP430FLASHER:=LD_LIBRARY_PATH=$(TIPATH)MSP430Flasher_1.3.3/ && $(TIPATH)MSP430Flasher_1.3.3/MSP430Flasher

# this is the path for all of the gnu utilies and compilers
TOOLSPATH:=$(TIPATH)gcc/bin/


#================================================
# Main part of the Makefile starts here. Usually no changes are needed.

# Append U(G Library
SRC = system_pre_init.c
SRC += $(shell ls $(U8GDIR)*.c)
SRC += $(shell ls $(FONTDIR)*.c)

# Internal Variable Names
LIBNAME:=$(TARGETNAME).a
ELFNAME:=$(TARGETNAME).elf
HEXNAME:=$(TARGETNAME).hex
DISNAME:=$(TARGETNAME).dis
OBJ := $(SRC:.c=.o)
MOBJ := $(MSRC:.c=.o)
# GNU compiler
CC = $(TOOLSPATH)msp430-elf-gcc
CXX = $(TOOLSPATH)msp430-elf-g++
AR = $(TOOLSPATH)msp430-elf-ar
# GNU Tools
OBJCOPY:=$(TOOLSPATH)msp430-elf-objcopy
OBJDUMP:=$(TOOLSPATH)msp430-elf-objdump
SIZE:=$(TOOLSPATH)msp430-elf-size
# C flags
COMMON_FLAGS = -DF_CPU=$(F_CPU) -mmcu=$(MCU)
COMMON_FLAGS += -g -Os -Wall -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
COMMON_FLAGS += -I. -I$(U8GDIR) -I$(TIPATH)/gcc/include -L$(TIPATH)/gcc/include
COMMON_FLAGS += -ffunction-sections -fdata-sections -Wl,--gc-sections
COMMON_FLAGS += -Wl,--relax
COMMON_FLAGS += 
CFLAGS = $(COMMON_FLAGS) -std=gnu99 -Wstrict-prototypes  
# Linker script
# LDLIBS = -T $(TIPATH)/gcc/include/$(MCU).ld

# Additional Suffixes
.SUFFIXES: .elf .hex .dis

# Targets
.PHONY: all
all: $(DISNAME) $(HEXNAME)
	$(SIZE) $(ELFNAME)

.PHONY: upload
upload: $(DISNAME) $(HEXNAME)
	-$(MSP430FLASHER) -w $(HEXNAME) -v -z [VCC,RESET]
	$(SIZE) $(ELFNAME)

.PHONY: clean
clean:
	$(RM) $(HEXNAME) $(ELFNAME) $(LIBNAME) $(DISNAME) $(OBJ) $(MOBJ)

# implicit rules
.elf.hex:
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# explicit rules
$(ELFNAME): $(LIBNAME)($(OBJ)) $(MOBJ)
	$(LINK.o) $(COMMON_FLAGS) $(MOBJ) $(LIBNAME) $(LOADLIBES) -o $@

$(DISNAME): $(ELFNAME)
	$(OBJDUMP) -S $< > $@
