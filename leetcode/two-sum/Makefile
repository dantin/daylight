CC  := clang++ -std=c++11 -stdlib=libc++
BIN := two_sum two_sum_2

.PHONY: clean

default: build

build: $(BIN)

two_sum: two_sum.cc
	@$(CC) -o two_sum two_sum.cc

two_sum_2: two_sum_2.cc
	@$(CC) -o two_sum_2 two_sum_2.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./two_sum < data/input
	@./two_sum_2 < data/input
