.PHONY: all cilk_sum clean

BINDIR := bin

CXX = clang++
CXXFLAGS = -Wall $(opt)


cilk_sum: opencilk_reducer.cpp
	mkdir -p $(BINDIR)
	$(CXX) -o bin/cilk_sum  cilk_sum.cpp  $(CXXFLAGS) -fopencilk 

cilk_max: opencilk_reducer.cpp 
	mkdir -p $(BINDIR)
	$(CXX) -o bin/cilk_max  cilk_max.cpp  $(CXXFLAGS) -fopencilk 
