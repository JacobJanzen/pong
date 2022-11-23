TEST_DEPENDENCIES=../build/test_game.o
DEPENDENCIES=../build/game.o

.PHONY: all game

all: game test.c ${TEST_DEPENDENCIES} ${DEPENDENCIES}
	${CC} -o ../build/test test.c ${TEST_DEPENDENCIES} ${DEPENDENCIES}

game:
	$(MAKE) -C game/
