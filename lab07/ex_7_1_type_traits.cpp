#include <iostream>
#include <limits>
using  namespace std;
/**
 * Outputs information about numerical type T:
 * (un)signed, (not) integer, min & max values
*/
template <typename T>
void info(T x){
    string sign = std::numeric_limits<T>::is_signed ? "signed" : "unsigned";
    string integer = std::numeric_limits<T>::is_integer ? "integer" : "not integer";
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();
    cout << sign << ", " << integer << ", " << "min: " << min << " max: " << max << endl;
}

int main() {
    info(1);
    info(2.0f);
    info(3U);
    return 0;
}
/**
 * Expected output:
    signed,  integer, min : -2147483648 max : 2147483647
    signed, not integer, min : 1.17549e-38 max : 3.40282e+38
    unsigned,  integer, min : 0 max : 4294967295
 */
