CC  := clang++ -std=c++11 -stdlib=libc++
BIN := divide

.PHONY: clean

default: build

build: $(BIN)

divide: divide.cc
	@$(CC) -o divide divide.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./divide < data/input
