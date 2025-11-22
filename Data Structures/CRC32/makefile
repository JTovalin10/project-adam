CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

GTEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = CRC32_Test

TEST_SOURCE = CRC32_gtest.cpp

all: test

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCE) CRC32.h
	$(CXX) $(CXXFLAGS) $(TEST_SOURCE) $(GTEST_FLAGS) -o $(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET) *.o