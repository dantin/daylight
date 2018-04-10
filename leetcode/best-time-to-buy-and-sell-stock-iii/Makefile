CC  := clang++ -std=c++11 -stdlib=libc++
BIN := max_profit

.PHONY: clean

default: build

build: $(BIN)

max_profit: max_profit.cc
	@$(CC) -o max_profit max_profit.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./max_profit < data/input
