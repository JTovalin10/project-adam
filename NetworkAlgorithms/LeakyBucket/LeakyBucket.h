#ifndef LEAKYBUCKET_H_
#define LEAKYBUCKET_H_

#include <algorithm>
#include <chrono>
#include <mutex>

class LeakyBucket {
 public:
  /**
   * Constructor for the leaky bucket
   *
   * ARGS:
   * leak_rate: the rate at which the bucket will leak
   * capacity: the max capacity of the bucket
   */
  LeakyBucket(double leak_rate, double capacity);

  /**
   * a check to see if the clients operation can be done based on the leak rate
   * The client provided the cost of the operation which will be checked
   *
   * ARGS:
   * cost: The cost of the clients operation, if the client does not provide one
   * then it defaults to 1.0
   *
   * RETURNS:
   * if the water level is less than or equal to the capacity it returns true.
   * else, it returns false
   */
  bool allow(double cost = 1.0);

 private:
  /**
   * leaks the current level based on the last leak and the client given leak
   * rate. if the water level falls below 0 then it will be set to 0.
   *
   */
  void leak();

  double leak_rate_;  // in seconds
  double capacity_;
  double water_level_;
  std::chrono::steady_clock::time_point last_leak_time_;
  std::mutex mutex_;
};

LeakyBucket::LeakyBucket(double leak_rate, double capacity)
    : leak_rate_(leak_rate),
      capacity_(capacity),
      water_level_(0),
      last_leak_time_(std::chrono::steady_clock::now()) {}

bool LeakyBucket::allow(double cost) {
  std::lock_guard<std::mutex> lock(mutex_);
  leak();
  double attempted_water_level = water_level_ + cost;
  if (attempted_water_level <= capacity_) {
    water_level_ = attempted_water_level;
    return true;
  }
  return false;
}

void LeakyBucket::leak() {
  auto now = std::chrono::steady_clock::now();
  auto time_difference =
      std::chrono::duration<double>(now - last_leak_time_).count();

  double new_count = water_level_ - (time_difference * leak_rate_);
  if (new_count < 0) {
    water_level_ = 0;
  } else {
    water_level_ = new_count;
  }
  last_leak_time_ = now;
}

#endif  // LEAKYBUCKET_H_
