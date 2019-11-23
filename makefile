SHELL:=/bin/bash
SOURCES:=$(wildcard */*.c)
BINARIES:=$(SOURCES:.c=)

all: $(BINARIES)

%: %.c
	gcc -g -Wall $< -o $@ -lm

clean:
	rm -f $(BINARIES)

test: $(BINARIES)
	@mkdir -p temp;\
	tracked_files=$$(git ls-tree --name-only HEAD PATAdvanced/ PATBasic/);\
	for bin in $(BINARIES);\
	do\
		if [ "$$tracked_files" = "$${tracked_files/$$bin/}" ]; then\
			echo not tracking $$bin\'s source;\
			continue;\
		fi;\
		cat=;\
		dir=$$(dirname $$bin);\
		id=$$(basename $$bin);\
		if [ $$dir = PATAdvanced ]; then cat=a; fi;\
		if [ $$dir = PATBasic    ]; then cat=b; fi;\
		if [ $$dir = PATTop      ]; then cat=t; fi;\
		for sample in samples/$$cat$$id-*.in;\
		do\
			echo testing $$bin, sample $$sample;\
			printf %s "$$($$dir/$$id < $$sample)" > temp/out;\
			printf %s "$$(cat $${sample/in/out})" > temp/ans;\
			diff temp/out temp/ans;\
		done;\
		if [ $$cat = b ] && [ $$id = 1041 ]; then exit; fi;\
	done;\
	rm -r temp

debug:
	@echo $(SOURCES)
	@echo $(BINARIES)
