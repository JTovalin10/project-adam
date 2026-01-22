CXX = g++

CXX_FLAGS = -Wall -Wextra -g -std=c++20

TEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_SOURCE = UniquePtr_Test

TEST_FILE = UniquePtr_gtest.cpp

all: $(TEST_SOURCE)
	./$(TEST_SOURCE)

$(TEST_SOURCE): $(TEST_FILE) UniquePtr.h
	$(CXX) $(CXX_FLAGS) $(TEST_FILE) $(TEST_FLAGS) -o $(TEST_SOURCE)

clean:
	rm -f $(TEST_SOURCE) *.o
