#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>

class Matrix {
private:
  // double coefficient;
  int rows;
  int cols;
  double *arr;

private:
  std::pair<int, int>
  getInitDimentions(std::initializer_list<std::initializer_list<double>> l) {
    int r = l.size();
    int c = 0;
    for (auto x : l) {
      c = std::max(c, int(x.size()));
    }
    return {r, c};
  }

public:
  Matrix() : rows(0), cols(0), arr(nullptr) { printf("default constructor\n"); }

  Matrix(int n, int m) : rows(n), cols(m) {
    printf("constructor of %dx%d matrix\n", rows, cols);
    arr = new double[n * m]();
  }

  Matrix(std::initializer_list<std::initializer_list<double>> l) {
    std::tie(rows, cols) = getInitDimentions(l);
    printf("constructor of %dx%d matrix from initializer_list\n", rows, cols);
    if (rows == 0 || cols == 0) {
      *this = Matrix();
      return;
    }

    arr = new double[rows * cols]();
    int i = 0;
    for (const auto &r : l) {
      int j = 0;
      for (const auto c : r) {
        arr[i * cols + j] = c;
        j++;
      }
      i++;
    }
  }

  Matrix(const Matrix &m) {
    printf("copy constructor\n");
    cols = m.cols;
    rows = m.rows;
    arr = new double[cols * rows];
    for (int i = 0; i < cols * rows; i++) {
      arr[i] = m.arr[i];
    }
  }

  ~Matrix() { delete[] arr; }

  Matrix &operator=(const Matrix &m) {
    printf("copy assignment operator\n");
    if (&m == this)
      return *this;
    double *temp = new double[cols * rows];
    cols = m.cols;
    rows = m.rows;
    for (int i = 0; i < cols * rows; i++)
      temp[i] = m.arr[i];

    if (arr != nullptr)
      delete[] arr;
    arr = temp;
    return *this;
  }

  double &operator()(int i, int k) { return arr[(i - 1) * cols + (k - 1)]; }

  Matrix operator-() const {
    Matrix res(cols, rows);
    for (int i = 0; i < cols * rows; i++)
      res.arr[i] = -arr[i];
    return res;
  }

  friend std::ostream &operator<<(std::ostream &o, const Matrix &m) {
    for (int i = 0; i < m.rows; i++) {
      o << "{";
      for (int k = 0; k < m.cols; k++)
        o << m.arr[i * m.cols + k] << (k == m.cols - 1 ? "}\n" : ", ");
    }
    return o;
  }

  Matrix(Matrix &&m) : cols(m.cols), rows(m.rows), arr(m.arr) {
    printf("move constructor\n");
    m.arr = nullptr;
    m.rows = 0;
    m.cols = 0;
  }
};

class MatrixWithLabel : public Matrix {
private:
  std::string label = "A";

public:
  using Matrix::Matrix;
  MatrixWithLabel(std::string label, int rows, int cols)
      : Matrix(rows, cols), label(label) {}

  MatrixWithLabel(std::string label,
                  std::initializer_list<std::initializer_list<double>> l)
      : Matrix(l), label(label) {}

  void setLabel(std::string label) { this->label = label; }

  std::string getLabel() { return label; }
};

using namespace std;
int main() {
  Matrix m1;       // default constructor: N=M=0, data=nullptr
  Matrix m2(3, 4); // N = 3, M = 4, data = N*M doubles set to 0.0
  Matrix m3(
      {{1, 2, 3}, {32, 23, 22}, {3, 234, 23, 44}}); // from initializer_list
  cout << m2(1, 1) << endl; // 0 - the first element in data (we count from 1)
  cout << m3(2, 2) << endl; // 23
  cout << m3;               // prints matrix
  cout << "Copy semantics \n";
  Matrix m4 = m2; // copy constructor that makes deep copy of the matrix m2
  m4 = m3;

  cout << "Move semantics \n";
  Matrix m7 = std::move(m2);
  m4 = -m3;
  cout << "Copy elision \n";
  Matrix m6 = -m4;
  Matrix *pm = new Matrix(-m4);
  cout << m6(2, 1) << endl; // 32

  cout << "Inheritance \n";
  MatrixWithLabel l0("B", 3, 4);
  MatrixWithLabel l1({{1, 2}, {4, 5}});
  l1.setLabel("A");
  MatrixWithLabel l2 = l1;
  MatrixWithLabel l3 = std::move(l1);
  cout << l2.getLabel() << " " << l3.getLabel() << endl;
  cout << l1.getLabel() << endl;
}
