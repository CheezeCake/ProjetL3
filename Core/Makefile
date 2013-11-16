CXX=c++
AR=ar
CXXFLAGS=-O2 -Wall
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
LIB_DIR=lib/
TARGET=$(LIB_DIR)libsolver.a

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(LIB_DIR)
	@$(AR) rv $@ $^

%.o: %.cpp %.hpp
	$(CXX) -c $< $(CXXFLAGS)

.PHONY: clean mrproper rebuild

clean:
	@rm -rf *.o

mrproper: clean
	@rm -f $(TARGET)

rebuild: mrproper all
