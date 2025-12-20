#include "sr_receiver.h"

namespace network {

uint32_t SRReceiver::ReceivePacket(const Packet& packet) {
  // TODO: Implement
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
  return 0;
}

std::optional<Packet> SRReceiver::GetNextPacket() {
  // TODO: Implement
  // 1. Lock mutex
  // 2. Find consecutive packets starting from rcv_base_
  // 3. If available, remove from buffer and return
  // 4. Otherwise return nullopt
  return std::nullopt;
}

bool SRReceiver::IsInWindow(uint32_t seq_num) const {
  // TODO: Implement
  // Return: seq_num >= rcv_base_ && seq_num < rcv_base_ + window_size_
  return false;
}

}  // namespace network
