SOURCES:=$(shell find ./ -name '*.c')
BINARIES:=$(SOURCES:%.c=%)

all: $(BINARIES)

%: %.c
	gcc -g -Wall $< -o $@ -lm

clean:
	rm $(BINARIES)
