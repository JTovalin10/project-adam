#ifndef BLOOMFILTER_H_
#define BLOOMFILTER_H_

#include <vector>
#include <functional>
#include <cstdint>

template <typename T>
class BloomFilter {
  using value_type = T;
	using size_type = std::size_t;
  using std::vector;

  public:
	BloomFilter(size_type size, size_type num_hash_functions);

  BloomFilter(const BloomFilter& other);

  BloomFilter(BloomFilter&& other);

  ~BloomFilter();

  BloomFilter& operator=(const BloomFilter& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    bit_array_ = other.bit_array_;
    num_elements_ = other.num_elements_;
    num_hash_functions = other.num_hash_functions;
    return *this;
  }

  BloomFilter& operator=(BloomFilter&& other) {
    if (this == &other) {
      return *this;
    }
    clear();
    bit_array_ = std::move(other.bit_array_);
    num_hash_functions = other.num_hash_functions;
    num_elements_ = other.num_elements_;

    other.num_elements_ = 0;
    other.num_hash_functions_ = 0;
    return *this;
  }

  void insert(const value_type& value);

  bool mayContain(const value_type& value) const;

  void clear();
  
  // calculated with (1 - (1 -(1/m)^(nk)))^k
  double falsePositiveRate() const;

  size_type size() const;
	private:
  vector<bool> bit_array_;
  size_type num_hash_functions_;
  size_type num_elements_;

  vector<size_type> getHashes(const value_type& value) const;
};

template<typename T>
BloomFilter<T>::BloomFilter(size_type size, size_type num_hash_functions) : bit_array_(size), num_elements_(0), num_hash_functions_(num_hash_functions) {}

template<typename T>
BloomFilter<T>::BloomFilter(const BloomFilter& other) : bit_array_(other.bit_array_), num_elements_(other.num_elements_), num_hash_functions(other.num_hash_functions) {}

template<typename T>
BloomFilter<T>::BloomFilter(BloomFilter&& other) : bit_array_(std::move(other.bit_array_), num_elements_(other.num_elements_), num_hash_functions(other.num_hash_functions) {
    other.num_hash_functions = 0;
    other.num_elements_ = 0;
    }

template<typename T>
BloomFilter<T>::~BloomFilter() {}

template<typename T>
void BloomFilter<T>::insert(const value_type& value) {
  num_elements_++;
}

template<typename T>
bool BloomFilter<T>::mayContain(const value_type& value) const {

}

template<typename T>
void BloomFilter<T>::clear() {
  vector.clear();
}

template<typename T>
double BloomFilter<T>::falsePositiveRate() const {
  double first_part = (1-1/num_elements_) ** (num_elements_ * num_hash_functions)
}

template<typename T>
typename BloomFilter<T>::size_type BloomFilter<T>::size() const {
  return num_elements_;
}

template<typename T>
std::vector<typename BloomFilter<T>::size_type> BloomFilter<T>::getHashes(const value_type& value) const {
  
}

#endif // BLOOMFILTER_H_
:
