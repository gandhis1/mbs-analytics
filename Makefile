CXX=g++
CXXFLAGS=-std=c++14 -pedantic -Wall -Wextra -Werror
LDFLAGS=
LDLIBS=

bin/run_analytics.exe: obj/main.o obj/scenario.o
	g++ $(LDFLAGS) $(LDLIBS) -o bin/run_analytics.exe obj/main.o obj/scenario.o

obj/main.o: main.cpp scenario.h
	g++ $(CXXFLAGS) -c -o obj/main.o main.cpp

obj/scenario.o: scenario.cpp scenario.h
	g++ $(CXXFLAGS) -c -o obj/scenario.o scenario.cpp

# engine.o: engine.cpp engine.h
# 	g++ $(CXXFLAGS) -c -o obj/engine.o engine.cpp engine.h
