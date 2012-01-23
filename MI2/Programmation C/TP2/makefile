CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
SRC = $(wildcart *.c)
OBJ = $(SRC:.c=.o)
EXEC=test_show_table 

all: $(EXEC)

test_show_table: test_show_table.o show_table.o constants.h
	$(CC) $(LDFLAGS) -o $@ $^

show_table.o: show_table.c show_table.h
	$(CC) $(CFLAGS) -o $@ -c $<

test_show_table.o: test_show_table.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean: 
	rm *.o
