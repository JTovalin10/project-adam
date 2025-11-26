#ifndef TOKEN_BUCKET_H_
#define TOKEN_BUCKET_H_

#include <algorithm>
#include <chrono>
#include <mutex>

/**
 * Rate Limiter that allows bursts of requests
 */
class TokenBucket {
 public:
  /**
   * Initalizes the TokenBucket, sets the tokens to the capacity to start with a
   * full bucket
   *
   * REQUIRE:
   * capacity > 0 and refill_rate > 0
   *
   * ARGS:
   * capacity: the max capacity for the tokens
   * refill_rate: the rate that the bucket will be refilled
   */
  TokenBucket(double capacity, double refill_rate);

  /**
   * checks if the bucket has enough tokens to support the attemped_tokens.
   *
   * REQUIRES:
   * attempted_tokens >= 0.0
   *
   * ARGS:
   * attempted_tokens: the client given tokens that they are trying to request
   * from the bucket
   *
   * RETURNS:
   * if tokens_ >= attempted_tokens then returns true. else returns false
   */
  bool TryConsume(double attemped_tokens);

 private:
  double capacity_;
  double tokens_;
  double refill_rate_;  // per second
  std::chrono::steady_clock::time_point last_refill_;
  std::mutex mutex_;

  /**
   * Checks the current time and the last_refill_ time and gets the difference
   * in order to refill the bucket with the given refill rate
   *
   * i.e. refill_rate * time_difference
   */
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
