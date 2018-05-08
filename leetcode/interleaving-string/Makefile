CC  := clang++ -std=c++11 -stdlib=libc++
BIN := is_interleave

.PHONY: clean

default: build

build: $(BIN)

is_interleave: is_interleave.cc
	@$(CC) -o is_interleave is_interleave.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./is_interleave < data/input
