#include "sr_receiver.h"

#include <mutex>

namespace network {

uint32_t SRReceiver::ReceivePacket(const Packet& packet) {
  // 1. Lock mutex
  // 2. Check if packet is in window
  // 3. If in window:
  //    - Add to buffer_
  //    - While rcv_base_ exists in buffer_:
  //      - Increment rcv_base_
  //    - Return ACK for this packet (packet.seq_num)
  // 4. If already delivered (seq_num < rcv_base_):
  //    - Return ACK again (duplicate)
  // 5. If beyond window:
  //    - Ignore
  std::lock_guard<std::mutex> lock(mtx_);
  uint32_t seq_num{packet.seq_num};
  if (IsInWindow(seq_num)) {
    buffer_[seq_num] = packet;
    while (buffer_.count(seq_num) == 1) {
      rcv_base_++;
    }
    return seq_num;
  } else if (seq_num < rcv_base_) {
    return seq_num;
  } else {
    return (rcv_base_ > 0) ? rcv_base_ - 1 : 0;
  }
}

std::optional<Packet> SRReceiver::GetNextPacket() {
  // 1. Lock mutex
  // 2. Find consecutive packets starting from rcv_base_
  // 3. If available, remove from buffer and return
  // 4. Otherwise return nullopt
  std::lock_guard<std::mutex> lock(mtx_);
  if (buffer_.count(rcv_base_) == 1) {
    Packet packet = buffer_[rcv_base_];
    buffer_.erase(rcv_base_);
    rcv_base_++;
    return packet;
  }
  return std::nullopt;
}

}  // namespace network
