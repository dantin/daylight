CC := clang++ -std=c++11 -stdlib=libc++
BIN := insert_sort bubble_sort selection_sort stable_sort shell_sort

.PHONY: clean

default: build

build: $(BIN)

insert_sort: insert_sort.cc
	@$(CC) -o insert_sort insert_sort.cc

bubble_sort: bubble_sort.cc
	@$(CC) -o bubble_sort bubble_sort.cc

selection_sort: selection_sort.cc
	@$(CC) -o selection_sort selection_sort.cc

stable_sort: stable_sort.cc
	@$(CC) -o stable_sort stable_sort.cc

shell_sort: shell_sort.cc
	@$(CC) -o shell_sort shell_sort.cc

clean:
	@rm -rf *~ $(BIN)

run: build
	@ echo "insert sort"
	@./insert_sort < data/insert_sort.txt
	@ echo "bubble sort"
	@./bubble_sort < data/bubble_sort.txt
	@ echo "selection sort"
	@./selection_sort < data/selection_sort.txt
	@ echo "stable sort"
	@./stable_sort < data/stable_sort.txt
	@ echo "shell sort"
	@./shell_sort < data/shell_sort.txt
