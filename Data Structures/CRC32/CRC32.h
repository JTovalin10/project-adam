#ifndef CRC32_H_
#define CRC32_H_

#include <array>
#include <cstddef>
#include <cstdint>

class Crc32 {
 public:
  using size_type = std::size_t;
  using crc_table = std::array<uint32_t, 256>;
  Crc32();

  // Compute CRC32 for entire buffer at once
  // returns the "hash"
  uint32_t Compute(const uint8_t* data, size_type length);

  // Incremental interface
  void Reset();
  void Update(const uint8_t* data, size_type length);
  uint32_t Finalize() const;

  bool Valid(const uint8_t* data, size_type length, uint32_t other_crc) const;

 private:
  /**
   * Creates a look up table for the crc, this increases performance but trades
   * of 1kb of memory. Initlalized during compile time.
   */
  void InitializeTable();
  static constexpr int kTableSize = 256;
  static constexpr int kBitsPerByte = 8;
  static constexpr uint8_t kByteMask = 0xFF;
  static constexpr uint32_t kInitialCrc = 0xFFFFFFFF;
  static constexpr uint32_t kPolynomial = 0xEDB88320;  // reversed
  static crc_table table_;
  static bool table_initialized_;
  uint32_t crc_;
};

Crc32::Crc32() {
  if (!table_initialized_) {
    InitializeTable();
  }
  Reset();
}

uint32_t Crc32::Compute(const uint8_t* data, size_t length) {
  Reset();  // we want to calculate from the start
  Update(data, length);
  return Finalize();
}

void Crc32::Reset() { crc_ = kInitialCrc; }

// fills the array of uint8_t array
void Crc32::Update(const uint8_t* data, size_t length) {
  const uint8_t mask = 0xFF;
  for (int i = 0; i < length; i++) {
    // we want to get the 2 LSB from the xor of kPolynomial and data[i]
    const uint8_t index = (crc_ ^ data[i]) & kByteMask;
    // as we already processed 8 bytes we remove it and then xor the
    // precalculated table at index
    uint32_t precalculated = table_[index];
    crc_ = (crc_ >> kBitsPerByte) ^ precalculated;
  }
}

uint32_t Crc32::Finalize() const { return ~crc_; }

void Crc32::InitializeTable() {
  for (int i = 0; i < kTableSize; i++) {
    uint32_t curr = i;
    for (int j = 0; j < kBitsPerByte; j++) {
      // checks if LSB is 1
      if ((curr & 1) != 0) {
        // if LSB is 1 then we xor in order to account
        // for any remainder that comes from right-shifting off 1
        curr = kPolynomial ^ (curr >> 1);
      } else {
        curr = (curr >> 1);
      }
    }
    table_[i] = curr;
  }
  table_initialized_ = true;
}

bool Crc32::Valid(const uint8_t* data, size_t length,
                  uint32_t other_crc) const {
  Crc32 other;
  uint32_t expected = other.Compute(data, length);
  return expected == other_crc;
}

#endif  // CRC32_H_
