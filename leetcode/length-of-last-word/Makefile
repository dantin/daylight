CC  := clang++ -std=c++11 -stdlib=libc++
BIN := length_of_last_word

.PHONY: clean

default: build

build: $(BIN)

$(BIN): $(BIN).cc
	@$(CC) -o $(BIN) $(BIN).cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./$(BIN) < data/input
