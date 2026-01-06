INCS = Clothing.h Caps.h Pants.h
OBJS = main.o Clothing.o Pants.o Caps.o
CXX = c++
CXXFLAGS = --std=c++14 -O2
CXXSOURCE = main.cpp Clothing.cpp Caps.cpp Pants.cpp
HEADERS = Clothing.h Caps.h Pants.h

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cpp

Clothing.o: Clothing.cpp Clothing.h

Caps.o: Caps.cpp Caps.h

Pants.o: Pants.cpp Pants.h

run: $(OBJS)
	./main

.PHONY: clean printM
clean:
	rm -rf *.o; rm main

printM:
	echo $(CXXSOURCE); echo $(HEADERS);
