# Makefile for CS170-Project2
CXX     = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2

# Executable name
TARGET  = feature_selection

# Source files
SRCS = main.cpp feature_selection.cpp nn_classifier.cpp dataset.cpp

# Object files (same as SRCS but with .o)
OBJS    = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp feature_selection.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
