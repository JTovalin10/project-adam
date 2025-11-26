#include <chrono>
#include <thread>

#include "TokenBucket.h"
#include "gtest/gtest.h"

TEST(TokenBucketTest, constructor) {
  TokenBucket t(1.0, 1);  // test if it compiles
}

TEST(TokenBucketTest, attempt_to_use_more_than_avaliable) {
  TokenBucket test(10.0, 1);
  ASSERT_FALSE(test.TryConsume(100.0));
  ASSERT_TRUE(test.TryConsume(10.0));
}

TEST(TokenBucketTest, eat_all_then_try_to_use) {
  TokenBucket test(10.0, 1);
  ASSERT_TRUE(test.TryConsume(10.0));
  ASSERT_FALSE(test.TryConsume(1.0));
}

TEST(TokenBucketTest, eat_token_multiple_times) {
  TokenBucket test(10.0, 1);
  for (int i = 0; i < 10; i++) {
    test.TryConsume(1.0);
  }
  ASSERT_FALSE(test.TryConsume(1.0));
}

TEST(TokenBucketTest, refill) {
  TokenBucket test(10.0, 10);

  ASSERT_TRUE(test.TryConsume(10.0));

  std::this_thread::sleep_for(std::chrono::seconds(1));
  ASSERT_TRUE(test.TryConsume(10.0));

  TokenBucket test2(10.0, 2);
  ASSERT_TRUE(test2.TryConsume(10.0));

  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ASSERT_FALSE(test2.TryConsume(100.0));
  ASSERT_TRUE(test2.TryConsume(1.0));
}
