CXX = c++
CXXFLAGS = -std=c++17
LIB_DIR = Library_msdscript
LIB_NAME = my_library
LDFLAGS = -L$(LIB_DIR) -l$(LIB_NAME)

all: msdscript

msdscript: main.o
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

help: main
	./main --help

clean: 
	rm -f *.o main *~ a.out

test: msdscript
	./msdscript --test

doc: msdscript
	cd doc && doxygen

.PHONY: clean test
