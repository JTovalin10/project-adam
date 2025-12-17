#include "gbn_receiver.h"

namespace network {

GBNReceiver::GBNReceiver(size_t window_size)
    : window_size_(window_size), expected_seq_num_(0) {
  // TODO: Initialize if needed
}

GBNReceiver::~GBNReceiver() {
  // TODO: Cleanup if needed
}

uint32_t GBNReceiver::ReceivePacket(const Packet& packet) {
  // TODO: Implement
  // 1. Lock mutex
  // 2. Check if packet.seq_num == expected_seq_num_
  // 3. If yes:
  //    - Add to delivered_packets_
  //    - Increment expected_seq_num_
  //    - Return ACK for this packet (expected_seq_num_ - 1)
  // 4. If no (out of order):
  //    - Discard packet
  //    - Return ACK for last in-order packet (expected_seq_num_ - 1)
  return 0;
}

std::optional<Packet> GBNReceiver::GetNextPacket() {
  // TODO: Implement
  // 1. Lock mutex
  // 2. Check if delivered_packets_ is empty
  // 3. If empty: return nullopt
  // 4. If not: pop front packet and return it
  return std::nullopt;
}

uint32_t GBNReceiver::GetExpectedSeqNum() const {
  // TODO: Implement
  return 0;
}

}  // namespace network
