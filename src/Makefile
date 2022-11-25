export

.PHONY: all display game log timer

all: display game log timer ../build

display:
	$(MAKE) -C display/

game:
	$(MAKE) -C game/

log:
	$(MAKE) -C log/

timer:
	$(MAKE) -C timer/

../build:
	mkdir -p ../build
