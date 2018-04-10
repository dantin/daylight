CC  := clang++ -std=c++11 -stdlib=libc++
BIN := construct_binary_tree

.PHONY: clean

default: build

build: $(BIN)

construct_binary_tree: build_tree.cc
	@$(CC) -o construct_binary_tree build_tree.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./construct_binary_tree < data/input
