CC  := clang++ -std=c++11 -stdlib=libc++
BIN := int_to_roman

.PHONY: clean

default: build

build: $(BIN)

int_to_roman: int_to_roman.cc
	@$(CC) -o int_to_roman int_to_roman.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./int_to_roman < data/input
