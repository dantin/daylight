CC  := clang++ -std=c++11 -stdlib=libc++
BIN := climbing_stairs

.PHONY: clean

default: build

build: $(BIN)

climbing_stairs: climbing_stairs.cc
	@$(CC) -o climbing_stairs climbing_stairs.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./climbing_stairs < data/input

