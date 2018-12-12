SOURCE_DIR := $(shell pwd)
SOURCES    := $(shell find $(SOURCE_DIR) -name 'solution.*' | grep -vE '.py' | grep -vE '.git')

C  := gcc -O2

BIN := $(subst .,_,$(notdir $(SOURCES)))

default: build

build: $(BIN)
	@echo "$(BIN) done!"

solution_c: solution.c
	@$(C) $< -o $@

.PHONY: clean
clean:
	@rm -rf *~ $(BIN)

.PHONY: run
run: build
	@./solution_c abcabcbb
