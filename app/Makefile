DEPENDENCIES=../build/display.o ../build/game.o ../build/log.o ../build/timer.o
LIBS=-lSDL2 -lm

.PHONY: all clean

all: ../bin/pong

../bin/pong: main.c ../bin ${DEPENDENCIES}
	${CC} ${CFLAGS} -o ../bin/pong main.c ${DEPENDENCIES} ${LIBS}

../bin:
	mkdir -p ../bin

