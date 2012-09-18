CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=reboursfils triosig

all: $(EXEC)

reboursfils: reboursfils.o
	$(CC) $(LDFLAGS) -o $@ $^

triosig: triosig.o bor-util.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm *.o
	
cleaner: clean
	rm $(EXEC)

