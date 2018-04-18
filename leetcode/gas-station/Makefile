CC  := clang++ -std=c++11 -stdlib=libc++
BIN := check_circuit

.PHONY: clean

default: build

build: $(BIN)

check_circuit: can_complete_circuit.cc
	@$(CC) -o check_circuit can_complete_circuit.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@./check_circuit < data/input
