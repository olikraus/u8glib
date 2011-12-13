CFLAGS = -g -Wall
#CFLAGS = -O4 -Wall

SRC = bdf2u8g.c

OBJ = $(SRC:.c=.o)

bdf2u8g: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o bdf2u8g

clean:	
	-rm $(OBJ) bdf2u8g

