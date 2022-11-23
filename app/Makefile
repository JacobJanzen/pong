CFLAGS=-Wall -Wextra -pedantic -std=c11
DEPENDENCIES=../build/display.o
LIBS=-lSDL2

.PHONY: all clean

all: ../bin/pong

../bin/pong: main.c ../bin
	${CC} ${CFLAGS} -o ../bin/main main.c ${DEPENDENCIES} ${LIBS}

../bin:
	mkdir -p ../bin

