CFLAGS = -g -Wall -I../../../csrc/. -DU8G_16BIT

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../sfntsrc/*.c) ../../../sys/pbm/dev/u8g_dev_pbm.c picgen.c

OBJ = $(SRC:.c=.o)

picgen: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o picgen

clean:	
	-rm $(OBJ) picgen

