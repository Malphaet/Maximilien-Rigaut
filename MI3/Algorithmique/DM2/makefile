CC = gcc

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc
TMP = tmp
RSC = ressources

CFLAGS = -W -Wall -ansi -pedantic -I$(INC)
LDFLAGS =

EXEC=corrector
EXEC_O=levenshtein 

DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) $(TMP)


all: $(EXEC)

init:
	mkdir -p $(DIRS)

$(EXEC): $(OBJ)/$(EXEC).o $(OBJ)/$(EXEC_O:%=%.o)
	$(CC) $(LDFLAGS) $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h $(INC)/utils.h
	$(CC) -c $(CFLAGS) $< -o $@

test: $(SRC)/test.c

doc: .PHONY
	doxygen Doxyfile

edit:
	gedit 2> /dev/null $(SRC)/* $(INC)/* makefile Readme.md &
	
clean: 
	rm -f $(OBJ)/*.o
	rm -f $(TMP)/*
	
cleaner: clean
	rm -f $(BIN)/*
	rm -f $(BIN)/$(EXEC)
	rm -f $(BIN)/$(MAIN).h
	rm -f $(BIN)/test

.PHONY:
