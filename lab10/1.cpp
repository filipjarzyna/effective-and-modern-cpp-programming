#include <iostream>
using namespace std;

// uncomment one of the following lines
//#define  test( value, expected) static_assert(value == expected);
#define  test( value, expected)  cout << boolalpha << (value) << " | " << (expected)<< endl;

class A{
public:
    static const int value_type = 10;
    int size = 0;
};
struct B{
    template <typename T>
    size_t size(T t){
        return sizeof(t);
    }
};


int main(){

    test( has_size< int >::value << endl, false);
    test( has_size< vector<int> >::value, true);
    test( has_size< A >::value ,  false);
    test( has_size< B >::value ,  false);

    test(  has_value_type< int >::value,  false);
    test(  has_value_type< vector<int> >::value, true);
    test(  has_value_type< A >::value,  false);




}
