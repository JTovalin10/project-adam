CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

GTEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = LRUCache_Test

TEST_SOURCE = LRUCache_gtest.cpp

all: test

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCE) LRUCache.h
			$(CXX) $(CXXFLAGS) $(TEST_SOURCE) $(GTEST_FLAGS) -o $(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET) *.o
