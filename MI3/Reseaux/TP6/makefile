CC = gcc
EDITOR = geany
QUIET = @

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc
TMP = tmp

INCS = $(INC)
LIB = liblsockets/$(INC)
DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) $(TMP)

CFLAGS = -W -Wextra -Wall -ansi -pedantic -Wdeclaration-after-statement -Wunsafe-loop-optimizations\
		 -std=c99 -Wshadow -O2 -I$(INC) -I$(LIB) -L$(LIB)
LDFLAGS = -I$(LIB) -L$(LIB)
EXEC=server client

all: 
	$(QUIET)echo "Making library"
	$(QUIET)make -e QUIET="" -e PRINT="true" -s -C liblsockets/ cleaner all
	$(QUIET)echo "Making project"
	$(QUIET)make $(EXEC:%=$(BIN)/%)

$(EXEC:%=$(BIN)/%): $(OBJ)/server.o $(OBJ)/client.o
	$(QUIET)echo ""
	$(QUIET)echo "__"$@"__"
	$(QUIET)echo "LINK" $^ "=>" $@
	$(QUIET)$(CC) $(LDFLAGS) -o $@ ${@:$(BIN)/%=$(OBJ)/%.o} -llsockets

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h
	$(QUIET)echo "MAKE" $^ "=>" $@
	$(QUIET)$(CC) $(CFLAGS) -o $@ -c $< -llsockets

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

