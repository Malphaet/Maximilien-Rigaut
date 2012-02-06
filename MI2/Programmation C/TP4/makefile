CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -g
LDFLAGS = 
EXEC=lib_string

all: $(EXEC)

$(EXEC): lib_string.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)
