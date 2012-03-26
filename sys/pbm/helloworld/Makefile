CFLAGS = -g -Wall -I../../../csrc/.  -DU8G_16BIT

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../sfntsrc/*.c) $(shell ls ../dev/u8g*.c) main.c

OBJ = $(SRC:.c=.o)

helloworld: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ)  -o helloworld

clean:	
	-rm $(OBJ) helloworld

