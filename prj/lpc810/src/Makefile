#
#  Generic and Simple GNU ARM Makefile 
#
#  Desinged for the gnu-arm-none-eabi tool chain
#
# 	Features
#		- create hex file
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
#
#================================================
# External tools

# The base directory of gcc-arm-none-eabi
# GCCPATH:=~/src/arm/gcc-arm-none-eabi-4_7-2013q1
GCCPATH:=~/src/arm/gcc-arm-none-eabi-4_7-2013q2

# Flash Tool
FLASHTOOL:=~/prg/lpc21isp/lpc21isp

#================================================
# Project Information

# The name for the project
TARGETNAME:=lpc810

# The source files of the project
SRC:=$(wildcard *.c)

# The CPU architecture (will be used for -mcpu)
MCPU:=cortex-m0

# Include directory for the system include files
SYSINC:=../lpc_chip_8xx_lib/inc
SYSSRC:=$(wildcard ../lpc_chip_8xx_lib/src/*.c)


# Directory for the linker script
LDSCRIPTDIR:=../common/.
# Name of the linker script (must be the "keep" script, because the other script is not always working)
LDSCRIPT:=lpc810.ld

# Unix device of the USB-RS232 converter for the flash tool
FLASHPORT:=/dev/ttyUSB0

#================================================
# Main part of the Makefile starts here. Usually no changes are needed.

# Internal Variable Names
LIBNAME:=$(TARGETNAME).a
ELFNAME:=$(TARGETNAME).elf
HEXNAME:=$(TARGETNAME).hex
DISNAME:=$(TARGETNAME).dis
MAPNAME:=$(TARGETNAME).map
OBJ:=$(SRC:.c=.o) $(SYSSRC:.c=.o)

# Replace standard build tools by avr tools
CC:=$(GCCPATH)/bin/arm-none-eabi-gcc
AR:=$(GCCPATH)/bin/arm-none-eabi-ar
OBJCOPY:=$(GCCPATH)/bin/arm-none-eabi-objcopy
OBJDUMP:=$(GCCPATH)/bin/arm-none-eabi-objdump
SIZE:=$(GCCPATH)/bin/arm-none-eabi-size

# Common flags
COMMON_FLAGS = -mthumb -mcpu=$(MCPU)
COMMON_FLAGS += -Wall -I. -I$(SYSINC)
# define stack size (defaults to 0x0100)  
# COMMON_FLAGS += -D__STACK_SIZE=0x0100
# define constant for lpcopen library
COMMON_FLAGS += -DCORE_M0PLUS
# do not make a call to SystemInit()
COMMON_FLAGS += -Os -flto -fno-jump-tables
# Do not use stand libs startup code. Uncomment this for gcclib procedures
# memcpy still works, but might be required for __aeabi_uidiv
# COMMON_FLAGS +=  -nostdlib
# remove unused data and function
COMMON_FLAGS += -ffunction-sections -fdata-sections
# C flags
CFLAGS:=$(COMMON_FLAGS) -std=gnu99 
# LD flags
# remove unreferenced procedures and variables, but keep "arm_stack_area" and __isr_vector
GC:=-Wl,--gc-sections  -Wl,--undefined=arm_stack_area -Wl,--undefined=__isr_vector
MAP:=-Wl,-Map=$(MAPNAME)
LFLAGS:=$(COMMON_FLAGS) $(GC) $(MAP)
LDLIBS:=--specs=nano.specs -lc -lc -lnosys -L$(LDSCRIPTDIR) -T $(LDSCRIPT)

# Additional Suffixes
.SUFFIXES: .elf .hex .dis

# Targets
.PHONY: all
all: $(DISNAME) $(HEXNAME)
	$(SIZE) $(ELFNAME)

.PHONY: upload
upload: $(DISNAME) $(HEXNAME) $(ELFNAME)
#	$(FLASHTOOL) $(HEXNAME) $(FLASHPORT) 115200 12000
	$(FLASHTOOL) $(HEXNAME) $(FLASHPORT) 38400 12000
	$(SIZE) $(ELFNAME)

.PHONY: clean
clean:
	$(RM) $(OBJ) $(HEXNAME) $(ELFNAME) $(LIBNAME) $(DISNAME) $(MAPNAME)

# implicit rules
.elf.hex:
	@$(OBJCOPY) -O ihex $< $@

# explicit rules
$(ELFNAME): $(LIBNAME)($(OBJ)) 
	$(LINK.o) $(LFLAGS) $(LIBNAME) $(LDLIBS) -o $@

$(DISNAME): $(ELFNAME)
	$(OBJDUMP) -D -S $< > $@

	
