# CFLAGS = -g -Wall -I../../../csrc/.  -DU8G_16BIT -pg

CFLAGS = -g -Wall -I../../../csrc/.  -pg

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../sfntsrc/*.c) $(shell ls ../dev/u8g*.c) main.c

OBJ = $(SRC:.c=.o)

cliptest: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ)  -o cliptest

clean:	
	-rm $(OBJ) cliptest

