#include <iostream>
using namespace std;


constexpr double operator ""_m(unsigned long long x) {
    return x;
};

constexpr double operator ""_m(long double x) {
    return x;
};

constexpr double operator ""_s(unsigned long long x) {
    return x;
};

constexpr double operator ""_s(long double x) {
    return x;
};

constexpr double operator ""_km(unsigned long long x) {
    return x * 1000_m;
};

constexpr double operator ""_km(long double x) {
    return x * 1000.0_m;
};

constexpr double operator ""_h(unsigned long long x) {
    return x * 3600_s;
};

constexpr double operator ""_h(long double x) {
    return x * 3600.0_s;
};

constexpr double operator ""_ms(long double x) {
    return x / 1000.0_s ;
};

constexpr double operator ""_cm(unsigned long long x) {
    return x / 100_m;
};

/**
    Computes velocity in meters per seconds.
    @param distance  distance in meters
    @param time      time in seconds
    @return velocity in meters per seconds.
*/
double computeVelocity(double distance, double time){
    return distance/time;
}

int main(){
    cout << computeVelocity(100_m, 5_s) << endl;     //20
    cout << computeVelocity(360_km, 2.0_h) << endl;  //50
    cout << computeVelocity(3.6_km, 0.02_h) << endl; //50
    cout << computeVelocity(250_cm, 2.5_ms) << endl; //1000
    return 0;
}
