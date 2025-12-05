CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17

GTEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_SOURCE = Stack_Test

TEST_FILE = Stack_gtest.cpp

all: test

test: $(TEST_SOURCE)
	./$(TEST_SOURCE)

$(TEST_SOURCE): $(TEST_FILE) Stack.h
	$(CXX) $(CXXFLAGS) $(TEST_FILE) $(GTEST_FLAGS) -o $(TEST_SOURCE)

clean:
	rm -f $(TEST_SOURCE) *.o
