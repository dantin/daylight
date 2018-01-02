CC  := clang++ -std=c++11 -stdlib=libc++
BIN := two_sum

.PHONY: clean

default: build

build: $(BIN)

two_sum: two_sum.cc
	@$(CC) -o two_sum two_sum.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./two_sum < data/input
