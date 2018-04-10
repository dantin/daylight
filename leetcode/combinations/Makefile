CC  := clang++ -std=c++11 -stdlib=libc++
BIN := combinations

.PHONY: clean

default: build

build: $(BIN)

combinations: combinations.cc
	@$(CC) -o combinations combinations.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./combinations < data/input
