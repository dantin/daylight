CC  := clang++ -std=c++11 -stdlib=libc++
BIN := max_area

.PHONY: clean

default: build

build: $(BIN)

max_area: max_area.cc
	@$(CC) -o max_area max_area.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./max_area < data/input
