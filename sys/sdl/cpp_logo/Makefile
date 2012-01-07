CFLAGS = -g -Wall -I../../../csrc/.  -DU8G_16BIT `sdl-config --cflags`
CXXFLAGS = -g -Wall -I../../../csrc/. -I../../../cppsrc/. -DU8G_16BIT `sdl-config --cflags`

SRC = $(shell ls ../../../csrc/*.c) $(shell ls ../../../sfntsrc/*.c) ../dev/u8g_dev_sdl.c
CPPSRC = $(shell ls ../../../cppsrc/*.cpp) main.cpp


OBJ = $(SRC:.c=.o)
CPPOBJ = $(CPPSRC:.cpp=.o)

u8g_sdl: $(OBJ) $(CPPOBJ) 
	$(LINK.cc) $(LDFLAGS) $(OBJ) $(CPPOBJ) `sdl-config --libs` -o u8g_sdl

clean:	
	-rm $(OBJ) $(CPPOBJ) u8g_sdl

