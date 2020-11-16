HC = ghc
FC = gfortran
CXXFLAGS = -std=c++17 -Wall -pedantic -Wextra
FFLAGS = -std=f2018 -Wall -pedantic -Wextra
HCFLAGS = -O2
.PHONY: all
all: p8cxx p8hs p8rect
p8cxx: p8cxx.o
	$(CXX) -o $@ $< $(LDFLAGS) $(LDLIBS)
p8cxx.o: p8cxx.cpp

p8hs: p8hs.o
	$(HC) -o $@ $<
p8hs.o: p8hs.hs
	$(HC) $(HCFLAGS) -c $<

p8rect: p8rect.o
	$(FC) $(LDFLAGS) -o $@ $< $(LDLIBS)
p8rect.o: p8rect.f03
	$(FC) $(FFLAGS) -c $<
.PHONY: clean
clean:
	-rm -f p8hs p8hs.o p8hs.hi
	-rm -f p8rect p8rect.o
	-rm -f p8cxx p8cxx.o
