CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
SRC = $(wildcart *.c)
OBJ = $(SRC:.c=.o)
EXEC=exo2 exo3

all: $(EXEC)

exo2: exo2.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean: 
	rm *.o $(EXEC)

