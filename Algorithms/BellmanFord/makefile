CXX = g++
CXX_FLAGS = -Wall -Wextra -g -std=c++17
TEST_FLAGS = -lgtest -lgtest_main -pthread
TEST_SOURCE = BellmanFord_Test
TEST_FILE = BellmanFord_gtest.cpp
IMPL_FILE = BellmanFord.cpp

all: test

test: $(TEST_SOURCE)
	./$(TEST_SOURCE)

$(TEST_SOURCE): $(TEST_FILE) $(IMPL_FILE) BellmanFord.h
	$(CXX) $(CXX_FLAGS) $(TEST_FILE) $(IMPL_FILE) $(TEST_FLAGS) -o $(TEST_SOURCE)

clean:
	rm -f $(TEST_SOURCE) *.o
