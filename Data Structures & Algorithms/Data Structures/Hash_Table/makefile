CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

GTEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = Hash_Table_Test

TEST_SOURCE = Hash_Table_gtest.cpp

all: test

test: $(TEST_TARGET)
	@echo "Running test..."
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCE) Hash_Table.h
		$(CXX) $(CXXFLAGS) $(TEST_SOURCE) $(GTEST_FLAGS) -o $(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET) *.o

