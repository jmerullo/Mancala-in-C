CC = gcc

SRC = ./src/*.c
IDIR = ./include/
CFLAGS = -lncurses -I$(IDIR)

LIBS = `pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5`

all: mancala run clean

mancala:
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o Mancala

run:
	./Mancala

clean:
	rm Mancala