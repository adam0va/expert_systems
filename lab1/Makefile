CXX = g++
CXXFLAGS = -Wall -g
SOURCES = fact.cpp rule.cpp graph.cpp read_data.cpp main.cpp
HEADERS = fact.hpp rule.hpp graph.hpp read_data.hpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main: fact.o rule.o graph.o read_data.o main.o
	$(CXX) $^ -o $@

clean:
	rm -rf *.o *.dSYM main
