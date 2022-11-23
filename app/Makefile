CFLAGS=-Wall -Wextra -pedantic -std=c11 -O2
DEPENDENCIES=../build/display.o ../build/game.o
LIBS=-lSDL2

.PHONY: all clean

all: ../bin/pong

../bin/pong: main.c ../bin ${DEPENDENCIES}
	${CC} ${CFLAGS} -o ../bin/main main.c ${DEPENDENCIES} ${LIBS}

../bin:
	mkdir -p ../bin

