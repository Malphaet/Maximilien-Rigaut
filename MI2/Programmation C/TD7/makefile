CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=test dump noise

all: $(EXEC)

test: test.o bary.o
	$(CC) $(LDFLAGS) -o $@ $^

dump: dump.o
	$(CC) $(LDFLAGS) -o $@ $^

noise: noise.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %.h utils.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean:
	rm -f *.o test.txt bary.txt
	
cleaner: clean
	rm -f $(EXEC)

