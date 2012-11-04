#
#  Generic and Simple Atmel AVR GNU Makefile
#
#  Desinged for the gnu-avr tool chain
#
#   Universal 8bit Graphics Library
#   
#   Copyright (c) 2012, olikraus@gmail.com
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
TARGETNAME = u8g_avr
MCU:=attiny84
F_CPU:=8000000
SRC = analog_value.c
U8GDIR = ../../../csrc/
FONTDIR = ../../../sfntsrc/


#================================================
# System/Environment Information
AVRTOOLSPATH:=/usr/bin/
# Type: "avrdude -c ?" to get a full listing.
AVRDUDE_PROGRAMMER := avrispmkii
# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT := usb

#================================================
# Main part of the Makefile starts here. Usually no changes are needed.

# Append U8G Library
# SRC += $(addprefix $(U8GDIR), $(shell ls $(U8GDIR)*.c 2>/dev/null))
SRC += $(shell ls $(U8GDIR)*.c)
SRC += $(shell ls $(FONTDIR)*.c)

# Internal Variable Names
AVRDUDE_FLASH = -U flash:w:$(TARGETNAME).hex
AVRDUDE_FLAGS = -B 12 -F -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -v -v
LIBNAME:=$(TARGETNAME).a
ELFNAME:=$(TARGETNAME).elf
HEXNAME:=$(TARGETNAME).hex
DISNAME:=$(TARGETNAME).dis
OBJ := $(SRC:.c=.o)
# Replace standard build tools by avr tools
CC = $(AVRTOOLSPATH)avr-gcc
CXX = $(AVRTOOLSPATH)avr-g++
AR  = @$(AVRTOOLSPATH)avr-ar
# AVR GNU Tools
OBJCOPY:=$(AVRTOOLSPATH)avr-objcopy
OBJDUMP:=$(AVRTOOLSPATH)avr-objdump
SIZE:=$(AVRTOOLSPATH)avr-size
AVRDUDE = avrdude
# C flags
COMMON_FLAGS = -DF_CPU=$(F_CPU) -mmcu=$(MCU)
COMMON_FLAGS += -g -Os -Wall -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
COMMON_FLAGS += -I. -I$(U8GDIR)
COMMON_FLAGS += -ffunction-sections -fdata-sections -Wl,--gc-sections
COMMON_FLAGS += -Wl,--relax
COMMON_FLAGS += -mcall-prologues
CFLAGS = $(COMMON_FLAGS) -std=gnu99 -Wstrict-prototypes  

# Additional Suffixes
.SUFFIXES: .elf .hex .dis

# Targets
.PHONY: all
all: $(DISNAME) $(HEXNAME)
	$(SIZE) $(ELFNAME)

.PHONY: upload
upload: $(DISNAME) $(HEXNAME)
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_FLASH)
	$(SIZE) $(ELFNAME)

.PHONY: clean
clean:
	$(RM) $(HEXNAME) $(ELFNAME) $(LIBNAME) $(DISNAME) $(OBJ)

# implicit rules
.elf.hex:
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# explicit rules
$(ELFNAME): $(LIBNAME)($(OBJ)) 
	$(LINK.o) $(COMMON_FLAGS) $(LIBNAME) $(LOADLIBES) $(LDLIBS) -o $@

$(DISNAME): $(ELFNAME)
	$(OBJDUMP) -S $< > $@

	
