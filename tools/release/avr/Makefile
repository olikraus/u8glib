#
#  Generic and Simple Atmel AVR GNU Makefile
#
#  Desinged for the gnu-avr tool chain
#
#  Copyright  (c) 2012 Oliver Kraus (olikraus@gmail.com)
#
# Redistribution and use in source and binary forms, with or without modification, are 
# permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this list of 
# conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright notice, this list 
# of conditions and the following disclaimer in the documentation and/or other materials 
# provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS 
# IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

# User defined values
TARGETNAME = u8m2
MCU:=atmega168
F_CPU:=8000000
WORKDIR:=.
U8GM2DIR:=../../src

# Type: "avrdude -c ?" to get a full listing.
AVRDUDE_PROGRAMMER := avrispmkii
# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT := usb

# Replace standard build tools by avr tools
CC = avr-gcc
AR  = @avr-ar

# Compile all .c files in all directories
SRC = $(shell ls $(WORKDIR)/*.c 2>/dev/null)
SRC += $(shell ls $(U8GM2DIR)/*.c 2>/dev/null)

# Flags for the linker and the compiler
COMMON_FLAGS = -DF_CPU=$(F_CPU) -mmcu=$(MCU) $(DOGDEFS)
COMMON_FLAGS += -I$(WORKDIR) -I$(U8GM2DIR)
COMMON_FLAGS += -g -Os -Wall -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
COMMON_FLAGS += -ffunction-sections -fdata-sections -Wl,--gc-sections
COMMON_FLAGS += -Wl,--relax -mcall-prologues
CFLAGS = $(COMMON_FLAGS) -std=gnu99 -Wstrict-prototypes  

OBJ = $(SRC:.c=.o)

.SUFFIXES: .elf .hex .dis

# Targets
.PHONY: all
all: $(TARGETNAME).dis $(TARGETNAME).hex
	avr-size $(TARGETNAME).elf

.PHONY: upload
upload: $(TARGETNAME).dis $(TARGETNAME).hex
	avrdude -F -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -v -v -U flash:w:$(TARGETNAME).hex
	avr-size $(TARGETNAME).elf

.PHONY: clean
clean:
	$(RM) $(TARGETNAME).hex $(TARGETNAME).elf $(TARGETNAME).a $(TARGETNAME).dis $(OBJ)

# implicit rules
.elf.hex:
	avr-objcopy -O ihex -R .eeprom $< $@

# explicit rules
$(TARGETNAME).elf: $(TARGETNAME).a($(OBJ)) 
	$(LINK.o) $(COMMON_FLAGS) $(TARGETNAME).a $(LOADLIBES) $(LDLIBS) -o $@

$(TARGETNAME).dis: $(TARGETNAME).elf
	avr-objdump -S $< > $@

