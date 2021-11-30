CXX = g++
CXXFLAGS = -g -Wall -std=c++17

all:		clean Dijkstras

Dijkstras:	Dijkstras.o
	$(CXX) $(CXXFLAGS) Dijkstras.o -o $@

clean:
	rm -f *~ *.o Dijkstras
