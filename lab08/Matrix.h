#pragma once

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrix{
private:
	T data[N*M]{};

 public:
    template <typename P, size_t Step>
    class base_iterator {
    private:
        P ptr;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T *;
        using reference = const T &;
        base_iterator(P ptr) : ptr(ptr) {}

        value_type operator*() const { return *ptr; }

        base_iterator &operator++() {
            ptr += Step;
            return *this;
        }

        pointer operator->() const {
            return ptr;
        }

        base_iterator operator++(int) {
            base_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const base_iterator& other) const {
            return ptr >= other.ptr;
        }

        bool operator!=(const base_iterator& other) const {
            return !(*this == other);
        }
    };

    using iterator = base_iterator<T*, 1>;
    using const_iterator = base_iterator<const T*, 1>;
    using row_iterator = iterator;
    using col_iterator = base_iterator<T*, M>;

    iterator begin() {
        return iterator(data);
    }

    iterator end() {
        return iterator(data + N * M);
    }

    iterator begin() const {
        return const_iterator(data);
    }

    iterator end() const {
        return const_iterator(data + N * M);
    }

    row_iterator row_begin(size_t i) {
        return row_iterator(data + (M * (i - 1)));
    }

    row_iterator row_end(size_t i) {
        return row_iterator(data + (M * i));
    }

    col_iterator col_begin(size_t i) {
        return col_iterator(data + (i - 1));
    }

    col_iterator col_end(size_t i) {
        return col_iterator(data + (i - 1) + N * M);
    }

    constexpr size_t numberOfRows() const noexcept { return N; }
	constexpr size_t numberOfColumns() const noexcept { return M; }

  	constexpr Matrix(T initValue = T{}) noexcept {
		std::fill_n(data, N * M, initValue);
  	}

    constexpr Matrix(const std::initializer_list<std::initializer_list<T>> & list) noexcept {
    	T *p = data;
    	for (const auto &row: list) {
    		T *p2 = std::copy_n(row.begin(), min(row.size(), M) , p);
    		std::fill(p2, p += M, T{});
    	}
    	std::fill(p, data + N * M, T{});
    }

	constexpr Matrix(const Matrix & m) noexcept {
		std::copy_n(m.data, N*M, data);
	}
	
	constexpr Matrix & operator=(const Matrix & m) noexcept {
		if(&m != this){
			std::copy_n(m.data, N*M, data);
		}
		return *this;
	}

    constexpr T& operator()(int i, int j) noexcept {
        return data[(i - 1) * M + j - 1];
    }

    constexpr const T& operator()(int i, int j) const noexcept {
        return data[(i - 1) * M + j - 1];
    }

    friend Matrix operator+(const Matrix & a, const Matrix &b) noexcept {
		Matrix r;
		for(int i = 1; i <= N; ++i){
			for(int j = 1; j <= M; ++j){
				r(i,j) = a(i,j) + b(i,j) ;
			}
		}
		return r;
	}

};

template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T,N,M> & m, int width = 10){
	for(int i = 1; i <= m.numberOfRows(); ++i){
		for(int j = 1; j <= m.numberOfColumns(); ++j){
			if(j != 1) 
				cout << " ";
			cout << setw(width) <<  m(i,j) ;
		}
		cout << endl;
	}
}
