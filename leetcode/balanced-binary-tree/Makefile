CC  := clang++ -std=c++11 -stdlib=libc++
BIN := balanced_binary_tree

.PHONY: clean

default: build

build: $(BIN)

balanced_binary_tree: is_balanced.cc
	@$(CC) -o balanced_binary_tree is_balanced.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./balanced_binary_tree
