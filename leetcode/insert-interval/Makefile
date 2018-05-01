CC  := clang++ -std=c++11 -stdlib=libc++
BIN := insert_interval

.PHONY: clean

default: build

build: $(BIN)

insert_interval: insert_interval.cc
	@$(CC) -o insert_interval insert_interval.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./insert_interval < data/input
