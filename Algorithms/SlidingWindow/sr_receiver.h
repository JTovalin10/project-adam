#ifndef SR_RECEIVER_H_
#define SR_RECEIVER_H_

#include <mutex>
#include <optional>
#include <unordered_map>

#include "packet.h"

namespace network {

class SRReceiver {
 public:
  // Constructor
  explicit SRReceiver(size_t window_size);

  // Destructor
  ~SRReceiver();

  // Process received packet
  // Returns: Individual ACK for this specific packet
  uint32_t ReceivePacket(const Packet& packet);

  // Get next in-order delivered packet
  std::optional<Packet> GetNextPacket();

  // Get the base sequence number
  uint32_t GetBase() const;

 private:
  const size_t window_size_;
  uint32_t rcv_base_;  // Smallest sequence number not yet delivered

  // Buffer for out-of-order packets
  std::unordered_map<uint32_t, Packet> buffer_;
  mutable std::mutex mtx_;

  // Helper: check if sequence number is in current window
  bool IsInWindow(uint32_t seq_num) const;
};

}  // namespace network

#endif  // SR_RECEIVER_H_
