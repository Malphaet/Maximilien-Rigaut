CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
SRC = $(wildcart *.c)
OBJ = $(SRC:.c=.o)
EXEC=test_show_table test_vector_operations test_matrix

all: $(EXEC)

test_show_table: test_show_table.o show_table.o
	$(CC) $(LDFLAGS) -o $@ $^

test_vector_operations: test_vector_operations.o vector_operations.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm

test_matrix: test_matrix.o show_matrix.o matrix.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm *.o
	
mrproprer: clean
	rm $(EXEC)

