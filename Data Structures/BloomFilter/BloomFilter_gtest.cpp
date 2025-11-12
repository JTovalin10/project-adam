#include "gtest/gtest.h"
#include "BloomFilter.h"
#include <vector>
#include <string> // Added for std::string

TEST(BloomFilterTest, constructor) {
  BloomFilter<int> bf(10, 0.1);
  ASSERT_EQ(bf.size(), 0);
  ASSERT_EQ(bf.falsePositiveRate(), 0.0);
}

// dummy class for testing
class MyClass {};

TEST(BloomFilterTest, is_bloomfilter_supported) {
  ASSERT_TRUE(is_bloomfilter_supported<int>); 
  ASSERT_TRUE(is_bloomfilter_supported<double>);
  ASSERT_TRUE(is_bloomfilter_supported<const char*>);
  ASSERT_TRUE(is_bloomfilter_supported<float>);
  ASSERT_TRUE(is_bloomfilter_supported<std::string>);
  ASSERT_TRUE(is_bloomfilter_supported<short>);
  ASSERT_TRUE(is_bloomfilter_supported<long long>);
  ASSERT_TRUE(is_bloomfilter_supported<long>);
  ASSERT_TRUE(is_bloomfilter_supported<signed int>); 
  ASSERT_TRUE(is_bloomfilter_supported<unsigned int>);
  ASSERT_TRUE(is_bloomfilter_supported<wchar_t>);
  ASSERT_TRUE(is_bloomfilter_supported<bool>);
  ASSERT_FALSE(is_bloomfilter_supported<MyClass>);
}

TEST(BloomFilterTest, copy_constructor) {
  BloomFilter<int> bf(10, 0.1);
  bf.insert(10);
  ASSERT_TRUE(bf.mayContain(10));
  ASSERT_EQ(bf.size(), 1);

  BloomFilter<int>bf2 = bf;
  ASSERT_TRUE(bf2.mayContain(10));
  ASSERT_EQ(bf2.size(), 1);
}

TEST(BloomFilterTest, move_constructor) {
  BloomFilter<int> bf(10, 0.1);
  bf.insert(10);

  BloomFilter<int> bf2 = std::move(bf);
  ASSERT_TRUE(bf2.mayContain(10));
  ASSERT_EQ(bf2.size(), 1);
  
  ASSERT_EQ(bf.size(), 0);
  ASSERT_FALSE(bf.mayContain(10)); // Corrected: check moved-from object
}

TEST(BloomFilterTest, copy_assignment_operator) {
  BloomFilter<int> bf(10, 0.1);
  bf.insert(10);
  bf.insert(1);

  BloomFilter<int> bf2(10, 0.1);
  bf2.insert(20);

  bf2 = bf;
  ASSERT_FALSE(bf2.mayContain(20));
  ASSERT_TRUE(bf2.mayContain(10));
  ASSERT_TRUE(bf2.mayContain(1));
  ASSERT_EQ(bf2.size(), 2);
}

TEST(BloomFilterTest, move_assignment_operator) {
  BloomFilter<int> bf(10, 0.1);
  bf.insert(10);
  bf.insert(1);

  BloomFilter<int> bf2(10, 0.1);
  bf2.insert(20);

  bf2 = std::move(bf);
  ASSERT_FALSE(bf2.mayContain(20));
  ASSERT_TRUE(bf2.mayContain(10));
  ASSERT_TRUE(bf2.mayContain(1));

  ASSERT_EQ(bf.size(), 0);
  ASSERT_FALSE(bf.mayContain(10)); // Corrected: check moved-from object
  ASSERT_FALSE(bf.mayContain(1));
}

TEST(BloomFilterTest, insert) {
  BloomFilter<int> bf(10, 0.1);
  bf.insert(1);
  ASSERT_TRUE(bf.mayContain(1));
  ASSERT_EQ(bf.size(), 1);
  ASSERT_FALSE(bf.mayContain(2));
}

TEST(BloomFilterTest, mayContain) {
  BloomFilter<int> bf(10, 0.1);
  bf.insert(1);

  ASSERT_TRUE(bf.mayContain(1));
  ASSERT_FALSE(bf.mayContain(2));
  ASSERT_FALSE(bf.mayContain(0));
}

TEST(BloomFilterTest, clear) {
  BloomFilter<int> bf(100, 0.1);
  for (int i = 0; i < 10; i++) {
    bf.insert(i);
  }
  bf.clear();
  ASSERT_EQ(bf.size(), 0);
  ASSERT_EQ(bf.falsePositiveRate(), 0.0);
  ASSERT_FALSE(bf.mayContain(0));
  ASSERT_FALSE(bf.mayContain(1));
  ASSERT_FALSE(bf.mayContain(2));
  ASSERT_FALSE(bf.mayContain(3));
  ASSERT_FALSE(bf.mayContain(4));
  ASSERT_FALSE(bf.mayContain(5));
  ASSERT_FALSE(bf.mayContain(6));
  ASSERT_FALSE(bf.mayContain(7));
  ASSERT_FALSE(bf.mayContain(8));
  ASSERT_FALSE(bf.mayContain(9));
}

TEST(BloomFilterTest, false_positive_rate) {
  BloomFilter<int> filter10(10, 0.1);
  for (int i = 0; i < 10; ++i) {
    filter10.insert(i);
  }
  double rate_10 = filter10.falsePositiveRate();
  double expected_rate = 0.1;
  double margin = 0.005; // 0.5% margin of error
  
  EXPECT_NEAR(rate_10, expected_rate, margin);

  BloomFilter<int> filter20(20, 0.1);
  
  for (int i = 0; i < 20; ++i) {
    filter20.insert(i);
  }
  double rate_20 = filter20.falsePositiveRate();
  EXPECT_NEAR(rate_20, expected_rate, margin);
}

TEST(BloomFilterTest, size) {
  BloomFilter<int> bf(100, 0.01);
  for (int i = 0; i < 10; i++) {
    bf.insert(i);
  }
  ASSERT_EQ(bf.size(), 10); // Corrected: size is 10, not 100
}