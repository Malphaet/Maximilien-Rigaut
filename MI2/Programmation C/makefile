CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
SRC = $(wildcart *.c)
OBJ = $(SRC:.c=.o)
EXEC=test_show_table test_vector_operations test_matrix

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm *.o
	
mrproprer: clean
	rm $(EXEC)

