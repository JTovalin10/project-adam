CXX = g++

CXX_FLAGS = -Wall -Wextra -g -std=c++17

GTEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_SOURCE = QuickSort_test

TEST_FILE = QuickSort_gtest.cpp

all: test

test: $(TEST_SOURCE)
	./$(TEST_SOURCE)

$(TEST_SOURCE): $(TEST_FILE) QuickSort.h
	$(CXX) $(CXX_FLAGS) $(TEST_FILE) $(GTEST_FLAGS) -o $(TEST_SOURCE)

clean:
	rm -f $(TEST_SOURCE) *.o
