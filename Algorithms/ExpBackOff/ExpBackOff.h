#ifndef EXPBACKOFF_H_
#define EXPBACKOFF_H_

#include <chrono>
#include <cmath>
#include <cstddef>
#include <random>
#include <thread>

class ExponentialBackOff {
 public:
  using size_type = std::size_t;

  ExponentialBackOff(size_type max_retries = default_max_retries,
                     size_type base_delay_ms = default_base_delay_ms,
                     size_type max_delay_ms = default_max_delay_ms);

  template <typename Func>
  bool Execute(Func operation) {}

 private:
  size_type max_retries_;
  size_type base_delay_ms_;
  size_type max_delay_ms_;

  static constexpr size_type default_max_retries = 5;
  static constexpr size_type default_base_delay_ms = 100;
  static constexpr size_type default_max_delay_ms = 32000;

  int CalculateDelay(size_type attempt);
};

ExponentialBackOff::ExponentialBackOff(size_type max_retries,
                                       size_type base_delay_ms,
                                       size_type max_delay_ms)
    : max_retries_(max_retries),
      base_delay_ms_(base_delay_ms),
      max_delay_ms_(max_delay_ms) {}

template <typename Func>
bool ExponentialBackOff::Execute(Func operation) {}

int ExponentialBackOff::CalculateDelay(size_type attempt) {}

#endif  // EXPBACKOFF_H_
