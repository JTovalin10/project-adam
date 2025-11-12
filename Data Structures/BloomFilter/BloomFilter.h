#ifndef BLOOMFILTER_H_
#define BLOOMFILTER_H_

#include <vector>
#include <functional>
#include <cstdint>
#include <cmath>
#define XXH_INLINE_ALL
#include "xxhash.h"
#include <type_traits>
#include <cstring>
#include <algorithm> 

/** trait to check if the type is supported by the bloom filter */
template<typename T>
constexpr bool is_bloomfilter_supported = std::is_fundamental_v<T> || std::is_same_v<T, std::string> || std::is_same_v<T, const char*>;

/**
 * Custom bloom filter 
 * * REQUIRES:
 * T to be char*, string, or primitive
 * */ 
template <typename T>
class BloomFilter {
  using value_type = T;
  using size_type = std::size_t;
  
  public:
  
  /**
   * Constructs and empty BloomFilter but calculated the requried size and number
   * of hashes from the given input
   *
   * ARGS:
   * expected_elemetns: the client's expected_elements, if more elements are inputed
   * then more false positives may occur
   * acceptable_false_positive_rate: the percentage of false positives that the client
   * finds tolerable
   */
  BloomFilter(size_type expected_elements, double acceptable_false_positive_rate);

  /**
   * copy construtor that copies another BloomFilter
   *
   * ARGS:
   * other: the other BloomFilter that will be copied
   */
  BloomFilter(const BloomFilter& other);

  /**
   * move construtor which steals from another BloomFilter
   *
   * ARGS:
   * other: the BloomFilter that will be stolen from
   *
   * MODIFIES:
   * other
   *
   * EFFECTS:
   * other.m_num_hashes_ = 0
   * other.size_ = 0
   */
  BloomFilter(BloomFilter&& other);

  /** Deconstructs the BloomFilter */
  ~BloomFilter();

  /**
   * Copy assignment operator which replaces the current bloom filter
   * with all fields with another BloomFilter
   *
   * ARGS:
   * other: the other bloomfilter that will be copied
   *
   * MODIFIES:
   * this
   *
   * RETURNS:
   * reference pointer to the newly constructed BloomFilter
   */
  BloomFilter& operator=(const BloomFilter& other) {
    if (this == &other) {
      return *this;
    }
    m_bits_ = other.m_bits_;
    m_num_hashes_ = other.m_num_hashes_;
    size_ = other.size_;
    return *this;
  }

  /**
   * Move assignment operator which will steal from the other bloomfilter
   * and replace the current fields with the other
   *
   * ARGS:
   * other: the bloomfilter that will be stolen from
   *
   * RETURNS:
   * pointer to this
   */
  BloomFilter& operator=(BloomFilter&& other) {
    if (this == &other) {
      return *this;
    }
    m_bits_ = std::move(other.m_bits_);
    m_num_hashes_ = other.m_num_hashes_;
    size_ = other.size_;

    other.m_num_hashes_ = 0;
    other.size_ = 0;
    other.m_bits_.clear();
    return *this;
  }

  /**
   * hashes the given value and adds it into the bloom filter
   * if the index of a hash is already true then nothing happens
   *
   * ARGS:
   * value: the element that will be hashed and added to the filter
   *
   * EFFECTS:
   * m_bits_
   * size_
   */
  void insert(const value_type& value);

  /**
   * hashes the given value and checks the bloom filter at each hash
   *
   * ARGS:
   * value: the element that will be hashed and checked if in the filter
   *
   * RETURNS:
   * true if ALL hashed are true, else false
   */
  bool mayContain(const value_type& value) const;

  /**
   * sets all current elements in the filter back to false
   * keeps the same number of hashes
   */
  void clear();
  
  /**
   * calculated an approximate false positive rate
   *
   * RETURNS:
   * a double which represents the approximate
   */
  double falsePositiveRate() const;

  size_type size() const;
  private:
  std::vector<bool> m_bits_;
  size_type m_num_hashes_;
  size_type size_;
  
