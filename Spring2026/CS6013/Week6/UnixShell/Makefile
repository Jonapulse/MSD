OBJS = main.o shelpers.o jshell.o
CXX = g++
CXXFLAGS = -g
HEADERS = shelpers.hpp jshell.hpp

all: jshell

jshell: $(OBJS)
	$(CXX) $(CXXFLAGS) -o jshell $(OBJS)

main.o: main.cpp $(HEADERS)

shelpers.o: shelpers.cpp shelpers.hpp

jshell.o: jshell.cpp jshell.hpp

run:
	cd $(CURDIR) && ./jshell

clean: 
	rm -f *.o jshell *~ a.out

.PHONY: clean test
