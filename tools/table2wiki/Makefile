CFLAGS = -g -Wall

SRC = table2html.c

OBJ = $(SRC:.c=.o)

table2html: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o table2html

clean:	
	-rm $(OBJ) table2html

