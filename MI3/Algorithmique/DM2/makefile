CC = gcc
EDITOR = geany
QUIET = @

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc
TMP = tmp
RSC = ressources

NFLAGS = -Wextra -Wall -ansi -pedantic -Wdeclaration-after-statement -std=c99 -Wshadow -O3 -I$(INC) 
DFLAGS = -Wextra -Wall -ansi -pedantic -Wdeclaration-after-statement -Wunsafe-loop-optimizations -std=c99 -Wshadow -I$(INC) -g -D build_tests
CFLAGS = $(DFLAGS)
LDFLAGS = 


EXEC=corrector
EXEC_O=wordtools utf8 utils clist

DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) $(TMP)


all: $(EXEC)

init:
	mkdir -p $(DIRS)
	
$(EXEC): $(OBJ)/$(EXEC).o $(EXEC_O:%=$(OBJ)/%.o)
	$(QUIET)echo "Linking" $^ "to" $@
	$(QUIET)$(CC) $(LDFLAGS) $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h
	$(QUIET)echo "Making" $@
	$(QUIET)$(CC) -c $(CFLAGS) $< -o $@ 

test: $(SRC)/test.c

doc: .PHONY
	doxygen Doxyfile

edit:
	$(EDITOR) 2> /dev/null $(SRC)/* $(INC)/* makefile Readme.md &
	
clean:
	$(QUIET)echo "Cleaning objects and temporary files"
	$(QUIET)rm -f $(OBJ)/*.o
	$(QUIET)rm -f $(TMP)/*
	
cleaner: clean
	$(QUIET)echo "Deleting build target"
	$(QUIET)rm -f $(BIN)/$(EXEC)

.PHONY:
