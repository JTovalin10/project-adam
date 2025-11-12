CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

TEST_FLAGS = -lgtest_main -lgtest -pthread

TEST_TARGET = BloomFilter_Test

TEST_SOURCE = BloomFilter_gtest.cpp

all: test

test: $(TEST_TARGET)
		./$(TEST_TARGET)

# This is the CORRECT command:
$(TEST_TARGET): $(TEST_SOURCE) BloomFilter.h
	$(CXX) $(CXXFLAGS) $(TEST_SOURCE) -o $(TEST_TARGET) $(TEST_FLAGS)

clean:
	rm -f $(TEST_TARGET) *.o
