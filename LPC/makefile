CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
TARGET = programa

SRCS = main.cpp
HEADERS = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
	@rm -f *.o

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all run clean