LDLIBS = -lm
.PHONY: all
all: p7.30 plot.svg res.txt plot2.svg
p7.30: p7.30.o roots.o
plot.svg: gnuplot.gpl res.txt
	gnuplot <gnuplot.gpl
res.txt: p7.30 proc.sh
	./p7.30 | ./proc.sh >res.txt
plot2.svg: p7.30 gnuplot.gpl
	./p7.30 | sed '1d;/^#/,$$d' | awk '{ print $$1, $$3, $$5 }' >res2.txt
	sed 's/res\.txt/res2\.txt/g;s/plot\.svg/plot2\.svg/;' < gnuplot.gpl | gnuplot
roots.o: roots.c roots.h
p7.30.o: p7.30.c roots.h
.PHONY: clean
clean:
	-rm -rf p7.30 p7.30.o roots.o res.txt plot.svg plot2.svg res2.txt
