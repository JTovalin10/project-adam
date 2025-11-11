CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

TEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = RedBlackTree_Test

TEST_SOURCE = RedBlackTree_gtest.cpp

all: test

test: $(TEST_TARGET)
	@echo "Running tests"
	./$(TEST_TARGET)

$(TEST_TARGET):
	$(TEST_SOURCE) RedBlackTree.h $(CXX) $(CXXFLAGS $(TEST_SOURCE) $(TEST_FLAGS) $(TEST_SOURCE)

clean:
	rm -f $(TEST_TARGET) *.o
			