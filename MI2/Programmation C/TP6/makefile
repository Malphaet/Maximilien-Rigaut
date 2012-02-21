CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=executable

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

