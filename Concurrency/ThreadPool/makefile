CXX = g++

CXX_FLAGS = -Wall -Wextra -g -std=c++17

GTEST_FLAGS = -lgtest -lgtest_main -pthread

# Source files
SOURCES = ThreadPool.cpp ThreadPool_gtest.cpp

# Output executable
TEST_EXECUTABLE = ThreadPool_Test

all: test

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(SOURCES) ThreadPool.h
	$(CXX) $(CXX_FLAGS) $(SOURCES) $(GTEST_FLAGS) -o $(TEST_EXECUTABLE)

clean:
	rm -f $(TEST_EXECUTABLE) *.o