CXX      = g++
CXXFLAGS = -fopenmp -Wall -Wextra -O2
FONTES   = $(wildcard *.cpp)
BINARIOS = $(FONTES:.cpp=)

all: $(BINARIOS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(BINARIOS)

.PHONY: all clean
