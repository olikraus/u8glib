# XC8 Makefile
# make -p

TARGETNAME = pic
LIBNAME = u8g
MCU:=18F26K80
F_CPU:=8000000
TOOLDIR:=/opt/microchip/xc8/v1.01/bin
U8GSRC:=/home/kraus/src/u8g/u8glib/csrc
U8GFONTSRC:=/home/kraus/src/u8g/u8glib/fntsrc

#=========================================

#=========================================

.SUFFIXES: p1

COMPILE.c = $(CC) --pass1 $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH)
OUTPUT_OPTION = -O$@
CFLAGS = -DF_CPU=$(F_CPU) --chip=$(MCU) $(DOGDEFS)
CFLAGS += -I$(U8GSRC)

CC = $(TOOLDIR)/xc8
AR = $(TOOLDIR)/libr
ARFLAGS = r


SRC = $(shell ls $(U8GSRC)/*.c 2>/dev/null)
SRC += $(shell ls $(U8GFONTSRC)/*uni*.c 2>/dev/null)

OBJ = $(SRC:.c=.p1)

all: $(LIBNAME).lpp($(OBJ)) 


%.p1: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	
# /opt/microchip/xc8/v1.01/bin/xc8 --chip=18F26K80 -I../../../csrc hello_world.c u8g.lpp

