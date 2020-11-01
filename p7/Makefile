LDLIBS = -lm
.PHONY: all
all: p7.30 plot.svg res.txt
p7.30: p7.30.o roots.o
plot.svg: res.txt
	gnuplot <gnuplot.gpl
res.txt: p7.30
	./p7.30 | ./proc.sh >res.txt
roots.o: roots.c roots.h
p7.30.o: p7.30.c roots.h
.PHONY: clean
clean:
	-rm -rf p7.30 p7.30.o roots.o res.txt plot.svg
