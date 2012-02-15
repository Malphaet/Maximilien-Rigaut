CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=test exec calfon

all: $(EXEC)

test: main.o str.o mat.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm

exec: exec.o
	$(CC) $(LDFLAGS) -o $@ $^

calfon: calfon.o str.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm

%.o: %.c %h utils.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

