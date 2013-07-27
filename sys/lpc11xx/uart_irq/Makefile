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
#		make screen
#			call unix screen utility (terminal emulator)
#		make clean
#			delete all generated files
#
#  Note:
#  	Display list make database: make -p -f/dev/null | less
#
#================================================
# Project Information

# The name for the project
TARGETNAME:=uart_irq

# The source files of the project
SRC:=$(wildcard *.c)

# The base directory of gcc-arm-none-eabi
GCCPATH:=~/src/arm/gcc-arm-none-eabi-4_7-2013q1

# The frequency of the target device
F_CPU:=12000000

# The CPU architecture (will be used for -mcpu)
MCPU:=cortex-m0

# The name of the startup file which matches to the architecture (MCPU)
# Usually this can be taken from
# gcc-arm-none-eabi-4_7-2013q1/share/gcc-arm-none-eabi/samples/startup
# STARTUP:=$(GCCPATH)/share/gcc-arm-none-eabi/samples/startup/startup_ARMCM0.S
STARTUP:=../common/startup_lpc11xx.S

# Include directory for the system include files
SYSINC:=../common

# Directory for the linker script
LDSCRIPTDIR:=../common
# Name of the linker script
LDSCRIPT:=lpc11xx.ld


#================================================
# Flash tool
FLASHTOOL:=~/prg/lpc21isp/lpc21isp
FLASHPORT:=/dev/ttyUSB0

#================================================
# Main part of the Makefile starts here. Usually no changes are needed.

# Internal Variable Names
LIBNAME:=$(TARGETNAME).a
ELFNAME:=$(TARGETNAME).elf
HEXNAME:=$(TARGETNAME).hex
DISNAME:=$(TARGETNAME).dis
MAPNAME:=$(TARGETNAME).map
OBJ:=$(SRC:.c=.o) $(STARTUP:.S=.o)

# Replace standard build tools by avr tools
CC:=$(GCCPATH)/bin/arm-none-eabi-gcc
AR:=$(GCCPATH)/bin/arm-none-eabi-ar
OBJCOPY:=$(GCCPATH)/bin/arm-none-eabi-objcopy
OBJDUMP:=$(GCCPATH)/bin/arm-none-eabi-objdump
SIZE:=$(GCCPATH)/bin/arm-none-eabi-size

# Common flags
COMMON_FLAGS = -DF_CPU=$(F_CPU) -mthumb -mcpu=$(MCPU)
COMMON_FLAGS += -Wall -I. -I$(SYSINC)
COMMON_FLAGS += -Os -flto
COMMON_FLAGS += -ffunction-sections -fdata-sections
# Assembler flags
ASFLAGS:=$(COMMON_FLAGS) -D__STARTUP_CLEAR_BSS -D__START=main
# C flags
CFLAGS:=$(COMMON_FLAGS) -std=gnu99 -fno-builtin
# LD flags
GC:=-Wl,--gc-sections
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

.PHONY: screen
screen:
	screen $(FLASHPORT) 9600

.PHONY: clean
clean:
	$(RM) $(HEXNAME) $(ELFNAME) $(LIBNAME) $(DISNAME) $(MAPNAME)

# implicit rules
.elf.hex:
	@$(OBJCOPY) -O ihex $< $@

# explicit rules
$(ELFNAME): $(LIBNAME)($(OBJ)) 
	$(LINK.o) $(LFLAGS) $(LIBNAME) $(LDLIBS) -o $@

$(DISNAME): $(ELFNAME)
	$(OBJDUMP) -S $< > $@

	
