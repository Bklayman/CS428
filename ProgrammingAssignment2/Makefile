CXX = g++
CXXFLAGS = -g -Wall -std=c++17

all:		clean Client1 Client2 Server

Server:	Server.o
	$(CXX) $(CXXFLAGS) Server.o -o $@

Client1:	Client1.o
	$(CXX) $(CXXFLAGS) Client1.o -o $@

Client2:	Client2.o
	$(CXX) $(CXXFLAGS) Client2.o -o $@

clean:
	rm -f *~ *.o Server Client1 Client2
