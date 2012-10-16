CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -L$(LIBS) $(INCS:%=-I%)
LDFLAGS = -L$(LIBS) $(INCS:%=-I%)

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc

LIBS = ../libs/
INCS = $(LIBS) $(INC)
LNKS = 
DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) tmp

EXEC= client server

all: $(EXEC)

server: $(OBJ)/server.o $(LNKS)
	$(CC) $^ $(LDFLAGS) -o $(BIN)/$@ -llsockets

client: $(OBJ)/client.o $(LNKS)
	$(CC) $^ $(LDFLAGS) -o $(BIN)/$@ -llsockets

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h
	$(CC) -c $(CFLAGS) $< -o $@

init:
	mkdir -p $(DIRS)

doc: .PHONY
	doxygen doxyconf

edit:
	gedit 2> /dev/null $(SRC)/* $(INC)/* &
	
clean: 
	rm -f $(OBJ)/*.o
	
cleaner: clean
	rm -f $(BIN)/*
	rm -rf $(DOC)/*

.PHONY:
	
