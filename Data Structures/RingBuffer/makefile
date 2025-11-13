CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

TEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = RingBuffer_Test

TEST_SOURCE = RingBuffer_gtest.cpp

all: test

test: $(TEST_TARGET)
		@echo "Running tests..."
		./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCE) RingBuffer.h
		$(CXX) $(CXXFLAGS) $(TEST_SOURCE) $(TEST_FLAGS) -o $(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET) *.o

