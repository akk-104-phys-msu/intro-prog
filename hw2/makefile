CFLAGS=-std=c11 -pedantic -Wall
LDLIBS=-lm
programs = hw2scanf hw2argv
.PHONY: all
all: $(programs)
$(programs): % : %.o
$(programs:=.o): %.o : %.c
.PHONY: clean
clean:
	-rm -f $(programs) $(programs:=.o)
