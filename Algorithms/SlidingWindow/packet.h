#ifndef PACKET_H_
#define PACKET_H_

#include <chrono>
#include <cstdint>
#include <vector>

namespace network {

// Basic packet structure
struct Packet {
  uint32_t seq_num;
  std::vector<uint8_t> data;

  Packet(uint32_t seq, const std::vector<uint8_t>& payload);
};

// Frame with timing info for sender
struct SenderFrame {
  Packet packet;
  std::chrono::steady_clock::time_point sent_time;
  bool acknowledged;

  explicit SenderFrame(const Packet& pkt);
};

}  // namespace network

#endif  // PACKET_H_
