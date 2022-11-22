TEST_DEPENDENCIES=../build/test_temp.o 
DEPENDENCIES=../build/temp.o

.PHONY: all temp

all: temp
	${CC} -o ../build/test test.c ${TEST_DEPENDENCIES} ${DEPENDENCIES}

temp:
	$(MAKE) -C temp/
