SOURCE_DIR := $(shell pwd)
SOURCES    := $(shell find $(SOURCE_DIR) -name 'solution.*' | grep -vE '.py' | grep -vE '.git')

CC := clang++ -std=c++11 -stdlib=libstdc++
C  := gcc -O2

BIN := $(subst .,_,$(notdir $(SOURCES)))

default: build

build: $(BIN)
	@echo "$(BIN) done!"

solution_c: solution.c
	@$(C) $< -o $@

solution_cc: solution.cc
	@$(CC) $< -o $@

.PHONY: clean
clean:
	@rm -rf *~ $(BIN)

.PHONY: run
run: build
	@./solution_cc < data/input
	@./solution_c 243 564
