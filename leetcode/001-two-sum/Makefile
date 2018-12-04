
SOURCE_DIR := $(shell pwd)

CC  := clang++ -std=c++11 -stdlib=libstdc++
GCC := gcc -O2

BIN := scc sc

default: build

build: $(BIN)

sc: two_sum.c
	@$(GCC) -o sc two_sum.c

scc: two_sum.cc
	@$(CC) -o scc two_sum.cc

scc2: two_sum_2.cc
	@$(CC) -o scc2 two_sum_2.cc

.PHONY: clean
clean:
	@echo $(BIN)
	@rm -rf *~ $(BIN)

.PHONY: run
run: build
	@./sc
	@./scc < data/input
	@#./scc_2 < data/input
