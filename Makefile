CFLAGS=-Wall -Wextra -pedantic -std=c11

.PHONY: all clean src app test

all: app

app: src
	$(MAKE) -C app/

src:
	$(MAKE) -C src/

test: src
	$(MAKE) -C test/
	./build/test

clean:
	rm -rf bin/ build/
