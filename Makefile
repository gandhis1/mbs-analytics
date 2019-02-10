CXX=g++
CXXFLAGS=-std=c++14 -pedantic -Wall -Wextra -Werror
LDFLAGS=
LDLIBS=

run_analytics: main.o scenario.o
	g++ $(LDFLAGS) $(LDLIBS) -o bin/run_analytics.exe obj/main.o obj/scenario.o

main.o: main.cpp scenario.h
	g++ $(CXXFLAGS) -c -o obj/main.o main.cpp

scenario.o: scenario.cpp scenario.h
	g++ $(CXXFLAGS) -c -o obj/scenario.o scenario.cpp

# engine.o: engine.cpp engine.h
# 	g++ $(CXXFLAGS) -c -o obj/engine.o engine.cpp engine.h
