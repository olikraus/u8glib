
CFLAGS = -g -Wall -I../../../csrc/.  -DU8G_16BIT
#CFLAGS = -g -Wall -I../../../src/. 

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../fntsrc/u8g_font_10x20*.c) $(shell ls ../dev/u8g*.c) main.c

OBJ = $(SRC:.c=.o)

rotation: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o rotation

clean:	
	-rm $(OBJ) rotation

