#ifndef SR_SENDER_H_
#define SR_SENDER_H_

#include <condition_variable>
#include <mutex>
#include <unordered_map>

#include "packet.h"

namespace network {

class SRSender {
 public:
  // Constructor
  SRSender(size_t window_size, uint32_t timeout_ms);

  // Destructor
  ~SRSender();

  // Send data (blocks if window is full)
  bool Send(const std::vector<uint8_t>& data);

  // Process individual acknowledgment (not cumulative!)
  void ProcessAck(uint32_t ack_num);

  // Check for timeouts and return packets that need retransmission
  // Only returns individually timed-out packets (not all like GBN)
  std::vector<Packet> CheckTimeouts();

  // Get the base sequence number
  uint32_t GetBase() const;

  // Get the next sequence number
  uint32_t GetNextSeqNum() const;

 private:
  struct FrameInfo {
    Packet packet;
    std::chrono::steady_clock::time_point sent_time;
    bool acknowledged;

    explicit FrameInfo(const Packet& pkt);
  };

  const size_t window_size_;
  const uint32_t timeout_ms_;

  uint32_t base_;
  uint32_t next_seq_num_;

  // Map sequence number -> FrameInfo for selective tracking
  std::unordered_map<uint32_t, FrameInfo> window_;
  mutable std::mutex mtx_;
  std::condition_variable cv_window_available_;

  // Helper: check if sequence number is in current window
  bool IsInWindow(uint32_t seq_num) const;
};

}  // namespace network

#endif  // SR_SENDER_H_
