CFLAGS = -std=c11 -Wall -Wextra
LDFLAGS =
.PHONY: all
all: ex.6.9 sort sort2
ex.6.9: ex.6.9.o
ex.6.9.o: ex.6.9.c
sort: sort.o
sort.o: sort.c
sort2: sort2.o
sort2.o: sort2.c
.PHONY:clean
clean:
	-rm -f sort sort.o ex.6.9 ex.6.9.o sort2 sort2.o
