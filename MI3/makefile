CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=

all: $(EXEC)

$(EXEC): x.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm *.o
	
mrproprer: clean
	rm $(EXEC)

