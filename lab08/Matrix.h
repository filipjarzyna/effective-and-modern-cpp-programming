#pragma once

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrix{

	T data[N*M];

 public:
    size_t numberOfRows() { return N; }
	size_t numberOfColumns() { return M; }

  	Matrix(T initValue = T{}){
		std::fill_n(data, N * M, initValue);
  	}

    Matrix(const std::initializer_list<std::initializer_list<T>> & list){
    	T *p = data;
    	for (const auto &row: list) {
    		T *p2 = std::copy_n(row.begin(), min(row.size(), M) , p);
    		std::fill(p2, p += M, T{});
    	}
    	std::fill(p, data + N * M, T{});
    }

	Matrix(const Matrix & m){
		std::copy_n(m.data, N*M, data);
	}
	
	Matrix & operator= (const Matrix & m){
		if(&m != this){
			std::copy_n(m.data, N*M, data);
		}
		return *this;
	}

	T& operator()(int i, int j) {
	   return data[(i-1)*M+j-1];
	}

    friend Matrix operator+( Matrix & a, Matrix &b){
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
void printMatrix(Matrix<T,N,M> & m, int width = 10){
	for(int i = 1; i <= m.numberOfRows(); ++i){
		for(int j = 1; j <= m.numberOfColumns(); ++j){
			if(j != 1) 
				cout << " ";
			cout << setw(width) <<  m(i,j) ;
		}
		cout << endl;
	}
}
