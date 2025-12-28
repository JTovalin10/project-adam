CXX = g++

CXX_FLAGS = -Wall -Wextra -g -std=c++17

GTEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_SOURCE = CGStack_Test

TEST_FILE = CGStack_gtest.cpp

all: test

test: $(TEST_SOURCE)
	./$(TEST_SOURCE)

$(TEST_SOURCE): $(TEST_FILE) CGStack.h
	$(CXX) $(CXX_FLAGS) $(TEST_FILE) $(GTEST_FLAGS) -o $(TEST_SOURCE)

clean:
	rm -f $(TEST_SOURCE) *.o
