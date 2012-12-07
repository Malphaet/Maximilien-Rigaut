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

BUILD_SHA=`git show --abbrev-commit HEAD | grep '^commit' | sed -e 's/commit //'` 
BUILD_TAG=`git describe --tags --match "v[0-9]*" --abbrev=0 HEAD`

EXEC=server client

all: version
	$(QUIET)echo "Making library"
	$(QUIET)make -e QUIET="" -e PRINT="true" -s -C liblsockets/ cleaner all
	$(QUIET)echo "Making project"
	$(QUIET)make $(EXEC:%=$(BIN)/%)

$(EXEC:%=$(BIN)/%): $(OBJ)/server.o $(OBJ)/client.o
	$(QUIET)echo ""
	$(QUIET)echo "__"$@"__"
	$(QUIET)echo "LINK" $^ "=>" $@
	$(QUIET)$(CC) $(LDFLAGS) -o $@ ${@:$(BIN)/%=$(OBJ)/%.o} -llsockets -lcrypt

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h
	$(QUIET)echo "MAKE" $^ "=>" $@
	$(QUIET)$(CC) $(CFLAGS) -o $@ -c $< -llsockets

version:
ifneq (`which git`,"")
	$(QUIET)echo "#define BUILD_NUMBER \"$(BUILD_SHA)\"" > inc/version.h
	$(QUIET)echo "#define BUILD_VERSION \"$(BUILD_TAG)\"" >> inc/version.h
endif

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

