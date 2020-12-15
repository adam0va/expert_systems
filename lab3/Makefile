CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
SOURCES = argument.cpp predicate.cpp rule.cpp readInfo.cpp main.cpp
HEADERS = argument.hpp predicate.hpp rule.hpp readInfo.hpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main: argument.o predicate.o rule.o readInfo.o main.o
	$(CXX) $^ -o $@

clean:
	rm -rf *.o *.dSYM main
