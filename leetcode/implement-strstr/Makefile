CC  := clang++ -std=c++11 -stdlib=libc++
BIN := str_str str_str_kmp

.PHONY: clean

default: build

build: $(BIN)

str_str: str_str.cc
	@$(CC) -o str_str str_str.cc

str_str_kmp: str_str_kmp.cc
	@$(CC) -o str_str_kmp str_str_kmp.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./str_str < data/input
	@./str_str_kmp < data/input
