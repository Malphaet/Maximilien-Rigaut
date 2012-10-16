AR = ar rcs
CC = gcc

CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 

EXEC=liblsockets.a
MAIN=liblsockets

DEST = ../../
PLACE= src/sck/

all: $(EXEC)

$(EXEC): $(MAIN).o 
	$(AR) $@ $^
	mv $@ $(DEST)
	ln -sf $(PLACE)$(MAIN).h $(DEST)$(MAIN).h

%.o: %.c %.h utils.h
	$(CC) $(CFLAGS) -o $@ -c $<

doc: .PHONY

	doxygen Doxyfile
clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)
	rm -f $(DEST)$(MAIN).h

.PHONY:
