CC  := clang++ -std=c++11 -stdlib=libc++
BIN := combination_sum

.PHONY: clean

default: build

build: $(BIN)

combination_sum: combination_sum.cc
	@$(CC) -o combination_sum combination_sum.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./combination_sum < data/input
