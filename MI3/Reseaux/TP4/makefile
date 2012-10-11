CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -L$(LIBS) -I$(INC)
LDFLAGS = -L$(LIBS) $(INCS:%=-I%)

BIN = bin
OBJ = obj
SRC = src
INC = inc
DOC = doc

LIBS = ../libs/
INCS = $(LIBS) $(INC)
DIRS=$(BIN) $(OBJ) $(SRC) $(INC) $(DOC) tmp

EXEC=server client lserver

all: $(EXEC)

server: $(OBJ)/server.o $(OBJ)/libsockets.o
	$(CC) $^ $(LDFLAGS) -o $(BIN)/$@

client: $(OBJ)/client.o $(OBJ)/libsockets.o
	$(CC) $^ $(LDFLAGS) -o $(BIN)/$@ 

lserver: $(OBJ)/lserver.o $(OBJ)/libsockets.o
	$(CC) $^ $(LDFLAGS) -o $(BIN)/$@ 

$(OBJ)/%.o: $(SRC)/%.c $(INC)/%.h
	$(CC) -c $(CFLAGS) $< -o $@

init:
	mkdir -p $(DIRS)

edit:
	gedit 2> /dev/null $(SRC)/* $(INC)/* &
	
clean: 
	rm -f $(OBJ)/*.o
	
cleaner: clean
	rm -f $(BIN)/*
	

