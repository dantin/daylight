CC  := clang++ -std=c++11 -stdlib=libc++
BIN := 3sum_closest

.PHONY: clean

default: build

build: $(BIN)

3sum_closest: 3sum_closest.cc
	@$(CC) -o 3sum_closest 3sum_closest.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./3sum_closest < data/input
