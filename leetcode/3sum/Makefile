CC  := clang++ -std=c++11 -stdlib=libc++
BIN := three_sum

.PHONY: clean

default: build

build: $(BIN)

three_sum: 3sum.cc
	@$(CC) -o three_sum 3sum.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./three_sum < data/input
