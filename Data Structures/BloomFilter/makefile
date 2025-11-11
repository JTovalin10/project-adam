CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

TEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = BloomFilter_Test

TEST_SOURCE = BloomFilter_gtest.cpp

all: test

test: $(TEST_TARGET)
		./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCE) BloomFilter.h
		$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -o $(TEST_TARGET)
