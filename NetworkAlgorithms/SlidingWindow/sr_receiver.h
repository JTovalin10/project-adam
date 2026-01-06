#ifndef SR_RECEIVER_H_
#define SR_RECEIVER_H_

#include <deque>
#include <mutex>
#include <optional>
#include <unordered_map>

#include "packet.h"

namespace network {

class SRReceiver {
 public:
  // Constructor
  explicit SRReceiver(size_t window_size) : window_size_(window_size) {}

  // Process received packet
  // Returns: Individual ACK for this specific packet
  uint32_t ReceivePacket(const Packet& packet);

  // Get next in-order delivered packet
  std::optional<Packet> GetNextPacket();

  // Get the base sequence number
  uint32_t GetBase() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return rcv_base_;
  }

  bool IsInWindow(uint32_t seq_num) const {
    return seq_num >= rcv_base_ && seq_num < rcv_base_ + window_size_;
  }

 private:
  const size_t window_size_;
  uint32_t rcv_base_{0};  // Smallest sequence number not yet delivered

  // Buffer for out-of-order packets
  std::deque<Packet> message_queue_;  // for in-order
  std::unordered_map<uint32_t, Packet> buffer_;
  mutable std::mutex mtx_;
};

}  // namespace network

#endif  // SR_RECEIVER_H_
