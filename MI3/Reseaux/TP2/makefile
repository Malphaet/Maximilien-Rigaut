CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -L$(LIBS) -I$(INC)
LDFLAGS = -L$(LIBS) -I$(INC)

LIBS = ../libs/
INC = ../libs/
BIN = bin
OBJ = obj

EXEC=redir2tub

all: $(EXEC)

redir2tub: redir2tub.o
	$(CC) -static $(LDFLAGS) $^ $(LDFLAGS) -o $@ -lres-bor

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@ -lres-bor

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

