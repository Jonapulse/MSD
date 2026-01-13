OBJS = main.o cmdline.o
CXX = g++
CXXFLAGS = -g
HEADERS = cmdline.h

all: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cpp $(HEADERS)

cmdline.o: cmdline.cpp cmdline.h

help: main
	./main --help

clean: 
	rm -f *.o main *~ a.out

.PHONY: clean
