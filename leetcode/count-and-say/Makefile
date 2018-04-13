CC  := clang++ -std=c++11 -stdlib=libc++
BIN := count_and_say

.PHONY: clean

default: build

build: $(BIN)

count_and_say: count_and_say.cc
	@$(CC) -o count_and_say count_and_say.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./count_and_say < data/input
