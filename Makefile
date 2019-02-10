CXX=g++
CXXFLAGS=-std=c++14 -pedantic -Wall -Wextra -Werror
LDFLAGS=
LDLIBS=

bin/run_analytics: build/main.o build/scenario.o
	g++ $(LDFLAGS) $(LDLIBS) -o $@ $^

build/main.o: src/main.cpp
	g++ $(CXXFLAGS) -c -o build/main.o src/main.cpp

build/scenario.o: src/scenario.cpp
	g++ $(CXXFLAGS) -c -o build/scenario.o src/scenario.cpp

# build/engine.o: engine.cpp engine.h
# 	g++ $(CXXFLAGS) -c -o build/engine.o engine.cpp engine.h

clean:
	rm build/*.o
