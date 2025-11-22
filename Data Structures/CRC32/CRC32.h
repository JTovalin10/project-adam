#ifndef CRC32_H_
#define CRC32_H_

#include <cstddef>
#include <cstdint>

namespace crc {

class Crc32 {
 public:
  Crc32();

  // Compute CRC32 for entire buffer at once
  uint32_t Compute(const uint8_t* data, size_t length);

  // Incremental interface
  void Reset();
  void Update(const uint8_t* data, size_t length);
  uint32_t Finalize() const;

 private:
  static void InitializeTable();
  static uint32_t table_[256];
  static bool table_initialized_;

  uint32_t crc_;
};

}  // namespace crc

#endif  // CRC32_H_