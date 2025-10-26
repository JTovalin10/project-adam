# Define the C++ compiler to use
CXX = g++

# Compiler flags
# -Wall: turn on all warnings
# -Wextra: turn on extra warnings
# -g: include debugging information
# -std=c++17: enforce C++17 standard
CXXFLAGS = -Wall -Wextra -g -std=c++17

# Google Test paths (on macOS with Homebrew)
GTEST_PREFIX = /opt/homebrew/opt/googletest
GTEST_INCLUDE = $(GTEST_PREFIX)/include
GTEST_LIB = $(GTEST_PREFIX)/lib
# -lgtest_main automatically provides main() for running tests
GTEST_FLAGS = -I$(GTEST_INCLUDE) -L$(GTEST_LIB) -lgtest -lgtest_main -pthread

# Define the name of the test executable
TEST_TARGET = Vector_test

# Test source file
TEST_SOURCES = Vector_gtest.cpp

# Default target - builds the test
all: test

# Build and run the test
test: $(TEST_TARGET)
	@echo "Running tests..."
	./$(TEST_TARGET)

# Build the test executable
# This compiles the test file and links it with gtest and our Vector implementation
$(TEST_TARGET): $(TEST_SOURCES) Vector.cpp Vector.h
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) $(GTEST_FLAGS) -o $(TEST_TARGET)

# Clean up generated files
clean:
	rm -f $(TEST_TARGET) *.o

# Show this help message
help:
	@echo "Available targets:"
	@echo "  make test    - Build and run tests"
	@echo "  make clean   - Remove generated files"
	@echo "  make help    - Show this message"