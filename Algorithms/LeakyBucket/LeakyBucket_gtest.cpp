#include "LeakyBucket.h"
#include "gtest/gtest.h"

TEST(LeakyBucketTest, Constructor) { LeakyBucket test(10.0, 1.0); }
