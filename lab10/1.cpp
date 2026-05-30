#include <iostream>
#include <type_traits>
#include <vector>
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



// detect .size()
template<typename T, typename = void>
struct has_size : std::false_type {};

template<typename T>
struct has_size<T, void_t<decltype(std::declval<T>().size())>> : std::true_type {};

// detect value_type
template<typename T, typename = void>
struct has_value_type : std::false_type {};

template<typename T>
struct has_value_type<T, void_t<typename T::value_type>> : std::true_type {};

namespace v {
    template<typename T>
    typename enable_if<has_size<T>::value && has_value_type<T>::value, size_t>::type
    getSize(const T & x) {
        return x.size() * sizeof(typename T::value_type);
    }

    template<typename T>
    typename enable_if<!has_size<T>::value, size_t>::type
    getSize(const T & x) {
        return sizeof(x);
    }
}

namespace v2 {
    template<typename T>
    auto getSize(const T & x) {
        if constexpr (has_size<T>::value && has_value_type<T>::value)
            return x.size() * sizeof(typename T::value_type);
        return sizeof(x);
    }
}

int main(){

    test( has_size< int >::value, false);
    test( has_size<vector<int>>::value, true);
    test( has_size< B >::value ,  false);

    test(  has_value_type<int >::value,  false);
    test(  has_value_type<vector<int> >::value, true);
    test(  has_value_type< A >::value,  false);

    std::vector<int> v{1,2,3,4,5};
    cout << v1::getSize(5) << endl; // 4
    cout << v1::getSize(v) << endl; // 20
    cout << v2::getSize(5) << endl; // 4
    cout << v2::getSize(v) << endl; // 20

}
