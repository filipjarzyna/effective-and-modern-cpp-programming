#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

template <typename T, size_t N>
class Vector{
    T data[N]{};

public:
    typedef T value_type;
    typedef std::size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    Vector() = default;

    Vector(const Vector & v) {
        for(size_type i = 0; i < N; i++)
            data[i] = v[i];
    }

    Vector &operator=(const Vector & m) {
        if(this == &m)
            return *this;

        for(size_type i = 0; i < N; i++)
            data[i] = m[i];

        return *this;
    }

    Vector(const std::initializer_list<T> &list) {
        assert(list.size() == N);
        size_type i = 0;
        for(auto& k: list)
            data[i++] = k;
    }

    Vector(const Vector<T, 0>& v) {
        assert(N == v.size());
        for(size_type i = 0; i < N; i++)
            data[i] = v[i];
    }

    friend Vector operator+(const Vector &u, const Vector<T, 0> &v) {
        assert(v.size() == N);
        Vector res;
        for (size_type i = 0; i < N; ++i)
            res.data[i] = u[i] + v[i];
        return res;
    }

    template<typename S, size_t M>
    Vector(const Vector<S, M>& v) {
        assert(M == N);
        for(size_t i = 0; i < N; i++)
            data[i] = static_cast<T>(v[i]);
    }

    friend Vector operator+ (const  Vector & u, const Vector & v ) {
        Vector res;
        for(size_type i = 0; i < u.size(); i++)
            res.data[i] = u[i] + v[i];
        return res;
    }

    constexpr size_type size() const {
        return N;
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
        for( auto elem: v.data )
            out << elem << " ";
        return out;
    }
};

#endif //STATIC_VECTOR_H
