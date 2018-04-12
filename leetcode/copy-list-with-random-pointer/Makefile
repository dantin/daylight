CC  := clang++ -std=c++11 -stdlib=libc++
BIN := copy_list_with_random_pointer

.PHONY: clean

default: build

build: $(BIN)

copy_list_with_random_pointer: copy_random_list.cc
	@$(CC) -o copy_list_with_random_pointer copy_random_list.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./copy_list_with_random_pointer
