#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
class Printer{
private:
  string prefix;
  string sufix;
  ostream& ostr;
public:
  Printer(ostream& s, string prefix, string sufix): ostr(s), prefix(prefix), sufix(sufix) {
  }
  template<typename T>
  void operator()(const T& x) {
    ostr << prefix << x << sufix;
  }
};

int main(){
  auto f = [k = 1]() mutable {
    cout << k++ << " ";
  };

  for(int i = 0; i < 10; ++i) {
    f();
  }

  /// Creates unary functor that takes one argument x (of any type)
  /// and outputs to given stream x surrounded by given prefix na postfix
  /// e.g. in the following  [ x ]
  /// Hint: define function template.
  Printer printer(std::cout,  "[ ", " ] " );
  printer("hello");    // [ hello ]
  std::cout << "\nv = ";
  std::vector<int> v = {1, 2, 3, 4};
  std::for_each(v.begin(), v.end(), printer);  // v = [ 1 ] [ 2 ] [ 3 ] [ 4 ]

  std::ofstream file("myFile.txt");
  Printer filePrinter(file, "- ", "\n");
  filePrinter(5);
  filePrinter("My text");	
	return 0;
}
/** myFile.txt
- 5
- My text
*/

// 1 2 3 4 5 6 7 8 9 10
