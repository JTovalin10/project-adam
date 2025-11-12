#ifndef BLOOMFILTER_H_
#define BLOOMFILTER_H_

#include <vector>
#include <functional>
#include <cstdint>
#include <cmath>
#include <xxhash.h>
#include <type_traits>
#include <cstring>

template <typename T>
class BloomFilter {
  using value_type = T;
	using size_type = std::size_t;
  using std::vector;

  public:
  
	BloomFilter(size_type expected_elements, double acceptable_false_positive_rate);

  BloomFilter(const BloomFilter& other);

  BloomFilter(BloomFilter&& other);

  ~BloomFilter();

  BloomFilter& operator=(const BloomFilter& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    bit_array_ = other.bit_array_;
    m_num_hashes_ = other.num_hash_functions;
    num_elements_ = other.num_elements_;
    return *this;
  }

  BloomFilter& operator=(BloomFilter&& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    bit_array_ = std::move(other.bit_array_);
    m_num_hashes_ = other.num_hash_functions;
    num_elements_ = other.num_elements_;

    other.m_num_hashes_ = 0;
    other.num_elements_ = 0;
    return *this;
  }

  void insert(const value_type& value);

  bool mayContain(const value_type& value) const;

  void clear();
  
  // calculated with (1 - (1 -(1/m)^(nk)))^k
  double falsePositiveRate() const;

  size_type size() const;
	private:
  vector<bool> m_bits_;
  size_type m_num_hashes_;
  size_type size_;

  void getHashes(const value_type& value, uint64_t& hash_a, uint64_t& hash_b);
};

template<typename T>
BloomFilter<T>::BloomFilter(size_type expected_elements, double acceptable_false_positive_rate) : size_(0) {
  // p = acceptable_false_positive_rate
  double ln2 = 0.69314718056
  double ln2_squared = 0.48045301381
  double top = -(expected_elements * ln(acceptable_false_positive_rate));
  bit_array_size = std::ceil(top / ln2_squared);
  bit_array_(bit_array_size, false);

  // (bit array size / )
  m_num_hashes_ = round((bit_array_size/expected_elements) * ln2);
}

template<typename T>
BloomFilter<T>::BloomFilter(const BloomFilter& other) : bit_array_(other.bit_array_), m_num_hashes_(other.num_hash_functions), size_(other.size_) {}

template<typename T>
BloomFilter<T>::BloomFilter(BloomFilter&& other) : bit_array_(std::move(other.bit_array_), m_num_hashes_(other.num_hash_functions) {
    other.m_num_hashes_ = 0;
    other.size_ = 0;
}

template<typename T>
BloomFilter<T>::~BloomFilter() {}

template<typename T>
void BloomFilter<T>::insert(const value_type& value) {
  uint64_t hash_a;
  uint64_t hash_b;
  getHashes(value, hash_a, hash_b);
  for (int i = 0; i < m_num_hashes_; i++) {
    size_type index = (hash_a + i * hash_b) % bit_array_.size();
    bit_array_[index] = true;
  }
  size_++;
}

template<typename T>
bool BloomFilter<T>::mayContain(const value_type& value) const {
  uint64_t hash_a;
  uint64_t hash_b;
  getHashes(value, hash_a, hash_b);
  for (int i = 0; i < m_num_hashes_; i++) {
    size_type index = (hash_a + i * hash_b) % bit_array_.size();
    bool item = bit_array_[index];
    if (item == false) {
      return false;
    }
  }
  return true;
}

template<typename T>
void BloomFilter<T>::clear() {
  vector.clear();
}

template<typename T>
double BloomFilter<T>::falsePositiveRate() const {
  // the formula to find the approx false positive rate is 
  // p = (1 - e^(-(kn)/m))^k
  // p = approx percentage
  // e = eulers number
  // k = m_num_hashes_
  // n = size_
  // m = bit_array_.size()
  double e = 2.71828;
  double k = statis_cast<double>(m_num_hashes_);
  double k = statis_cast<double>(size_);
  double m = statis_cast<double>(bit_array_.size());
  double exp = pow(e,(-(k * n) / m));
  double ans = pow((1 - exp), k);
  return ans;
}

template<typename T>
typename BloomFilter<T>::size_type BloomFilter<T>::size() const {
  return size_;
}

template<typename T>
void BloomFilter<T>::getHashes(const value_type& value, uint64_t& hash_a, uint64_t& hash_b) {
  if constexpr (std::is_same(value, std::string)) {
    hash_a = xxhash(value.data(), value.size(), 0);
    hash_b = xxhash(value.data(), value.size(), 1);
  } else if constexpr (std::is_same<T, const char*>) {
    hash_a = xxhash(value, strlen(value), 0);
    hash_b = xxhash(value, strlen(value), 1);
  } else if constexpr (std::is_fundamental_v<T>) {
    hash_a = xxhash(&value, sizeof(value), 0);
    hash_b = xxhash(&value, sizeof(value), 1);
  } else {
    static_assert(std::is_fundamental_v<T> || std::is_same<T, const char*>, std::is_same<T, std::string>, 
        "value_type is not supported, please only use std::string, const char*, or primitive type");
  }
}

#endif // BLOOMFILTER_H_

