SOURCES:=$(wildcard */*.c)
BINARIES:=$(SOURCES:.c=)

.PHONY: all clean test debug

all: $(BINARIES)

%: %.c
	gcc -g -DONLINE_JUDGE -fno-tree-ch -O2 -Wall -std=c99 -pipe $< -o $@ -lm

clean:
	rm -f $(BINARIES)

test:
	@sh ./test $(BINARIES)

debug:
	@echo $(SOURCES)
	@echo $(BINARIES)
