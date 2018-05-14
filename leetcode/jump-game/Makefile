CC  := clang++ -std=c++11 -stdlib=libc++
BIN := can_jump

.PHONY: clean

default: build

build: $(BIN)

can_jump: can_jump.cc
	@$(CC) -o can_jump can_jump.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./can_jump < data/input
