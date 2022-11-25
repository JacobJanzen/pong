export

.PHONY: all display game log

all: display game log ../build

display:
	$(MAKE) -C display/

game:
	$(MAKE) -C game/

log:
	$(MAKE) -C log/

../build:
	mkdir -p ../build
