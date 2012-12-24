CFLAGS = -g -pg -Wall -I../../../csrc/. -I../../../dogmsrc/. -DU8G_16BIT `sdl-config --cflags`

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../sfntsrc/*.c ../../../dogmsrc/*.c) spacemain.c ../dev/u8g_dev_sdl.c

OBJ = $(SRC:.c=.o)

helloworld: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `sdl-config --libs` -o u8g_sdl

clean:	
	-rm $(OBJ) u8g_sdl

#        valgrind --tool=exp-ptrcheck -v --read-var-info=yes ./u8g_sdl

