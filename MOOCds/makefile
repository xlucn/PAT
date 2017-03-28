src=$(wildcard *.c)
bin=$(basename $(src))

all:$(bin)

%:%.c
	gcc -std=c11 -g -Wall -o $@ $< -lm

test:
	@echo $(src) $(bin)

rebuild:
	rm -f $(bin)
	make
