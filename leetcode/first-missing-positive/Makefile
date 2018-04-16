CC  := clang++ -std=c++11 -stdlib=libc++
BIN := missing_positive

.PHONY: clean

default: build

build: $(BIN)

missing_positive: missing_positive.cc
	@$(CC) -o missing_positive missing_positive.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./missing_positive < data/input
