CC = gcc
LIN = ar rcs

CFLAGS = -W -Wall -ansi -pedantic -c -fPIC
LDFLAGS = 

EXEC=libres-bor.so
MAIN=bor-util

DEST = ../../
PLACE= src/bor/

all: $(EXEC)

$(EXEC): $(MAIN).o
	gcc -shared -Wl,-soname,$@ -o $@ $^ -lc
	mv $@ $(DEST)
	ln -sf $(PLACE)$(MAIN).h $(DEST)$(MAIN).h

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)
	rm -f $(DEST)$(MAIN).h
