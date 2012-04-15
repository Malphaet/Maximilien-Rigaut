CC = gcc
BIN = ./bin/
DATA_OUT = ./data/out/
INC = ./include/
OBJ = ./obj/
SRC = ./src/
CFLAGS = -W -Wall -ansi -pedantic -I$(INC) -O3 -g

all: $(BIN)main

$(BIN)main: $(OBJ)main.o $(OBJ)imageio.o $(OBJ)image_utils.o $(OBJ)temperature.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ)main.o: $(SRC)main.c $(INC)imageio.h $(INC)image_utils.h $(INC)image_types.h $(INC)temperature.h
	$(CC) $(CFLAGS) -c -o$@ $<

$(OBJ)temperature.o: $(SRC)temperature.c $(INC)imageio.h $(INC)image_utils.h $(INC)image_types.h $(INC)temperature.h
	$(CC) $(CFLAGS) -c -o$@ $<

$(OBJ)image_utils.o: $(SRC)image_utils.c $(INC)image_utils.h $(INC)image_types.h
	$(CC) $(CFLAGS) -c -o$@ $<

$(OBJ)imageio.o: $(SRC)imageio.c $(INC)imageio.h $(INC)image_types.h
	$(CC) $(CFLAGS) -c -o$@ $<

$(OBJ)image_effects.o: $(SRC)image_effects.c $(INC)image_effects.h $(INC)image_types.h
	$(CC) $(CFLAGS) -c -o$@ $<

clean:
	rm -f $(OBJ)*.o $(BIN)main* $(DATA_OUT)*.pgm