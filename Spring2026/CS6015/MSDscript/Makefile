OBJS = main.o cmdline.o expr.o
CXX = g++
CXXFLAGS = -g
HEADERS = cmdline.h expr.h

all: msdscript

msdscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS)

main.o: main.cpp $(HEADERS)

cmdline.o: cmdline.cpp cmdline.h

expr.o: expr.cpp expr.h

help: main
	./main --help

clean: 
	rm -f *.o main *~ a.out

.PHONY: clean
