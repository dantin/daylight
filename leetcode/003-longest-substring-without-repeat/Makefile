SOURCE_DIR := $(shell pwd)

C  := gcc -O2

BIN := solution_c

default: build

build: $(BIN)

solution_c: longest_substring_without_repeat.c
	@$(C) -o solution_c longest_substring_without_repeat.c

.PHONY: clean
clean:
	@rm -rf *~ $(BIN)

.PHONY: run
run: build
	@./solution_c abcabcbb
