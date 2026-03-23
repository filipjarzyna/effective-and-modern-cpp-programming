#include <iostream>
#include <cmath>
using namespace std;

typedef double(*F1)(int, double);
typedef double(*F2)(double, double);
typedef double(*F3)(int, double, double, F1, F2) ;

/// Computes n-th root of x
double sqrtn(int n, double x){
  return exp( log(x) / n); 
}
double power(double  x, double y){
  return exp( log(x) * y);
}
template <typename F, typename G>
double function(int n, double y, double z, F f, G g){
  return (f(n,y) > z) ? g(z, y) : g(y, z);
}
int main(){
  F1 fp1 = sqrtn;
  F2 fp2 = power;
  F3 fp3 = function<F1, F2>;
  cout << fp3(2, 10, 3, fp1, fp2) << endl;
  cout << fp3(3, 10, 3, fp1, fp2) << endl;
  return 0;
}
