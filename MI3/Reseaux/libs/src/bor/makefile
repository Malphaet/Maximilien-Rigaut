AR = ar rcs
CC = gcc

CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 

EXEC=libres-bor.a
MAIN=bor-util

DEST = ../../
PLACE= src/bor/

all: $(EXEC)

$(EXEC): $(MAIN).o
	$(AR) $@ $^
	mv $@ $(DEST)
	ln -sf $(PLACE)$(MAIN).h $(DEST)$(MAIN).h

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)
	rm -f $(DEST)$(MAIN).h
