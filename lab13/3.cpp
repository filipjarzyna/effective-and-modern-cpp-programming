#include <type_traits>
#include <iostream>
#include <iomanip>

template <int...>
class IntegerList {};

using namespace std;
int main() {

  using listA = 	IntegerList<5, -1, 5, 2, 1>;
  using listB =   IntegerList<1, 4, 6, 9>;
  cout << "List A : " << listA() << endl;
  cout << "List B : " << listB() << endl;

  cout << "A[1] = " << getInt<1, listA>::value << endl;
  cout << "B[3] = " << listB::get(3) << endl;
  static_assert( getInt<1, listA>::value == -1 );
  static_assert( listB::get(3) == 9 );
  static_assert( listB::get(1) == 4 );

  cout << boolalpha;
  cout << "Is A sorted? " << IsSorted<listA>::value << endl;
  cout << "Is B sorted? " << IsSorted<listB>::value << endl;

  using listC = Join<listA, listB>::type;

  cout << "List C : " << listC() << endl;
  cout << Max<listC>::value << endl;
  cout << listC::max() << endl;
  static_assert(listC::max() == 9 );
  static_assert(listA::max() == 5 );

}
