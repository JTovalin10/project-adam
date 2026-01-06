#ifndef SR_SENDER_H_
#define SR_SENDER_H_

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <unordered_map>

#include "packet.h"

namespace network {

class SRSender {
 public:
  // Constructor
  SRSender(size_t window_size, uint32_t timeout_ms)
      : window_size_(window_size), timeout_ms_(timeout_ms) {}

  // Send data (blocks if window is full)
  bool Send(const std::vector<uint8_t>& data);

  // Process individual acknowledgment (not cumulative!)
  void ProcessAck(uint32_t ack_num);

  // Check for timeouts and return packets that need retransmission
  // Only returns individually timed-out packets (not all like GBN)
  std::vector<Packet> CheckTimeouts();

  // Get the base sequence number
  uint32_t GetBase() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return base_;
  }

  // Get the next sequence number
  uint32_t GetNextSeqNum() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return next_seq_num_;
  }

 private:
  struct FrameInfo {
    Packet packet;
    std::chrono::steady_clock::time_point sent_time{
        std::chrono::steady_clock::now()};
    bool acknowledged{false};

    FrameInfo() = default;
    explicit FrameInfo(const Packet& pkt) : packet(pkt) {}
  };

  const size_t window_size_;
  const uint32_t timeout_ms_;

  uint32_t base_{0};
  uint32_t next_seq_num_{0};

  // Map sequence number -> FrameInfo for selective tracking
  std::unordered_map<uint32_t, FrameInfo> window_;
  mutable std::mutex mtx_;
  std::condition_variable cv_window_available_;

  // Helper: check if sequence number is in current window
  bool IsInWindow(uint32_t seq_num) const {
    return window_.count(seq_num) == 1;
  }
};

}  // namespace network

#endif  // SR_SENDER_H_
