
CXX=c++
CXX=g++
CXXFLAGS= -g -std=c++11 -Wall -Wconversion -Wextra -pedantic

all2: test
	./test

test: 

all: select/select qsort/qsort CountingSort/main


clean: 
	rm -f select/select qsort/qsort CountingSort/main
