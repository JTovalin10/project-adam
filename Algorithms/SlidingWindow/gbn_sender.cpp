#include "gbn_sender.h"

#include <chrono>
#include <cstddef>
#include <cstdint>

namespace network {

bool GBNSender::Send(const std::vector<uint8_t>& data) {
  // we have a unique lock as std::condtional_variable requires it to use wait
  std::unique_lock<std::mutex> lock(mtx_);
  // we pass in this into [] so that it has access to all functions
  cv_window_available_.wait(lock, [this]() { return !IsWindowFull(); });
  Packet new_packet(next_seq_num_, data);
  SenderFrame new_frame(new_packet);
  next_seq_num_++;
  return true;
}

void GBNSender::ProcessAck(uint32_t ack_num) {
  std::lock_guard<std::mutex> lock(mtx_);
  if (ack_num >= base_) {
    std::size_t num_ack = ack_num - base_ + 1;
    if (num_ack <= window_.size()) {
      window_.erase(window_.begin(), window_.begin() + num_ack);
      base_ = ack_num + 1;
      cv_window_available_.notify_one();
    }
  }
}

std::vector<Packet> GBNSender::CheckTimeouts() {
  std::lock_guard<std::mutex> lock(mtx_);
  // calculate time difference between base_ time and current time
  auto now = std::chrono::steady_clock::now();
  auto oldest_frame_time = window_.front().sent_time;
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                     now - oldest_frame_time)
                     .count();
  // we only want to retry if the time is in timeout
  if (elapsed >= timeout_ms_) {
    // add them back into the retransmit vector
    std::vector<Packet> packets;
    packets.reserve(window_size_);
    for (auto& frame : window_) {
      packets.push_back(frame.packet);
    }
    return packets;
  }
  // if not then return an empty vector
  return std::vector<Packet>();
}

}  // namespace network
