#include "sr_sender.h"

#include <chrono>
#include <mutex>

namespace network {

bool SRSender::Send(const std::vector<uint8_t>& data) {
  // 1. Lock mutex
  // 2. Wait until window has space (window_.size() < window_size_)
  // 3. Create packet with next_seq_num_
  // 4. Insert into window_ map
  // 5. Increment next_seq_num_
  std::unique_lock<std::mutex> lock(mtx_);
  cv_window_available_.wait(lock,
                            [this]() { return window_.size() < window_size_; });

  Packet new_packet = Packet(next_seq_num_, data);
  FrameInfo frame_info(new_packet);
  window_[next_seq_num_] = frame_info;
  next_seq_num_++;
  return true;
}

void SRSender::ProcessAck(uint32_t ack_num) {
  // 1. Lock mutex
  // 2. Find ack_num in window_ map
  // 3. Mark as acknowledged
  // 4. While base_ is acknowledged:
  //    - Remove from window_
  //    - Increment base_
  //    - Notify waiting threads
  std::lock_guard<std::mutex> lock(mtx_);
  auto iter = window_.find(ack_num);
  if (iter != window_.end()) {
    // .frist = ack_num and .second = packet
    iter->second.acknowledged = true;
    while (window_[base_].acknowledged == true) {
      window_.erase(base_);
      base_++;
    }
    cv_window_available_.notify_one();
  }
}

std::vector<Packet> SRSender::CheckTimeouts() {
  // 1. Lock mutex
  // 2. Get current time
  // 3. For each frame in window_:
  //    - If not acknowledged and timed out:
  //      - Add to retransmit vector
  //      - Reset sent_time
  // 4. Return vector (only timed-out packets, not all!)
  std::lock_guard<std::mutex> lock(mtx_);
  auto now = std::chrono::steady_clock::now();
  std::vector<Packet> timed_out;

  for (auto& [seq_num, frame_info] : window_) {
    if (!frame_info.acknowledged) {
      // we want to check if its timed out in ms
      auto diff_time = now - frame_info.sent_time;
      auto diff_ms =
          std::chrono::duration_cast<std::chrono::milliseconds>(diff_time)
              .count();
      if (diff_ms >= timeout_ms_) {
        frame_info.sent_time = now;
        timed_out.push_back(frame_info.packet);
      }
    }
  }
  return timed_out;
}

}  // namespace network
