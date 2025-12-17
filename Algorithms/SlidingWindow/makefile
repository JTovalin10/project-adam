CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -g

# All source files
SRCS = src/packet.cc src/gbn_sender.cc src/gbn_receiver.cc src/sr_sender.cc src/sr_receiver.cc

# All test files
TESTS = test/packet_test.cc test/gbn_test.cc test/sr_test.cc

# Output
TEST_EXEC = run_tests

all: $(TEST_EXEC)

$(TEST_EXEC): $(SRCS) $(TESTS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(TESTS) -lgtest -lgtest_main -o $(TEST_EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(TEST_EXEC)
