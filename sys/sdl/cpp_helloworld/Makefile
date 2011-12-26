CFLAGS = -g -Wall -I../../../csrc/.  -DU8G_16BIT `sdl-config --cflags`

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../fntsrc/u8g_font_10x20*.c ../../../fntsrc/u8g_font_osb*.c ../../../fntsrc/u8g_font_uni*.c ../../../fntsrc/u8g_font_fur*.c ../../../fntsrc/u8g_font_cursor*.c) main.c ../dev/u8g_dev_sdl.c
CPPSRC = $(shell ls ../../../cppsrc/*.cpp)


OBJ = $(SRC:.c=.o)
CPPOBJ = $(CPPSRC:.cpp=.o)

helloworld: $(OBJ) $(CPPOBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `sdl-config --libs` -o u8g_sdl

clean:	
	-rm $(OBJ) $(CPPOBJ) u8g_sdl

