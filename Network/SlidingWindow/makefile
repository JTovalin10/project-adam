CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17

TEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_TARGET = sliding_window_test

TEST_SOURCE = SlidingWindow_gtest.cpp

SOURCES = gbn_sender.cpp gbn_receiver.cpp sr_sender.cpp sr_receiver.cpp

all: test

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCE) $(SOURCES)
	$(CXX) $(CXXFLAGS) $(TEST_SOURCE) $(SOURCES) $(TEST_FLAGS) -o $(TEST_TARGET)

clean:
	rm -f $(TEST_TARGET) *.o

.PHONY: all test clean
