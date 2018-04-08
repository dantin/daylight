CC  := clang++ -std=c++11 -stdlib=libc++
BIN := group_anagrams

.PHONY: clean

default: build

build: $(BIN)

group_anagrams: group_anagrams.cc
	@$(CC) -o group_anagrams group_anagrams.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./group_anagrams < data/input
