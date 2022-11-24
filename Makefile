CFLAGS=-Wall -Wextra -pedantic -std=c11 -O2
export

.PHONY: all clean src app test run

all: app

app: src
	$(MAKE) -C app/

src:
	$(MAKE) -C src/

test: src
	$(MAKE) -C test/
	./build/test

run: app
	./bin/pong

clean:
	rm -rf bin/ build/
