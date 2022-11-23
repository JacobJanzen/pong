CFLAGS=-Wall -Wextra -pedantic -Werror -std=c11 -O2
.PHONY: all

all: ../../build/game.o

../../build/game.o: game.c ../../build
	${CC} -c -o ../../build/game.o game.c

../../build:
	mkdir -p ../../build
