#ifndef TOKEN_BUCKET_H_
#define TOKEN_BUCKET_H_

#include <algorithm>
#include <chrono>
#include <mutex>

class TokenBucket {
 public:
  TokenBucket(double capacity, double refill_rate);

  bool TryConsume(double attemped_tokens);

 private:
  double capacity_;
  double tokens_;
  double refill_rate_;  // per second
  std::chrono::steady_clock::time_point last_refill_;
  std::mutex mutex_;

  void Refill();
};

TokenBucket::TokenBucket(double capacity, double refill_rate)
    : capacity_(capacity),
      tokens_(capacity),  // starts full
      refill_rate_(refill_rate),
      last_refill_(std::chrono::steady_clock::now()) {}

bool TokenBucket::TryConsume(double attemped_tokens) {
  std::lock_guard<std::mutex> lock(mutex_);
  // check the same time it has been refilled
  Refill();
  if (tokens_ >= attemped_tokens) {
    tokens_ -= attemped_tokens;
    return true;
  }
  return false;
}

void TokenBucket::Refill() {
  auto now = std::chrono::steady_clock::now();
  auto time_difference =
      std::chrono::duration<double>(now - last_refill_).count();

  tokens_ = std::min(capacity_, tokens_ + (refill_rate_ * time_difference));
  last_refill_ = now;
}

#endif  // TOKEN_BUCKET_H_
