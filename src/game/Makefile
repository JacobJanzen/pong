.PHONY: all

all: ../../build/game.o

../../build/game.o: game.c ../../build
	${CC} -c -o ../../build/game.o game.c

../../build:
	mkdir -p ../../build
