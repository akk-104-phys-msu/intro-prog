CFLAGS=-std=c11 -pedantic -Wall
programs = hello empty
.PHONY: all
all: $(programs)
$(programs): % : %.o
$(programs:=.o): %.o : %.c
.PHONY: clean
clean:
	-rm -f $(programs) $(programs:=.o)
