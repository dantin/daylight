OOT := $(shell dirname `pwd`)

vet:
	find $(ROOT) \( -iname "*.cpp" -o -iname "*.c" -o -iname "*.h" \) -print0 | \
		xargs -0 astyle --style=bsd -A1

clean:
	find $(ROOT) \( -iname "*.orig" -o -iname "*.o" \) -print0 | \
		xargs -0 rm -f
	find $(ROOT) \( -iname "a.out" \) -print0 | \
		xargs -0 rm -f
