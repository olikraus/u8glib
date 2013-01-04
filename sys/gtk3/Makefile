CFLAGS = -g -pg -Wall -I../../../csrc/. -DU8G_16BIT `pkg-config --cflags gtk+-3.0`

#SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../sfntsrc/*.c) 
SRC = u8g_gtk3.c

OBJ = $(SRC:.c=.o)

u8g_gtk3: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) `pkg-config --cflags --libs gtk+-3.0` -o u8g_gtk3

clean:	
	-rm $(OBJ) u8g_gtk3

#        valgrind --tool=exp-ptrcheck -v --read-var-info=yes ./u8g_sdl

