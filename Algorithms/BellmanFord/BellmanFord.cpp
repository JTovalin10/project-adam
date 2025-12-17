#include "BellmanFord.h"

#include <cstddef>
#include <iterator>
#include <limits>

std::vector<int> BellManFord::Compute(int start, std::vector<Edge>& edges,
                                      std::size_t num_vertices) {
  const int limit = std::numeric_limits<int>::max();
  std::vector<int> result(num_vertices, limit);
  result[start] = 0;

  for (size_t i = 0; i < num_vertices - 1; i++) {
    for (const auto edge : edges) {
      if (result[edge.from] != limit &&
          result[edge.from] + edge.weight < result[edge.to]) {
        result[edge.to] = result[edge.from] + edge.weight;
      }
    }
  }

  for (const auto edge : edges) {
    if (result[edge.from] != limit &&
        result[edge.from] + edge.weight < result[edge.to]) {
      return std::vector<int>(1, -1);
    }
  }
  return result;
}
