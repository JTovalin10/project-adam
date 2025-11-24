#ifndef CRC32_H_
#define CRC32_H_

#include <cstddef>
#include <cstdint>

namespace crc {

class Crc32 {
 public:
  using size_type = size_t;
  Crc32();

  // Compute CRC32 for entire buffer at once
  // returns the "hash"
  uint32_t Compute(const uint8_t* data, size_t length);

  // Incremental interface
  void Reset();
  void Update(const uint8_t* data, size_t length);
  uint32_t Finalize() const;

 private:

  /**
   * Creates a look up table for the crc, this increases performance but trades
   * of 1kb of memory. Initlalized during compile time.
   */
  constexpr void InitializeTable();
  static uint32_t table_[256];
  static bool table_initialized_;
  const uint32_t polynomial_ = 0xEDB88320 // reversed

  uint32_t crc_;
};

}  // namespace crc

Crc32::Crc32() {
  if (!table_initialized_) {
    InitializeTable();
  }
  Reset();
}

uint32_t Crc32::Compute(const uint8_t* data, size_type length) {

}

void Crc32::Reset() {
  crc_ = 0xFFFFFFF;
}

// fills the array of uint8_t array
void Crc32::Update(const uint8_t* data, size_type length) {

}

uint32_t Crc32::Finalize() const {

}

constexpr void Crc32::InitializeTable() {
  int table_size = 256;
  int bits_per_byte = 8;
  for (int i = 0; i < table_size; i++) {
    int c = i;
    for (int j = 0; j < bits_per_byte; j++) {
      // checks if LSB is 1
      if (c & 1) {
        c = polynomial_ ^ (c >> 1);
      } else {
        c = (c >> 1);
      }
    }
    table_[i] = c;
  }
  table_initialized_ = true;
}

#endif  // CRC32_H_
