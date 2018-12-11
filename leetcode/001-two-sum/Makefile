
SOURCE_DIR := $(shell pwd)

CC := clang++ -std=c++11 -stdlib=libstdc++
C  := gcc -O2

BIN := solution_cc solution_c

default: build

build: $(BIN)

solution_c: two_sum.c
	@$(C) -o solution_c two_sum.c

solution_cc: two_sum.cc
	@$(CC) -o solution_cc two_sum.cc

#scc2: two_sum_2.cc
	#@$(CC) -o scc2 two_sum_2.cc

.PHONY: clean
clean:
	@rm -rf *~ $(BIN)

.PHONY: run
run: build
	@./solution_c
	@./solution_cc < data/input
	@#./scc_2 < data/input
