SOURCES:=$(wildcard */*.c)
BINARIES:=$(SOURCES:.c=)

.PHONY: all clean test debug

all: $(BINARIES)

%: %.c
	clang -DONLINE_JUDGE -O2 -Wall -std=c99 -pipe $< -lm -o $@

clean:
	rm -f $(BINARIES)

test:
	@mkdir -p temp; \
	tracked_files=$$(git ls-tree --name-only HEAD PAT*/); \
	for bin in $(BINARIES); do \
		[ "$$tracked_files" = "$${tracked_files%$$bin*}" ] && continue; \
		dir=$$(dirname "$$bin"); \
		id=$$(basename "$$bin"); \
		case "$$dir" in \
			PATAdvanced) cat=a;; \
			PATBasic)    cat=b;; \
			PATTop)      cat=t;; \
		esac; \
		for sample in "samples/$$cat$$id-"*.in; do \
			echo "testing $$bin, sample $$sample"; \
			printf "%s" "$$("$$dir/$$id" < "$$sample" | tr -d '\0')" > temp/out; \
			printf "%s" "$$(cat "$${sample%.in}.out")" > temp/ans; \
			diff temp/out temp/ans || failed="$$failed$$bin $$sample\n"; \
		done; \
	done; \
	rm -r temp
	@str_check_output="Scroll back for answer and actuall output"; \
	cred="\033[1;31m"; \
	cgreen="\033[1;32m"; \
	creset="\033[1;0m"; \
	if [ -n "$$failed" ]; then \
		printf "$$failed%s" | while read -r b s; do \
			printf "$$cred%s failed for sample %s$$creset\n" "$$b" "$$s"; \
		done; \
		printf "$$cred%s$$creset\n" "$$str_check_output"; \
		exit 1; \
	else \
		printf "$$cgreen%s$$creset\n" "All passed!"; \
	fi


debug:
	@echo $(SOURCES)
	@echo $(BINARIES)
