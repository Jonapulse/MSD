OBJS = main.o cmdline.o expr.o parse.o
CXX = g++
CXXFLAGS = -g
HEADERS = cmdline.h expr.h parse.hpp

all: msdscript

msdscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS)

main.o: main.cpp $(HEADERS)

cmdline.o: cmdline.cpp cmdline.h

expr.o: expr.cpp expr.h

parse.o: parse.cpp parse.hpp

help: main
	./main --help

clean: 
	rm -f *.o main *~ a.out

test: msdscript
	./msdscript --test

doc: msdscript
	cd doc && doxygen

.PHONY: clean test
