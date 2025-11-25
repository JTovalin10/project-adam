#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "CRC32.h"

// Test basic construction
TEST(Crc32Test, Constructor) {
  Crc32 crc;
  // Should not crash
}

// Test empty data
TEST(Crc32Test, EmptyData) {
  Crc32 crc;
  const uint8_t* empty = nullptr;
  uint32_t result = crc.Compute(empty, 0);
  // CRC of empty data should be the inverted initial value
  EXPECT_EQ(result, 0x00000000);
}

// Test single byte
TEST(Crc32Test, SingleByte) {
  Crc32 crc;
  uint8_t data[] = {0x00};
  uint32_t result = crc.Compute(data, 1);
  EXPECT_NE(result, 0);
}

// Test known CRC values (standard test vector)
TEST(Crc32Test, KnownValue_123456789) {
  Crc32 crc;
  const char* test_string = "123456789";
  uint8_t* data = reinterpret_cast<uint8_t*>(const_cast<char*>(test_string));
  uint32_t result = crc.Compute(data, 9);
  // Standard CRC32 of "123456789" is 0xCBF43926
  EXPECT_EQ(result, 0xCBF43926);
}

// Test another known value
TEST(Crc32Test, KnownValue_Hello) {
  Crc32 crc;
  const char* test_string = "Hello";
  uint8_t* data = reinterpret_cast<uint8_t*>(const_cast<char*>(test_string));
  uint32_t result = crc.Compute(data, 5);
  EXPECT_NE(result, 0);
}

// Test incremental computation matches one-shot computation
TEST(Crc32Test, IncrementalMatchesOneShot) {
  Crc32 crc1;
  Crc32 crc2;
  const char* test_string = "The quick brown fox";
  uint8_t* data = reinterpret_cast<uint8_t*>(const_cast<char*>(test_string));
  size_t len = strlen(test_string);

  // One-shot computation
  uint32_t oneshot = crc1.Compute(data, len);

  // Incremental computation
  crc2.Reset();
  for (size_t i = 0; i < len; i++) {
    crc2.Update(&data[i], 1);
  }
  uint32_t incremental = crc2.Finalize();

  EXPECT_EQ(oneshot, incremental);
}

// Test incremental in chunks
TEST(Crc32Test, IncrementalChunks) {
  Crc32 crc1;
  Crc32 crc2;
  const char* part1 = "Hello ";
  const char* part2 = "World";
  const char* full = "Hello World";

  // Full computation
  uint32_t full_crc =
      crc1.Compute(reinterpret_cast<const uint8_t*>(full), strlen(full));

  // Chunked computation
  crc2.Reset();
  crc2.Update(reinterpret_cast<const uint8_t*>(part1), strlen(part1));
  crc2.Update(reinterpret_cast<const uint8_t*>(part2), strlen(part2));
  uint32_t chunked_crc = crc2.Finalize();

  EXPECT_EQ(full_crc, chunked_crc);
}

// Test Reset functionality
TEST(Crc32Test, Reset) {
  Crc32 crc;
  const char* test_string = "test";
  uint8_t* data = reinterpret_cast<uint8_t*>(const_cast<char*>(test_string));

  uint32_t first = crc.Compute(data, 4);
  crc.Reset();
  crc.Update(data, 4);
  uint32_t second = crc.Finalize();

  EXPECT_EQ(first, second);
}

// Test different data produces different CRCs
TEST(Crc32Test, DifferentDataDifferentCRC) {
  Crc32 crc;
  const char* data1 = "test1";
  const char* data2 = "test2";

  uint32_t crc1 =
      crc.Compute(reinterpret_cast<const uint8_t*>(data1), strlen(data1));
  uint32_t crc2 =
      crc.Compute(reinterpret_cast<const uint8_t*>(data2), strlen(data2));

  EXPECT_NE(crc1, crc2);
}

// Test Valid function with correct CRC
TEST(Crc32Test, ValidWithCorrectCRC) {
  Crc32 crc;
  const char* test_string = "validation test";
  uint8_t* data = reinterpret_cast<uint8_t*>(const_cast<char*>(test_string));
  size_t len = strlen(test_string);

  uint32_t computed_crc = crc.Compute(data, len);
  EXPECT_TRUE(crc.Valid(data, len, computed_crc));
}

// Test Valid function with incorrect CRC
TEST(Crc32Test, ValidWithIncorrectCRC) {
  Crc32 crc;
  const char* test_string = "validation test";
  uint8_t* data = reinterpret_cast<uint8_t*>(const_cast<char*>(test_string));
  size_t len = strlen(test_string);

  uint32_t computed_crc = crc.Compute(data, len);
  EXPECT_FALSE(crc.Valid(data, len, computed_crc + 1));
}

// Test all zeros
TEST(Crc32Test, AllZeros) {
  Crc32 crc;
  std::vector<uint8_t> zeros(100, 0);
  uint32_t result = crc.Compute(zeros.data(), zeros.size());
  EXPECT_NE(result, 0);
}

// Test all ones
TEST(Crc32Test, AllOnes) {
  Crc32 crc;
  std::vector<uint8_t> ones(100, 0xFF);
  uint32_t result = crc.Compute(ones.data(), ones.size());
  EXPECT_NE(result, 0);
}

// Test multiple instances use same table
TEST(Crc32Test, MultipleInstances) {
  const char* test_string = "shared table test";
  uint8_t* data = reinterpret_cast<uint8_t*>(const_cast<char*>(test_string));
  size_t len = strlen(test_string);

  Crc32 crc1;
  Crc32 crc2;
  Crc32 crc3;

  uint32_t result1 = crc1.Compute(data, len);
  uint32_t result2 = crc2.Compute(data, len);
  uint32_t result3 = crc3.Compute(data, len);

  EXPECT_EQ(result1, result2);
  EXPECT_EQ(result2, result3);
}

// Test large data
TEST(Crc32Test, LargeData) {
  Crc32 crc;
  std::vector<uint8_t> large_data(10000);
  for (size_t i = 0; i < large_data.size(); i++) {
    large_data[i] = static_cast<uint8_t>(i % 256);
  }

  uint32_t result = crc.Compute(large_data.data(), large_data.size());
  EXPECT_NE(result, 0);

  // Verify it's repeatable
  uint32_t result2 = crc.Compute(large_data.data(), large_data.size());
  EXPECT_EQ(result, result2);
}

// Test processing text word by word (real-world usage pattern)
TEST(Crc32Test, WordByWordProcessing) {
  Crc32 crc;
  const char* text = "all, dogs. go/ to? heaven!";

  // Split into words and process incrementally
  std::vector<std::string> words = {"all,", " dogs.", " go/", " to?",
                                    " heaven!"};

  crc.Reset();
  for (const auto& word : words) {
    crc.Update(reinterpret_cast<const uint8_t*>(word.c_str()), word.length());
  }
  uint32_t incremental_crc = crc.Finalize();

  // Compute full text at once for comparison
  Crc32 crc2;
  uint32_t full_crc =
      crc2.Compute(reinterpret_cast<const uint8_t*>(text), strlen(text));

  // They should match
  EXPECT_EQ(incremental_crc, full_crc);

  // Validate using the Valid function
  EXPECT_TRUE(crc2.Valid(reinterpret_cast<const uint8_t*>(text), strlen(text),
                         incremental_crc));

  // Validate with wrong CRC should fail
  EXPECT_FALSE(crc2.Valid(reinterpret_cast<const uint8_t*>(text), strlen(text),
                          incremental_crc + 1));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
