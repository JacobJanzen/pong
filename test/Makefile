TEST_DEPENDENCIES=../build/test_game.o ../build/test_timer.o
DEPENDENCIES=../build/game.o ../build/timer.o ../build/log.o
LIBS=-lSDL2

.PHONY: all game timer

all: game timer test.c ${TEST_DEPENDENCIES} ${DEPENDENCIES}
	${CC} -o ../build/test test.c ${TEST_DEPENDENCIES} ${DEPENDENCIES} ${LIBS}

game:
	$(MAKE) -C game/

timer:
	$(MAKE) -C timer/
