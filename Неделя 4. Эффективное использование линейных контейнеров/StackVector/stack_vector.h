#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0): size(a_size) {
    if(a_size > capacity) {
      throw invalid_argument{"Invalid size"};
    }
    for(auto it = array.begin(), end = it + a_size; it != end; ++it) {
      *it = T();
    }
  }

  T& operator[](size_t index) {
    return array[index];
  }
  const T& operator[](size_t index) const {
    return array[index];
  }

  typename array<T, N>::iterator begin() {
    if(size == 0) return this->end();
    return array.begin();
  }
  typename array<T, N>::iterator end() {
    return array.end();
  }
  typename array<T, N>::const_iterator begin() const {
    if(size == 0) return this->end();
    return array.cbegin();
  }
  typename array<T, N>::const_iterator end() const {
    return array.cend();
  }

  size_t Size() const {
    return size;
  }
  size_t Capacity() const {
    return capacity;
  }

  void PushBack(const T& value) {
    if(size == capacity) throw overflow_error{"Can't insert no more"};
    array[size] = value;
    size += 1;
  }
  T PopBack() {
    if(size == 0) throw underflow_error{"There are no elements"};
    size -= 1;
    return array[size];
  }

private:
  array<T, N> array;
  size_t capacity{N};
  size_t size{0};
};