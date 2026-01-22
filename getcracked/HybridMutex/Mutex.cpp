#include "Mutex.h"

#include <atomic>
#include <thread>

Mutex::lock() {
  for (uint32_t i{0}; flag_.load(std::memory_order_relaxed) ||
                      flag_.exchange(1, std::memory_order_acquire);
       ++i) {
    if (i % 8 == 0 && i != 0) {
      std::this_thread::yield();
    }
  }
}

Mutex::unlock() { flag_.store(0, std::memory_order_release); }
