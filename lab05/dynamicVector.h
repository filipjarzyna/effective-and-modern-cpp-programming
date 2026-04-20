#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <cstddef>
#include <locale>
#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

#include "staticVector.h"

template <typename T>
class Vector<T, 0> {
    std::unique_ptr<T[]> data;
    size_t numOfElem = 0;

public:
    typedef T value_type;
    typedef size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    Vector() = default;
    Vector(size_t size):
        data(std::make_unique<value_type[]>(size)),
        numOfElem(size) {}

    Vector(const Vector & v) {
        data = std::make_unique<value_type[]>(v.size());
        numOfElem = v.size();
        for(size_type i = 0; i < size(); i++)
            data[i] = v[i];
    }

    Vector &operator=(const Vector & m) {
        if(this == &m)
            return *this;

        numOfElem = m.numOfElem;
        data = std::make_unique<value_type[]>(numOfElem);
        for(size_type i = 0; i < numOfElem; i++)
            data[i] = m[i];

        return *this;
    }

    Vector(const std::initializer_list<T> &list) {
        numOfElem = list.size();
        data = std::make_unique<value_type[]>(numOfElem);
        size_type i = 0;
        for(auto& k: list)
            data[i++] = k;
    }

    template<size_t N>
    Vector(Vector<T, N> v) : numOfElem(v.size()) {
        data = std::make_unique<T[]>(N);
        for(size_t i = 0; i < N; ++i)
            data[i] = v[i];
    }

    friend Vector operator+ (const Vector &u, const Vector& v) {
        assert(u.size() == v.size());
        Vector res(u.size());
        for(size_type i = 0; i < u.size(); i++)
            res.data[i] = u[i] + v[i];
        return res;
    }

    template<size_t N>
    friend Vector operator+(const Vector <T, 0> &u, const Vector<T, N> &v) {
        assert(u.size() == N);
        Vector res(u.size());
        for (size_type i = 0; i < N; ++i)
            res.data[i] = u[i] + v[i];
        return res;
    }

    constexpr size_type size() const {
        return numOfElem;
    }

    const_reference get(size_type index) const {
        return data[index];
    }

    void set(size_type index, const_reference value) {
        data[index] = value;
    }

    reference operator[](size_type index){
        return data[index];
    }
    const_reference operator[](size_type index) const{
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
        for(size_type i = 0; i < v.size(); i++)
            out << v[i] << " ";
        return out;
    }

    void resize(size_type newSize) {
        auto newData = std::make_unique<value_type[]>(newSize);
        size_type numToCopy = (newSize < numOfElem) ? newSize : numOfElem;
        for(size_type i = 0; i < numToCopy; i++)
            newData[i] = data[i];
        data = std::move(newData);
        numOfElem = newSize;
    }
};

#endif //DYNAMIC_VECTOR_H
