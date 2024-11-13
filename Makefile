CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
LIBS = -lSDL2 -lSDL2main -lSDL2_image

SRC = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin
OUTPUT = $(BIN)/week_game

.PHONY: all clean

all: dirs game

dirs: 
	mkdir -p ./$(BIN)

game: $(OBJ)
	$(CC) -o $(OUTPUT) $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

run: all
	$(OUTPUT)

clean:
	rm -rf $(BIN) $(OBJ)
