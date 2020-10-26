CFLAGS = -std=c11 -Wall -Wextra
LDFLAGS =
.PHONY: all
all: ex.6.9 sort
ex.6.9: ex.6.9.o
ex.6.9.o: ex.6.9.c
sort: sort.o
sort.o: sort.c
.PHONY:clean
clean:
	-rm -f sort sort.o ex.6.9 ex.6.9.o
