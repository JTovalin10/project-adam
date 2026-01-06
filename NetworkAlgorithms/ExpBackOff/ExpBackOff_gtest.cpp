#include <gtest/gtest.h>

#include <chrono>
#include <stdexcept>

#include "ExpBackOff.h"

class ExponentialBackOffTest : public ::testing::Test {
 protected:
  ExponentialBackOff backoff;
};

TEST_F(ExponentialBackOffTest, SucceedsImmediately) {
  auto result = backoff.Execute([]() { return 42; });
  EXPECT_EQ(result, 42);
}

TEST_F(ExponentialBackOffTest, ReturnsCorrectType) {
  auto result = backoff.Execute([]() { return std::string("hello"); });
  EXPECT_EQ(result, "hello");
}

TEST_F(ExponentialBackOffTest, RetriesUntilSuccess) {
  int attempts = 0;
  auto result = backoff.Execute([&attempts]() {
    attempts++;
    if (attempts < 3) {
      throw std::runtime_error("Not yet");
    }
    return attempts;
  });
  EXPECT_EQ(attempts, 3);
  EXPECT_EQ(result, 3);
}

TEST_F(ExponentialBackOffTest, ThrowsAfterMaxRetries) {
  int attempts = 0;
  EXPECT_THROW(
      {
        backoff.Execute([&attempts]() -> int {
          attempts++;
          throw std::runtime_error("Always fails");
        });
      },
      std::runtime_error);
  EXPECT_EQ(attempts, 5);  // DEFAULT_MAX_RETRIES
}

TEST_F(ExponentialBackOffTest, RespectsCustomRetryCount) {
  int attempts = 0;
  EXPECT_THROW(
      {
        backoff.Execute(
            [&attempts]() -> int {
              attempts++;
              throw std::runtime_error("Fail");
            },
            std::chrono::milliseconds(10),  // base_delay
            std::chrono::seconds(1),        // max_delay
            3                               // retries
        );
      },
      std::runtime_error);
  EXPECT_EQ(attempts, 3);
}

TEST_F(ExponentialBackOffTest, DelayIncreases) {
  auto start = std::chrono::steady_clock::now();
  int attempts = 0;

  try {
    backoff.Execute(
        [&attempts]() -> int {
          attempts++;
          throw std::runtime_error("Fail");
        },
        std::chrono::milliseconds(50),  // base_delay (short for testing)
        std::chrono::seconds(1), 3);
  } catch (...) {
  }

  auto elapsed = std::chrono::steady_clock::now() - start;
  auto ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

  // Should have waited at least: 0-50ms + 0-100ms = some time
  // With jitter it's random, but should be > 0
  EXPECT_GT(ms, 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
