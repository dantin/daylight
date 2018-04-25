CC  := clang++ -std=c++11 -stdlib=libc++
BIN := gray_code gray_code_v2

.PHONY: clean

default: build

build: $(BIN)

gray_code: gray_code.cc
	@$(CC) -o gray_code gray_code.cc

gray_code_v2: gray_code_v2.cc
	@$(CC) -o gray_code_v2 gray_code_v2.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./gray_code    < data/input
	@./gray_code_v2 < data/input
