CC  := clang++ -std=c++11 -stdlib=libc++
BIN := convert_bst

.PHONY: clean

default: build

build: $(BIN)

convert_bst: sorted_array_to_bst.cc
	@$(CC) -o convert_bst sorted_array_to_bst.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./convert_bst < data/input
