CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS =
LIBS = ../libs/
LINKLIB =  -L$(LIBS) -l
EXEC=reboursfils triosig

all: $(EXEC)

reboursfils: reboursfils.o
	$(CC) $^ $(LDFLAGS) -o $@ 

triosig: triosig.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@ $(LINKLIB)res-bor -c

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

