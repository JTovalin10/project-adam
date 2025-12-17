#include <gtest/gtest.h>

#include <climits>
#include <limits>

#include "BellmanFord.h"

TEST(BellmanFordTest, SimpleGraph) {
  BellManFord test;
  std::vector<Edge> edges = {{0, 1, 1}, {0, 2, 4}, {1, 2, -3}};

  auto result = test.Compute(0, edges, 2);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 1);
  EXPECT_EQ(result[2], -2);
}

TEST(BellmanFordTest, NegativeCycleDetection) {
  BellManFord test;
  std::vector<Edge> edges = {{0, 1, 1}, {1, 2, -5}, {2, 1, 1}};

  auto result = test.Compute(0, edges, 3);

  EXPECT_EQ(result[0], -1);  // Negative cycle returns -1
}

TEST(BellmanFordTest, Disconnected) {
  BellManFord test;
  std::vector<Edge> edges = {{0, 1, 5}};

  auto result = test.Compute(0, edges, 3);

  EXPECT_EQ(result[0], 0);
  EXPECT_EQ(result[1], 5);
  EXPECT_EQ(result[2], std::numeric_limits<int>::max());  // Unreachable
}
