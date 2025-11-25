#include "TokenBucket.h"
#include "gtest/gtest.h"

TEST(TokenBucketTest, constructor) {
  TokenBucket(1.0, 1);  // test if it compiles
}
