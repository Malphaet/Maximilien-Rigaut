CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
SRC = $(wildcart *.c)
OBJ = $(SRC:.c=.o)
EXEC=test_show_table 

all: $(EXEC)

test_show_table: test_show_table.o show_table.h constants.h
	$(CC) $(LDFLAGS) -o $@ $^

test_show_table.o: test_show_table.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
    rm *.o
