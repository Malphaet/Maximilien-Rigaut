CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=executable

all: $(EXEC)

$(EXEC): test.o image_utils.o image_io.o image_effects.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %h types_image.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(EXEC)

