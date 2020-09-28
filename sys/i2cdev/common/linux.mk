CC = gcc
CFLAGS = -g -Wall -I../../../csrc/. -I../common -DU8G_LINUX -DU8G_WITH_PINLIST

APP = $(notdir $(shell pwd))
SRC = $(wildcard ../../../csrc/*.c ../../../sfntsrc/*.c ../common/*.c) $(APP).c

OBJ = $(SRC:.c=.o)

$(APP): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(APP)

clean:
	$(RM) $(OBJ) $(APP)

