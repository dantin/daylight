CC  := clang++ -std=c++11 -stdlib=libc++
BIN :=distinct_subseq

.PHONY: clean

default: build

build: $(BIN)

distinct_subseq: num_distinct.cc
	@$(CC) -o distinct_subseq num_distinct.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./distinct_subseq < data/input
