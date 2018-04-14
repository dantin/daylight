CC  := clang++ -std=c++11 -stdlib=libc++
BIN := min_distance

.PHONY: clean

default: build

build: $(BIN)

min_distance: min_distance.cc
	@$(CC) -o min_distance min_distance.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./min_distance < data/input
