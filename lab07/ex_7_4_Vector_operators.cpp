#include <iostream>
#include <type_traits>
using namespace std;


template<int(*operation)(int,int), typename L, typename R>
class LazyEval {
private:
    const L& left;
    const R& right;
public:
    LazyEval(const L& l, const R& r): left(l), right(r) {}

    int operator[](int x) const {
        if constexpr(is_arithmetic<L>()) {
            return operation(left, right[x]);
        } else if constexpr (is_arithmetic<R>()) {
            return operation(left[x], right);
        } else {
            return operation(left[x], right[x]);
        }
    }
};

inline int add(int i, int j) {
    return i + j;
}

inline int multiply(int i, int j) {
    return i * j;
}

inline int subtract(int i, int j) {
    return i - j;
}

template<typename L, typename R>
using AddExpr = LazyEval<add, L, R>;

template<typename L, typename R>
using MultiExpr = LazyEval<multiply, L, R>;

template<typename L, typename R>
using SubtrExpr = LazyEval<subtract, L, R>;

template<typename L, typename R>
AddExpr<L,R> operator+(const L& l, const R& r) {
    return AddExpr<L,R>(l, r);
}

template<typename L, typename R>
MultiExpr<L,R> operator*(const L& l, const R& r) {
    return MultiExpr<L,R>(l, r);
}

template<typename L, typename R>
SubtrExpr<L,R> operator-(const L& l, const R& r) {
    return SubtrExpr<L,R>(l, r);
}

template <int N>
class Vector {
private:
    int data[N];

public:
    Vector() {
        for (int i = 0; i < N; ++i) data[i] = 0;
        cout << " Default constr" << endl;
    }

    Vector(std::initializer_list<int> list) {
        cout << " Init list constr" << endl;
        auto it = list.begin();
        for (int i = 0; i < N && it != list.end(); i++) {
            data[i] = *it++;
        }
    }

    Vector(const Vector& m) {
        std::copy(m.data, m.data + N, data);
        cout << " Copy constr" << endl;
    }

    template <typename Expr>
    Vector(const Expr& expr) {
        cout << " Default constr" << endl;
        for (int i = 0; i < N; ++i) {
            data[i] = expr[i];
        }
    }

    int operator[](int index) const {
        return data[index];
    }

    int& operator[](int index) {
        return data[index];
    }

    friend ostream& operator<<(ostream& out, const Vector& m) {
        for (int i = 0; i < N; i++) {
            out << m.data[i] << (i == N - 1 ? "" : ", ");
        }
        return out;
    }

    template<int(*Op)(int,int), typename L, typename R>
        Vector& operator=(const LazyEval<Op, L, R>& expr) {
            for(int i = 0; i < N; ++i)
                data[i] = expr[i];

            return *this;
        }
};


int main(){
  using V = Vector<10>;
  V v{1,2,3,4,5,6,7,8,9,10};
  V x(v);
  V y{4,4,2,5,3,2,3,4,2,1};

  cout << "Lazy operations :\n";
  // It does not create temporary Vectors
  // It computes resulting vector coordinate by coordinate
  // (evaluating whole expression)
  V z = v + x + 3 * y - 2 * x;
  cout << z << endl;
  
  // Computes only one coordinate of Vector
  int e = (z+x+y)[2];
  cout << " e = " << e << endl;
  V w = v + x + 3 * y - 2 * x;
  cout << w[2] << endl;
  return 0;
}
/**
 Init list constr
 Copy constr
 Init list constr
Lazy operations :
 Default constr
12, 12, 6, 15, 9, 6, 9, 12, 6, 3,
e = 11
 */
