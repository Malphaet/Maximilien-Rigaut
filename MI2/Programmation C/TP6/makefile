CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=test

all: $(EXEC)

$(EXEC): main.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %.h utils.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

