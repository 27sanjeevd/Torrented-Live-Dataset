CXX = clang++
CXXFLAGS = -std=c++17

all: tracker_server

tracker_server: tracker_server.cpp
	$(CXX) $(CXXFLAGS) $< -o tracker_server

clean:
	rm -f tracker_server