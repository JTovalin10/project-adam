#ifndef GBN_SENDER_H_
#define GBN_SENDER_H_

#include <condition_variable>
#include <deque>
#include <mutex>

#include "packet.h"

namespace network {

class GBNSender {
 public:
  // Constructor
  // window_size: maximum number of unacknowledged packets
  // timeout_ms: milliseconds before retransmission
  GBNSender(size_t window_size, uint32_t timeout_ms)
      : window_size_(window_size),
        timeout_ms_(timeout_ms),
        base_(0),
        next_seq_num_(0) {}

  // Send data (blocks if window is full)
  // Returns true on success
  bool Send(const std::vector<uint8_t>& data);

  // Process cumulative acknowledgment
  // ack_num: all packets up to and including this number are acknowledged
  void ProcessAck(uint32_t ack_num);

  // Check for timeouts and return packets that need retransmission
  // Returns vector of packets to retransmit (empty if no timeouts)
  std::vector<Packet> CheckTimeouts();

  // Get the base sequence number (oldest unacknowledged)
  uint32_t GetBase() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return base_;
  }

  // Get the next sequence number to be assigned
  uint32_t GetNextSeqNum() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return next_seq_num_;
  }

  // Get current window usage (number of packets in flight)
  size_t GetWindowUsage() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return next_seq_num_ - base_;
  }

  // Check if window is full
  bool IsWindowFull() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return (next_seq_num_ - base_) == window_size_;
  }

 private:
  const size_t window_size_;
  const uint32_t timeout_ms_;

  uint32_t base_;          // Oldest unacknowledged sequence number
  uint32_t next_seq_num_;  // Next sequence number to use

  std::deque<SenderFrame> window_;  // Frames currently in flight
  mutable std::mutex mtx_;
  std::condition_variable cv_window_available_;
};

}  // namespace network

#endif  // GBN_SENDER_H_
