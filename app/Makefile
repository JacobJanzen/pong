CFLAGS=-Wall -Wextra -pedantic -std=c11

.PHONY: all clean

all: ../bin/pong

../bin/pong: main.c ../bin
	${CC} ${CFLAGS} -o ../bin/main main.c 

../bin:
	mkdir -p ../bin

