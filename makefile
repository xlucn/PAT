SOURCES:=$(wildcard */*.c)
BINARIES:=$(SOURCES:.c=)

all: $(BINARIES)

%: %.c
	gcc -g -Wall $< -o $@ -lm

clean:
	rm -f $(BINARIES)

test:
	@echo $(SOURCES)
	@echo $(BINARIES)
