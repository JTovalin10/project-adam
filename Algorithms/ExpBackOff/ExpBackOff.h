#ifndef EXPBACKOFF_H_
#define EXPBACKOFF_H_

#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <random>
#include <thread>

class ExponentialBackOff {
 public:
  using size_type = std::size_t;

  ExponentialBackOff() {}

  template <typename Func>
  auto Execute(Func&& operation,
               std::chrono::milliseconds base_delay = DEFAULT_BASE_DELAY,
               std::chrono::seconds max_delay = DEFAULT_MAX_DELAY,
               size_type retries = DEFAULT_MAX_RETRIES)
      -> decltype(operation()) {
    thread_local std::mt19937 rng(std::random_device{}());
    for (size_type attempt = 0; attempt < retries; attempt++) {
      try {
        return operation();
      } catch (const std::exception& e) {
        if (attempt == retries - 1) {
          throw;
        }
      }
      auto exp_delay = base_delay * (1 << attempt);
      if (exp_delay > max_delay) {
        exp_delay = max_delay;
      }
      std::uniform_int_distribution<uint64_t> dist(0, exp_delay.count());
      auto jittered_delay = std::chrono::milliseconds(dist(rng));
      std::this_thread::sleep_for(jittered_delay);
    }
    throw;
  }

 private:
  static constexpr size_type DEFAULT_MAX_RETRIES = 5;
  static constexpr std::chrono::milliseconds DEFAULT_BASE_DELAY =
      std::chrono::milliseconds(500);
  static constexpr std::chrono::seconds DEFAULT_MAX_DELAY =
      std::chrono::seconds(30);
};

#endif  // EXPBACKOFF_H_
