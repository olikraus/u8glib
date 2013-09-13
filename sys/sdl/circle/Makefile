#CFLAGS = -g -Wall -I../../../csrc/.  -DU8G_16BIT `sdl-config --cflags`
CFLAGS = -g -Wall -I../../../csrc/. `sdl-config --cflags`

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../sfntsrc/*.c ) main.c ../dev/u8g_dev_sdl.c

OBJ = $(SRC:.c=.o)

helloworld: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `sdl-config --libs` -o u8g_sdl

clean:	
	-rm $(OBJ) u8g_sdl