  /**
   * sets the hash functions to work with the given value
   *
   * ARGS:
   * vaue: the element that will be hashed
   * hash_a: the first hash to work with hash_b
   * hash_b: the second hash that works with hash_a
   */
  void getHashes(const value_type& value, uint64_t& hash_a, uint64_t& hash_b) const;
};

template<typename T>
BloomFilter<T>::BloomFilter(size_type expected_elements, double acceptable_false_positive_rate) : size_(0) {
  double ln2 = 0.69314718056;
  double ln2_squared = 0.48045301381;
  double top = -(expected_elements * std::log(acceptable_false_positive_rate));
  
  size_type bit_array_size = std::ceil(top / ln2_squared);
  m_bits_.resize(bit_array_size, false); 

  m_num_hashes_ = std::round((static_cast<double>(bit_array_size) / expected_elements) * ln2);
}

template<typename T>
BloomFilter<T>::BloomFilter(const BloomFilter& other) : 
    m_bits_(other.m_bits_), 
    m_num_hashes_(other.m_num_hashes_), 
    size_(other.size_) {}

template<typename T>
BloomFilter<T>::BloomFilter(BloomFilter&& other) : 
    m_bits_(std::move(other.m_bits_)), 
    m_num_hashes_(other.m_num_hashes_),
    size_(other.size_)
{
    other.m_num_hashes_ = 0;
    other.size_ = 0;
    other.m_bits_.clear();
}

template<typename T>
BloomFilter<T>::~BloomFilter() {}

template<typename T>
void BloomFilter<T>::insert(const value_type& value) {
  uint64_t hash_a;
  uint64_t hash_b;
  getHashes(value, hash_a, hash_b);
  for (size_type i = 0; i < m_num_hashes_; i++) {
    size_type index = (hash_a + i * hash_b) % m_bits_.size();
    m_bits_[index] = true;
  }
  size_++;
}

template<typename T>
bool BloomFilter<T>::mayContain(const value_type& value) const {
  if (m_bits_.empty() || m_num_hashes_ == 0) {
    return false;
  }
  uint64_t hash_a;
  uint64_t hash_b;
  getHashes(value, hash_a, hash_b);
  for (size_type i = 0; i < m_num_hashes_; i++) {
    size_type index = (hash_a + i * hash_b) % m_bits_.size();
    bool item = m_bits_[index];
    if (item == false) {
      return false;
    }
  }
  return true;
}

template<typename T>
void BloomFilter<T>::clear() {
  std::fill(m_bits_.begin(), m_bits_.end(), false);
  size_ = 0;
}

template<typename T>
double BloomFilter<T>::falsePositiveRate() const {
  /**
   * the formula to find the approx false positive rate is 
   * p = (1 - e^(-(kn)/m))^k
   * p = approx percentage
   * e = eulers number
   * k = m_num_hashes_
   * n = size_
   * m = m_bits_.size()
   */
  
  if (size_ == 0) {
      return 0.0;
  }

  double k = static_cast<double>(m_num_hashes_);
  double n = static_cast<double>(size_);
  double m = static_cast<double>(m_bits_.size());
  
  double exponent = (-k * n) / m;
  double inner_prob = 1.0 - std::exp(exponent);
  double ans = std::pow(inner_prob, k);
  return ans;
}

template<typename T>
typename BloomFilter<T>::size_type BloomFilter<T>::size() const {
  return size_;
}

template<typename T>
void BloomFilter<T>::getHashes(const value_type& value, uint64_t& hash_a, uint64_t& hash_b) const {
  if constexpr (std::is_same_v<T, std::string>) {
    hash_a = XXH64(value.data(), value.length(), 0);
    hash_b = XXH64(value.data(), value.length(), 1);
  } else if constexpr (std::is_same_v<T, const char*>) {
    hash_a = XXH64(value, strlen(value), 0);
    hash_b = XXH64(value, strlen(value), 1);
  } else if constexpr (std::is_fundamental_v<T>) {
    hash_a = XXH64(&value, sizeof(value), 0);
    hash_b = XXH64(&value, sizeof(value), 1);
  } else {
    static_assert(is_bloomfilter_supported<T>, 
        "value_type is not supported, please only use std::string, const char*, or primitive type");
  }
}

#endif // BLOOMFILTER_H_
