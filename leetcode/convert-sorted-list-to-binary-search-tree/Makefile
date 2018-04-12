CC  := clang++ -std=c++11 -stdlib=libc++
BIN := convert_to_bst

.PHONY: clean

default: build

build: $(BIN)

convert_to_bst: sorted_list_to_bst.cc
	@$(CC) -o convert_to_bst sorted_list_to_bst.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./convert_to_bst < data/input
