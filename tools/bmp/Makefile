CFLAGS = -g -Wall

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

descpic: $(OBJ) 
	$(CXX) $(CFLAGS) $(OBJ) -o u8gbmp2hex

clean:	
	-rm $(OBJ) u8gbmp2hex

