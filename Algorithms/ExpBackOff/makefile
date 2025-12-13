CXX = g++

CXX_FLAGS = -Wall -Wextra -g -std=c++17

TEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_SOURCE = ExpBackOff_Test

TEST_FILE = ExpBackOff_gtest.cpp

all: test

test: $(TEST_SOURCE)
	./$(TEST_SOURCE)

$(TEST_SOURCE): $(TEST_FILE) ExpBackOff.h
	$(CXX) $(CXX_FLAGS) $(TEST_FILE) $(TEST_FLAGS) -o $(TEST_SOURCE)

clean:
	rm -f $(TEST_SOURCE) *.o
