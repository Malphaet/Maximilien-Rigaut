CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
SRC = $(wildcart *.c)
OBJ = $(SRC:.c=.o)

all: 
    $(OBJ)
    
%.o: %.c
    $(CC) $(CFLAGS) -o $@

clean: 
    rm *.o
