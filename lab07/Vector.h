
#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>

#include "vector_traits.h"
#include "vector_policies.h"

template <typename T, size_t N,
          template<typename, size_t> class P = SafePolicy>
class Vector {
  T data[N];

 public:
  typedef T value_type;
  typedef std::size_t  size_type;
  typedef T* pointer;
  typedef T& reference;
  typedef typename vector_traits<T>::param_type param_type;
  typedef typename vector_traits<T>::scalar_type scalar_type;
  using policy = P<T,N>;

  Vector() {
      policy::init(data);
  };
  Vector(const Vector & v) = default;
  Vector &operator=(const Vector & m) = default;

  Vector(const std::initializer_list<T> &list){
    policy::check(list.size() - 1);
	std::copy(list.begin(), list.end(), data);
  }
  size_type size() const {
	return N;
  }

  param_type get(size_type index) const {
    policy::check(index);
	return data[index];
  }

  void set(size_type index, param_type value) {
    policy::check(index);
	data[index] = value;
  }

  friend Vector operator* (scalar_type x, const Vector & v ){
	Vector result;
	for(int i=0; i < v.size(); ++i){
	  result.set(i, vector_traits<T>::multiply(x, v.get(i)));
	}
	return result;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
	for(int i=0; i < v.size(); ++i){
	  out << v.get(i) << " ";
	}
	return out;
  }

  friend std::istream &operator>>(std::istream &in, Vector & v) {
	Vector::value_type value;
	for(int i=0; i < v.size(); ++i){
	  in >> value;
	  if(in)
		v.set(i, value);
	}
	return in;
  }

};

#endif // LAB8_VECTOR_H
