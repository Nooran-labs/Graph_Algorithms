# noorangnaim@gmail.com
CXX = g++
CXXFLAGS = -g -Wall
SRC = Algorithms.cpp graphs.cpp
HEADERS = Algorithms.h Graph.h

# Default target
all: main

main: main.cpp $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) main.cpp $(SRC) -o main

test: test_graph_algorithms.cpp $(SRC) $(HEADERS) doctest.h
	$(CXX) $(CXXFLAGS) test_graph_algorithms.cpp $(SRC) -o test

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -f main test *.o *.out *.exe

