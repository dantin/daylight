CC  := clang++ -std=c++11 -stdlib=libc++
BIN := inorder_iterator inorder_recursive

.PHONY: clean

default: build

build: $(BIN)

inorder_iterator: inorder_iterator.cc
	@$(CC) -o inorder_iterator inorder_iterator.cc

inorder_recursive: inorder_recursive.cc
	@$(CC) -o inorder_recursive inorder_recursive.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./inorder_iterator
	@./inorder_recursive
