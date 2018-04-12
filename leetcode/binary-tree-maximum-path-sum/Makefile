CC  := clang++ -std=c++11 -stdlib=libc++
BIN := max_path_sum

.PHONY: clean

default: build

build: $(BIN)

max_path_sum: max_path_sum.cc
	@$(CC) -o max_path_sum max_path_sum.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./max_path_sum
