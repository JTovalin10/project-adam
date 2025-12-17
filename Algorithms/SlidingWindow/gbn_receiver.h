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
  explicit GBNReceiver(size_t window_size);

  // Destructor
  ~GBNReceiver();

  // Process received packet
  // Returns: ACK number to send back to sender
  uint32_t ReceivePacket(const Packet& packet);

  // Get next delivered packet (if available)
  // Returns: packet if available, nullopt otherwise
  std::optional<Packet> GetNextPacket();

  // Get the expected sequence number
  uint32_t GetExpectedSeqNum() const;

 private:
  const size_t window_size_;
  uint32_t expected_seq_num_;

  std::deque<Packet>
      delivered_packets_;  // Packets ready to deliver to application
  mutable std::mutex mtx_;
};

}  // namespace network

#endif  // GBN_RECEIVER_H_
