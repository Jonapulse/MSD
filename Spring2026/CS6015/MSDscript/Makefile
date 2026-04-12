OBJS = main.o cmdline.o expr.o val.o parse.o env.o
CXX = g++
CXXFLAGS = -g -fPIC
HEADERS = cmdline.h expr.h val.h parse.hpp pointer.h env.h
LIB_NAME = libmsdscript.dylib
LIB_OBJS = expr_lib.o val_lib.o parse_lib.o env_lib.o

all: msdscript

msdscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS)

main.o: main.cpp $(HEADERS)

cmdline.o: cmdline.cpp cmdline.h

expr.o: expr.cpp expr.h pointer.h

val.o: val.cpp val.h pointer.h

parse.o: parse.cpp parse.hpp pointer.h

env.o: env.cpp env.h pointer.h

help: main
	./main --help

clean: 
	rm -f *.o main *~ a.out $(LIB_NAME) *_lib.o

test: msdscript
	./msdscript --test

test_gen_solo: compile_test_gen
	./generated_test msdscript

test_gen_twos: compile_test_gen
	echo mine vs msdscript1
	./generated_test msdscript testing/msdscript1 > testing/compLog1.txt
	echo mine vs msdscript2
	./generated_test msdscript testing/msdscript2 > testing/compLog2.txt
	echo mine vs msdscript3
	./generated_test msdscript testing/msdscript3 > testing/compLog3.txt
	echo mine vs msdscript4
	./generated_test msdscript testing/msdscript4 > testing/compLog4.txt
	echo mine vs msdscript5
	./generated_test msdscript testing/msdscript5 > testing/compLog5.txt
	echo mine vs msdscript6
	./generated_test msdscript testing/msdscript6 > testing/compLog6.txt
	echo mine vs msdscript7
	./generated_test msdscript testing/msdscript7 > testing/compLog7.txt


compile_test_gen: run_msdscript.cpp exec.cpp
	g++ run_msdscript.cpp exec.cpp -o generated_test

test_test: e_run_wc.cpp exec.cpp
	g++ e_run_wc.cpp exec.cpp -o test_test

doc: msdscript
	cd doc && doxygen

make_lib: $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) -shared -fPIC -o $(LIB_NAME) $(LIB_OBJS)

%_lib.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -DNTEST -c -o $@ $<

.PHONY: clean test
