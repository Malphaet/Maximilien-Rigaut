CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -L$(LIBS) -I$(INC)
LDFLAGS = -L$(LIBS) $(INCS:%=-I%)

BIN = bin
OBJ = obj
SRC = src
INC = inc

LIBS = ../libs/
INCS = $(LIBS) $(INC)
DIRS=$(BIN) $(OBJ) $(SRC) $(INC)

EXEC=tp1

all: $(EXEC)

tp1: $(OBJ)/tp1.o
	$(CC) $^ $(LDFLAGS) -o $(BIN)/$@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

init:
	mkdir -p $(DIRS)

edit:
	gedit 2> /dev/null $(SRC)/* $(INC)/*
	
clean: 
	rm -f $(OBJ)/*.o
	
cleaner: clean
	rm -f $(BIN)/*
	

