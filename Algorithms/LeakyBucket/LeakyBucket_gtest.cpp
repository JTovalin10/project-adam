#include <chrono>
#include <thread>

#include "LeakyBucket.h"
#include "gtest/gtest.h"

class LeakyBucketTest : public ::testing::Test {
 protected:
  void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
  }
};

TEST(LeakyBucketTest, ConstructWithoutError){LeakyBucket test(10.0, 1.0)}

TEST(LeakyBucketTest, EmptyBucketRequest) {
  LeakyBucket test(10.0, 1.0);
  ASSERT_TRUE(test.allow());
}

TEST(LeakyBucketTest, DefaultTokenIsOne) {
  LeakyBucket test(10.0, 2);
  ASSERT_TRUE(test.allow());
  ASSERT_TRUE(test.allow());
  ASSERT_FALSE(test.allow());
}
