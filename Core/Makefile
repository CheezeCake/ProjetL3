CXX=c++
CXXFLAGS=-O2 -Wall
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
TARGET=ProjetL3

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@

main.o: main.cpp
	$(CXX) -c $^ $(CXXFLAGS)

%.o: %.cpp %.hpp
	$(CXX) -c $< $(CXXFLAGS)

.PHONY: clean mrproper rebuild

clean:
	@rm -rf *.o

mrproper: clean
	@rm -f $(TARGET)

rebuild: mrproper all
