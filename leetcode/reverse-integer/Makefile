CC  := clang++ -std=c++11 -stdlib=libc++
BIN := reverse_integer

.PHONY: clean

default: build

build: $(BIN)

reverse_integer: reverse_integer.cc
	@$(CC) -o reverse_integer reverse_integer.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@cat data/input | while read n; do (echo $$n | ./reverse_integer); done
