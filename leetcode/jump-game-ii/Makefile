CC  := clang++ -std=c++11 -stdlib=libc++
BIN := jump

.PHONY: clean

default: build

build: $(BIN)

jump: jump.cc
	@$(CC) -o jump jump.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./jump < data/input
