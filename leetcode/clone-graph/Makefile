CC  := clang++ -std=c++11 -stdlib=libc++
BIN := clone_graph

.PHONY: clean

default: build

build: $(BIN)

clone_graph: clone_graph.cc
	@$(CC) -o clone_graph clone_graph.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./clone_graph
