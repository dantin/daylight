CC  := clang++ -std=c++11 -stdlib=libc++
BIN := largest_rectangle_area

.PHONY: clean

default: build

build: $(BIN)

largest_rectangle_area: largest_rectangle_area.cc
	@$(CC) -o largest_rectangle_area largest_rectangle_area.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./largest_rectangle_area < data/input
