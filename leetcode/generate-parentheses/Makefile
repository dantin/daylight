CC  := clang++ -std=c++11 -stdlib=libc++
BIN := generate_parentheses

.PHONY: clean

default: build

build: $(BIN)

generate_parentheses: generate_parentheses.cc
	@$(CC) -o generate_parentheses generate_parentheses.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./generate_parentheses < data/input
