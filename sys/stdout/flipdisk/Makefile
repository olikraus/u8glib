CFLAGS = -g -Wall -I../../../csrc/. 

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../fntsrc/u8g_font_*x*.c) main.c

OBJ = $(SRC:.c=.o)

flipdisk: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ)  -o flipdisk

clean:	
	-rm $(OBJ) helloworld

