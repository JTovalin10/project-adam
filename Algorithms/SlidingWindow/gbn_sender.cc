#include "gbn_sender.h"

namespace network {

GBNSender::GBNSender(size_t window_size, uint32_t timeout_ms)
    : window_size_(window_size),
      timeout_ms_(timeout_ms),
      base_(0),
      next_seq_num_(0) {
  // TODO: Initialize if needed
}

GBNSender::~GBNSender() {
  // TODO: Cleanup if needed
}

bool GBNSender::Send(const std::vector<uint8_t>& data) {
  // TODO: Implement
  // 1. Lock mutex
  // 2. Wait if window is full
  // 3. Create packet with next_seq_num_
  // 4. Create SenderFrame and add to window
  // 5. Increment next_seq_num_
  return false;
}

void GBNSender::ProcessAck(uint32_t ack_num) {
  // TODO: Implement
  // 1. Lock mutex
  // 2. Check if ack_num >= base_ (valid ACK)
  // 3. Calculate how many packets are acknowledged
  // 4. Remove acknowledged packets from window
  // 5. Update base_
  // 6. Notify waiting threads
}

std::vector<Packet> GBNSender::CheckTimeouts() {
  // TODO: Implement
  // 1. Lock mutex
  // 2. Get current time
  // 3. Check if oldest frame timed out
  // 4. If timeout: add ALL frames to retransmit vector
  // 5. Reset sent_time for all frames
  // 6. Return vector of packets to retransmit
  return std::vector<Packet>();
}

uint32_t GBNSender::GetBase() const {
  // TODO: Implement
  return 0;
}

uint32_t GBNSender::GetNextSeqNum() const {
  // TODO: Implement
  return 0;
}

size_t GBNSender::GetWindowUsage() const {
  // TODO: Implement
  // Return: next_seq_num_ - base_
  return 0;
}

bool GBNSender::IsWindowFull() const {
  // TODO: Implement
  // Return: GetWindowUsage() >= window_size_
  return false;
}

}  // namespace network
