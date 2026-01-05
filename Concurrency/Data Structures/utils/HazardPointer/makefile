# Makefile for Hazard Pointer Utility

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -pthread
GTEST_FLAGS = -lgtest -lgtest_main -pthread

TARGET = hazard_test
SOURCES = HazardPointer_gtest.cpp
HEADERS = HazardPointer.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(GTEST_FLAGS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all test clean
