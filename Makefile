# noavrd@gmail.com
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LINKFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: main test

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o $(LINKFLAGS)

test: test.o
	$(CXX) $(CXXFLAGS) -o test test.o $(LINKFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f main test *.o