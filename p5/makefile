compare: compare.o funs.o
compare.o: compare.c funs.h

reverse: reverse.o funs.o
reverse.o: reverse.c funs.h

funs.o: funs.c funs.h

modify: modify.o funs.o
modify.o: modify.c funs.h

fib: funs.o fib.o
fib.o: fib.c funs.h

.PHONY: clean
clean:
	-rm -f funs.o fib.o fib modify modify.o reverse reverse.o
