#include "gbn_receiver.h"

#include <mutex>

namespace network {

uint32_t GBNReceiver::ReceivePacket(const Packet& packet) {
  std::lock_guard<std::mutex> lock(mtx_);

  if (packet.seq_num == expected_seq_num_) {
    delivered_packets_.push_back(packet);
    expected_seq_num_++;
    return expected_seq_num_ - 1;
  }
  // it is out of order
  return (expected_seq_num_ > 0) ? expected_seq_num_ - 1 : 0;
}

std::optional<Packet> GBNReceiver::GetNextPacket() {
  std::lock_guard<std::mutex> lock(mtx_);

  // if our deque is empty
  if (delivered_packets_.empty()) {
    return std::nullopt;
    // if it is not empty
  } else {
    Packet packet = delivered_packets_.front();
    delivered_packets_.pop_front();
    return packet;
  }
}

}  // namespace network
