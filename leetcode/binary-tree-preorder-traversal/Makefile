CC  := clang++ -std=c++11 -stdlib=libc++
BIN := preorder_iterator

.PHONY: clean

default: build

build: $(BIN)

preorder_iterator: preorder_iterator.cc
	@$(CC) -o preorder_iterator preorder_iterator.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./preorder_iterator
