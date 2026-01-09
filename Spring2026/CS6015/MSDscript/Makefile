OBJS = main.o cmdline.o
CXX = g++
CXXFLAGS = -g
HEADERS = cmdline.h

all: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

cmdline.o: cmdline.cpp cmdline.h
	$(CXX) $(CXXFLAGS) -c cmdline.cpp -o cmdline.o

run: main
	./main

clean: 
	rm -f *.o main *~ a.out

.PHONY: all run clean
