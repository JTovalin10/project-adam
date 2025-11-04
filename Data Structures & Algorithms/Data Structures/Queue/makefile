CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

GTEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = Queue_Test

TEST_SOURCES = Queue_gtest.cpp

all: test

test: $(TEST_TARGET)
	@echo "Running Tests..."
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCES) Queue.cpp Queue.h
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) $(GTEST_FLAGS) -o $(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET) *.o

.PHONY: all test clean