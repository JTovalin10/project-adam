CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

GTEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = Trie_Test

TEST_SOURCE = Trie_gtest.cpp

all: test

test: $(TEST_TARGET)
	@echo "Running test..."
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCE) Trie.h
			$(CXX) $(CXXFLAGS) $(TEST_SOURCE) $(GTEST_FLAGS) -o $(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET) *.o