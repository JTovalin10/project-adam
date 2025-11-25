#ifndef TOKEN_BUCKET_H_
#define TOKEN_BUCKET_H_

#include <chrono>
#include <mutex>

class TokenBucket {
 public:
  TokenBucket(double capacity, double refill_rate);

  bool TryConsume(double tokens = 1.0);

 private:
  double capacity_;
  double tokens_;
  double refill_rate_;
  std::chrono::steady_clock::time_point last_refill_;
  std::mutex mutex_;

  void Refill();
};

TokenBucket::TokenBucket(double capacity, double refill_rate)
    : capacity_(capacity),
      tokens_(capacity),  // starts full
      refill_rate_(refill_rate),
      last_refill_(std::chrono::steady_clock::now()) {}

bool TokenBucket::TryConsume(double tokens = 1.0) {}

void TokenBucket::Refill() {}

#endif  // TOKEN_BUCKET_H_
