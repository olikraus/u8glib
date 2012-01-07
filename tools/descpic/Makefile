CFLAGS = -g -Wall -I../../csrc/. -DU8G_16BIT

SRC = $(shell ls ../../csrc/*.c) $(shell ls ../../sfntsrc/*.c) ../../sys/pbm/dev/u8g_dev_pbm.c descpic.c

OBJ = $(SRC:.c=.o)

descpic: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o descpic

clean:	
	-rm $(OBJ) descpic

