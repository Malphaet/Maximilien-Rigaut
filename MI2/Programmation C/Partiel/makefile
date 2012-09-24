CC = gcc
CFLAGS = 
LDFLAGS = 
EXEC=executable
OBJ=tintable_lib.o adressbook.o

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %.h utils.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

