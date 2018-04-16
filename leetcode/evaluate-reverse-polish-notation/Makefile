CC  := clang++ -std=c++11 -stdlib=libc++
BIN := rpn

.PHONY: clean

default: build

build: $(BIN)

rpn: eval_rpn.cc
	@$(CC) -o rpn eval_rpn.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./rpn < data/input
