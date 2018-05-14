CC  := clang++ -std=c++11 -stdlib=libc++
BIN := can_jump can_jump_v2

.PHONY: clean

default: build

build: $(BIN)

can_jump: can_jump.cc
	@$(CC) -o can_jump can_jump.cc

can_jump_v2: can_jump_v2.cc
	@$(CC) -o can_jump_v2 can_jump_v2.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./can_jump < data/input
	@./can_jump_v2 < data/input
