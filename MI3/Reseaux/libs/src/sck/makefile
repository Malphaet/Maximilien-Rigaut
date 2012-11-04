AR = ar rcs
CC = gcc

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc
TMP = tmp

CFLAGS = -W -Wall -ansi -pedantic -I$(INC)
LDFLAGS = -L../../

EXEC=liblsockets.a
MAIN=liblsockets

DEST = ../..
PLACE= src/sck
DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) $(TMP)

all: $(EXEC)

init:
	mkdir -p $(DIRS)

$(EXEC): $(OBJ)/$(MAIN).o $(OBJ)/wrappers.o $(OBJ)/lpackets.o $(OBJ)/lclists.o
	$(AR) $@ $^
	mv $@ $(DEST)/
	ln -sf $(PLACE)/$(INC)/$(MAIN).h $(DEST)/$(MAIN).h

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h $(INC)/utils.h $(INC)/structures.h
	$(CC) -c $(CFLAGS) $< -o $@

test: $(SRC)/test.c $(DEST)/$(EXEC)
	$(CC) $(CFLAGS) -o $(OBJ)/test.o -c $<
	$(CC) $(LDFLAGS) $(OBJ)/test.o -o $(BIN)/$@ -llsockets

doc: .PHONY
	doxygen Doxyfile

edit:
	gedit 2> /dev/null $(SRC)/* $(INC)/* makefile Readme.md &
	
clean: 
	rm -f $(OBJ)/*.o
	rm -f $(TMP)/*
	
cleaner: clean
	rm -f $(BIN)/*
	rm -f $(DEST)/$(EXEC)
	rm -f $(DEST)/$(MAIN).h
	rm -f $(BIN)/test

.PHONY:
