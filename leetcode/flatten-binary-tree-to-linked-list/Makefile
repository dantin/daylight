CC  := clang++ -std=c++11 -stdlib=libc++
BIN := flatten

.PHONY: clean

default: build

build: $(BIN)

flatten: flatten.cc
	@$(CC) -o flatten flatten.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./flatten
