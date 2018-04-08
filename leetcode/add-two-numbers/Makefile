CC  := clang++ -std=c++11 -stdlib=libc++
BIN := add_two_numbers

.PHONY: clean

default: build

build: $(BIN)

add_two_numbers: add_two_numbers.cc
	@$(CC) -o add_two_numbers add_two_numbers.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./add_two_numbers < data/input
