#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <cstddef>
#include <limits>
#include <vector>

struct Edge {
  int from;
  int to;
  int weight;
};

class BellManFord {
 public:
  BellManFord() {}

  std::vector<int> Compute(int start, std::vector<Edge>& edges,
                           std::size_t num_vertices);
};

#endif  // BELLMAN_FORD_H
