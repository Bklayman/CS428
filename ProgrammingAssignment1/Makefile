CXX = g++
CXXFLAGS = -g -Wall -std=c++17

CXX_FILES = $(wildcard *.cpp)

OFILES = $(CXX_FILES:cc=o)

all:		clean udp_ping_client udp_ping_server

udp_ping_server:	udp_ping_server.o
	$(CXX) $(CXXFLAGS) udp_ping_server.o -o $@

udp_ping_client:	udp_ping_client.o
	$(CXX) $(CXXFLAGS) udp_ping_client.o -o $@

clean:
	rm -f *~ *.o udp_ping_server udp_ping_client
