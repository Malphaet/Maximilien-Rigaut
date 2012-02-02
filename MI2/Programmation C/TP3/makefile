CC = gcc
CFLAGS = -W -Wall -ansi -pedantic
LDFLAGS = 
EXEC=lib_number
TEST=test_lib_rational test_lib_complex test_lib_number

all: $(EXEC)

test: $(TEST)

test_lib_rational: test_lib_rational.o lib_rational.o
	$(CC) $(LDFLAGS) -o $@ $^

test_lib_complex: test_lib_complex.o lib_complex.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm

test_lib_number: test_lib_number.o lib_number.o lib_complex.o lib_rational.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm

test_lib_rational.o: test_lib_rational.c lib_rational.h
	$(CC) $(CFLAGS) -o $@ -c $<

test_lib_complex.o: test_lib_complex.c lib_complex.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm

test_lib_number.o: test_lib_number.c lib_number.h lib_complex.h lib_rational.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm
	
%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $< -lm

clean: 
	rm -f *.o
	
cleaner: clean
	rm -f $(TEST) $(EXEC)

