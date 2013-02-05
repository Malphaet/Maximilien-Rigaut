CC = gcc
EDITOR = geany
QUIET = @

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc
TMP = 
RSC = 

NFLAGS = -Wextra -Wall -ansi -pedantic -Wdeclaration-after-statement -Wunsafe-loop-optimizations\
		 -std=c99 -Wshadow -O2 -I$(INC) 
DFLAGS = -Wextra -Wall -ansi -pedantic -Wdeclaration-after-statement -Wunsafe-loop-optimizations\
		 -std=c99 -Wshadow -O2 -I$(INC) -g -D build_tests
CFLAGS = $(DFLAGS)
LDFLAGS = 


EXEC=program
EXEC_O=objet1 objet2

DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) $(TMP)


all: $(EXEC)

init:
	$(QUIET)echo "INIT" $(DIRS)
	$(QUIET)mkdir -p $(DIRS)
	
$(EXEC): $(OBJ)/$(EXEC).o $(EXEC_O:%=$(OBJ)/%.o)
	$(QUIET)echo "LINK" $^ "=>" $@
	$(QUIET)$(CC) $(LDFLAGS) $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h
	$(QUIET)echo "MAKE" $^ "=>" $@
	$(QUIET)$(CC) -c $(CFLAGS) $< -o $@

doc: .PHONY
	$(QUIET)doxygen Doxyfile
	$(QUIET)echo "MAKE DOCS"


edit:
	$(EDITOR) 2> /dev/null $(SRC)/* $(INC)/* makefile Readme.md Doxyfile &
	
clean:
	$(QUIET)echo "RMVE" $(OBJ)/*.o $(TMP)/* $(DOC)/*
	$(QUIET)rm -f $(OBJ)/*.o
	$(QUIET)rm -f $(TMP)/*
	$(QUIET)rm -rf $(DOC)/*
	
cleaner: clean
	$(QUIET)echo "RMVE" $(BIN)/$(EXEC)
	$(QUIET)rm -f $(BIN)/$(EXEC)

.PHONY:
