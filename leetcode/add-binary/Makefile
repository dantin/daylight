CC  := clang++ -std=c++11 -stdlib=libc++
BIN := add_binary

.PHONY: clean

default: build

build: $(BIN)

add_binary: add_binary.cc
	@$(CC) -o add_binary add_binary.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./add_binary < data/input
