.PHONY: all

all: ../../build/display.o

../../build/display.o: display.c ../../build
	${CC} ${CFLAGS} -c -o ../../build/display.o display.c

../../build:
	mkdir -p ../../build
