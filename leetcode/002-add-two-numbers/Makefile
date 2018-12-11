SOURCE_DIR := $(shell pwd)

CC  := clang++ -std=c++11 -stdlib=libstdc++
GCC := gcc -O2

BIN := solution_cc solution_c

default: build

build: $(BIN)

solution_cc: add_two_numbers.cc
	@$(CC) -o solution_cc add_two_numbers.cc

solution_c: add_two_numbers.cc
	@$(GCC) -o solution_c add_two_numbers.c

.PHONY: clean
clean:
	@rm -rf *~ $(BIN)

.PHONY: run
run: build
	@./solution_cc < data/input
	@./solution_c 243 564
