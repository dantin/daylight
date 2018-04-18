CC  := clang++ -std=c++11 -stdlib=libc++
BIN := flatten inorder_flatten

.PHONY: clean

default: build

build: $(BIN)

flatten: flatten.cc
	@$(CC) -o flatten flatten.cc

inorder_flatten: inorder_flatten.cc
	@$(CC) -o inorder_flatten inorder_flatten.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./flatten
	@./inorder_flatten
