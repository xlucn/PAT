SOURCES:=$(wildcard */*.c)
BINARIES:=$(SOURCES:.c=)

.PHONY: all clean test debug

all: $(BINARIES)

%: %.c
	gcc -g -Wall $< -o $@ -lm

clean:
	rm -f $(BINARIES)

test:
	@sh ./test $(BINARIES)

debug:
	@echo $(SOURCES)
	@echo $(BINARIES)
