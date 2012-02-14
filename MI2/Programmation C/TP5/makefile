CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=test exec

all: $(EXEC)

test: main.o str.o mat.o
	$(CC) $(LDFLAGS) -o $@ $^

exec: exec.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %h utils.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

