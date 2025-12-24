#include "ThreadPool.h"

#include <cstddef>

WorkStealingThreadPool::WorkStealingThreadPool(std::size_t num_threads) {
  for (std::size_t i{0}; i < num_threads; i++) {
  }
}
