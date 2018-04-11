CC  := clang++ -std=c++11 -stdlib=libc++
BIN := level_order

.PHONY: clean

default: build

build: $(BIN)

level_order: traversal.cc
	@$(CC) -o level_order traversal.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./level_order
