CC = gcc
EDITOR = geany
QUIET = @

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc
TMP = tmp

type = MK_ASM
colors=false
debug=false

options=

ifeq ($(colors),true)
	options+="-D COLORS"
endif

NFLAGS = -Wextra -Wall -ansi -pedantic -Wdeclaration-after-statement -Wunsafe-loop-optimizations\
		 -std=c99 -Wshadow -O2 -I$(INC) $(options) -D $(type)
DFLAGS = -Wextra -Wall -ansi -pedantic -Wdeclaration-after-statement -Wunsafe-loop-optimizations\
		 -std=c99 -Wshadow -O2 -I$(INC) -g -D DEBUG  $(options) -D $(type)

ifeq ($(debug),true)
	CFLAGS = $(DFLAGS)
	LDFLAGS = 
else
	CFLAGS = $(NFLAGS)
	LDFLAGS = 
endif

EXEC=plcc
EXEC_O=yylex yyparse arbre dico code3

DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) $(TMP)


all: convert $(EXEC)

init:
	$(QUIET)echo "INIT" $(DIRS)
	$(QUIET)mkdir -p $(DIRS)
	
test_lex: clean
	$(QUIET)make all type="MK_LEX"

test_syntaxe: clean
	$(QUIET)make all type="MK_SYN"
	
test_arbre: clean
	$(QUIET)make all type="MK_TREE"
	
test_c3a: clean
	$(QUIET)make all type="MK_C3"
	
test_asm: clean
	$(QUIET)make all type="MK_ASM"
	
convert: $(OBJ)/convert.o
	$(QUIET)$(CC) $(LDFLAGS) $^ -o $(BIN)/$@
	$(QUIET)$(BIN)/convert $(INC)/identifiers.h

$(EXEC): $(OBJ)/$(EXEC).o $(EXEC_O:%=$(OBJ)/%.o)
	$(QUIET)echo "LINK" $^ "=>" $@
	$(QUIET)$(CC) $(LDFLAGS) $^ -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h $(INC)/utils.h
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
	$(QUIET)rm -fr $(DOC)/*
	
cleaner: clean
	$(QUIET)echo "RMVE" $(BIN)/$(EXEC)
	$(QUIET)rm -f $(BIN)/$(EXEC)

.PHONY:
