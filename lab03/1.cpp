#include <iostream>
#include <cmath>
using namespace std;
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
	auto fp1 = sqrtn;
  auto fp2 = power;
	auto fp3 = function<decltype(fp1), decltype(fp2)>;
	cout << fp3(2, 10, 3, fp1, fp2) << endl;
	cout << fp3(3, 10, 3, fp1, fp2) << endl;
	return 0;
}
