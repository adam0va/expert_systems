CXX = g++
CXXFLAGS = -Wall -g
SOURCES = fact.cpp rule.cpp graph.cpp main.cpp
HEADERS = fact.hpp rule.hpp graph.hpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main: fact.o rule.o graph.o main.o
	$(CXX) $^ -o $@

clean:
	rm -rf *.o *.dSYM main
