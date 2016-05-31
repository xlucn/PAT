src=$(wildcard *.c)
bin=$(basename $(src))

all:$(bin)

%:%.c
	gcc -g -Wall -o $@ $< -lm

test:
	@echo $(src) $(bin)
