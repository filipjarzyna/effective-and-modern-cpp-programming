#include <iostream>

#ifndef LAB8_RANGE_H
#define LAB8_RANGE_H

template <typename T>
class Range {
private:
    T start;
    T stop;
    T step;

public:
  class iterator {
    T cur;
    T step;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;
    iterator(T current, T step) : cur(current), step(step) {}

    T operator*() const { return cur; }

    iterator &operator++() {
      cur += step;
      return *this;
    }

    iterator operator++(int) {
        iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const iterator& other) const {
        return cur >= other.cur;
    }

    bool operator!=(const iterator& other) const {
        return !(*this == other);
    }
  };

public:
  Range(T stop) : start(0), stop(stop), step(1) {}
  Range(T step, T stop) : start(0), stop(stop), step(1) {}
  Range(T start, T stop, T step) : start(start), stop(stop), step(step) {}
  
  iterator begin() {
      return iterator(start, step);
  }

  iterator end() {
      return iterator(stop, step);
  }

};

template <typename T>
Range<T> make_range(T start, T stop, T step) {
    return Range(start, stop, step);
}

template <typename T>
Range<T> make_range(T stop) {
    return Range(stop);
}

#endif // LAB8_RANGE_H
