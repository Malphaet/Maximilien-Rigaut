CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -L$(LIBS) -I$(INC)
LDFLAGS = -L$(LIBS) -I$(INC)

LIBS = ../libs/
INC = ../libs/
BIN = bin
OBJ = obj

EXEC=reboursfils triosig

all: $(EXEC)

reboursfils: reboursfils.o
	$(CC) $^ $(LDFLAGS) -o $@ 

triosig: triosig.o
	$(CC)  -static $(LDFLAGS) -o $@ $^ -lres-bor

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@ -lres-bor

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

