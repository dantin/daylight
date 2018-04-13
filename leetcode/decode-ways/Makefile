CC  := clang++ -std=c++11 -stdlib=libc++
BIN := num_decodings

.PHONY := clean

default: build

build: $(BIN)

num_decodings: num_decodings.cc
	@$(CC) -o num_decodings num_decodings.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./num_decodings < data/input
