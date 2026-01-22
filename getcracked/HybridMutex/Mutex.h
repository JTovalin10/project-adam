#ifndef UTILS_HYBRID_MUTEX_
#define UTILS_HYBRID_MUTEX_

#include <atomic>
#include <cstdint>

class Mutex {
 public:
  Mutex(const Mutex&) = delete;
  void operator=(const Mutex&) = delete;

  void lock();

  void unlock();

 private:
  std::atomic<std::uint32_t> flag_{0};
};

#endif  // UTILS_HYBRID_MUTEX_
