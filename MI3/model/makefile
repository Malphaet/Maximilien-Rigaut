CC = gcc
EDITOR = geany
QUIET = @

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc
TMP = tmp

DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) $(TMP)

CFLAGS = -W -Wextra -Wall -ansi -pedantic -Wdeclaration-after-statement -Wunsafe-loop-optimizations\
		 -std=c99 -Wshadow -O3 -I$(INC) 
LDFLAGS = 
EXEC=

all: $(EXEC)

$(EXEC): .o
	$(QUIET)echo ""
	$(QUIET)echo "__"$@"__"
	$(QUIET)echo "LINK" $^ "=>" $@
	$(QUIET)$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(QUIET)echo "MAKE" $^ "=>" $@
	$(QUIET)$(CC) $(CFLAGS) -o $@ -c $< -lm

init:
	mkdir -p $(DIRS)

edit:
	$(EDITOR) 2> /dev/null $(SRC)/* $(INC)/* makefile &
	
clean:
	$(QUIET)echo ""
	$(QUIET)echo "__"$@"__"
	$(QUIET)echo "RMVE" $(OBJ)/*.o $(TMP)/* $(DOC)/*
	$(QUIET)rm -f $(OBJ)/*.o
	$(QUIET)rm -f $(TMP)/*
	$(QUIET)rm -rf $(DOC)/*
	
cleaner: clean
	$(QUIET)echo "RMVE" $(BIN)/*
	$(QUIET)rm -f $(BIN)/*

