CC = gcc

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc
TMP = tmp
RSC = ressources

CFLAGS = -Wextra -Wall -ansi -pedantic -std=c99 -Wshadow -O3 -I$(INC) -D build_tests
LDFLAGS = 


EXEC=corrector
EXEC_O=wordtools utf8 utils clist

DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) $(TMP)


all: $(EXEC)

init:
	mkdir -p $(DIRS)
	
$(EXEC): $(OBJ)/$(EXEC).o $(EXEC_O:%=$(OBJ)/%.o)
	$(CC) $(LDFLAGS) $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h
	$(CC) -c $(CFLAGS) $< -o $@ 

test: $(SRC)/test.c

doc: .PHONY
	doxygen Doxyfile

edit:
	gedit 2> /dev/null $(SRC)/* $(INC)/* makefile Readme.md &
	
clean: 
	rm -f $(OBJ)/*.o
	rm -f $(TMP)/*
	rm -f $(LIB)/*.a
	
cleaner: clean
	rm -f $(BIN)/$(EXEC)

.PHONY:
