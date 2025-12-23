#ifndef PACKET_H_
#define PACKET_H_

#include <chrono>
#include <cstdint>
#include <vector>

namespace network {

// Basic packet structure
struct Packet {
  uint32_t seq_num{0};
  std::vector<uint8_t> data;

  Packet() = default;

  Packet(uint32_t seq, const std::vector<uint8_t>& payload)
      : seq_num(seq), data(payload) {}

  // for testing purposes
  bool operator==(const Packet& other) const {
    return seq_num == other.seq_num && data == other.data;
  }

  bool operator!=(const Packet& other) const {
    return seq_num != other.seq_num && data != other.data;
  }
};

// Frame with timing info for sender
struct SenderFrame {
  Packet packet;
  std::chrono::steady_clock::time_point sent_time =
      std::chrono::steady_clock::now();
  bool acknowledged = false;

  explicit SenderFrame(const Packet& pkt) : packet(pkt) {}
};

}  // namespace network

#endif  // PACKET_H_
