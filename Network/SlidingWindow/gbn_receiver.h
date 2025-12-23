#ifndef GBN_RECEIVER_H_
#define GBN_RECEIVER_H_

#include <deque>
#include <mutex>
#include <optional>

#include "packet.h"

namespace network {

class GBNReceiver {
 public:
  // Constructor
  explicit GBNReceiver(size_t window_size) : window_size_(window_size) {}

  // Process received packet
  // Returns: ACK number to send back to sender
  uint32_t ReceivePacket(const Packet& packet);

  // Get next delivered packet (if available)
  // Returns: packet if available, nullopt otherwise
  std::optional<Packet> GetNextPacket();

  // Get the expected sequence number
  uint32_t GetExpectedSeqNum() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return expected_seq_num_;
  }

 private:
  const size_t window_size_;
  uint32_t expected_seq_num_{0};

  std::deque<Packet>
      delivered_packets_;  // Packets ready to deliver to application
  mutable std::mutex mtx_;
};

}  // namespace network

#endif  // GBN_RECEIVER_H_
