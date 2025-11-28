CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

TESTFLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = LeakyBucket_Test

TEST_SOURCE = LeakyBucket_gtest.cpp

all: test

test: $(TEST_TARGET)
		./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCE) LeakyBucket.h
		$(CXX) $(CXXFLAGS) $(TEST_SOURCE) $(TESTFLAGS) -o $(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET) *.o;
