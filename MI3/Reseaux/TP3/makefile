CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -L$(LIBS) -I$(INC)
LDFLAGS = -L$(LIBS) -I$(INC)

LIBS = ../libs/
INC = ../libs/
BIN = bin
OBJ = obj

EXEC=debitub

all: $(EXEC)

debitub: debitub.o
	$(CC) $^ $(LDFLAGS) -o $@ -lres-bor

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

