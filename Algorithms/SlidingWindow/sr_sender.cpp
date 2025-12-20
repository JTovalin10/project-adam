#include "sr_sender.h"

namespace network {

bool SRSender::Send(const std::vector<uint8_t>& data) {
  // TODO: Implement
  // 1. Lock mutex
  // 2. Wait until window has space (window_.size() < window_size_)
  // 3. Create packet with next_seq_num_
  // 4. Insert into window_ map
  // 5. Increment next_seq_num_
  return false;
}

void SRSender::ProcessAck(uint32_t ack_num) {
  // TODO: Implement
  // 1. Lock mutex
  // 2. Find ack_num in window_ map
  // 3. Mark as acknowledged
  // 4. While base_ is acknowledged:
  //    - Remove from window_
  //    - Increment base_
  //    - Notify waiting threads
}

std::vector<Packet> SRSender::CheckTimeouts() {
  // TODO: Implement
  // 1. Lock mutex
  // 2. Get current time
  // 3. For each frame in window_:
  //    - If not acknowledged and timed out:
  //      - Add to retransmit vector
  //      - Reset sent_time
  // 4. Return vector (only timed-out packets, not all!)
  return std::vector<Packet>();
}

bool SRSender::IsInWindow(uint32_t seq_num) const {
  // TODO: Implement
  return false;
}

}  // namespace network
