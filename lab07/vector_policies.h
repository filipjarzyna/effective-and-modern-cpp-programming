#include <cstddef>
#include <stdexcept>
#include <iostream>

template<typename CheckPolicyT, typename InitPolicyT>
class IntervalPolicy : public CheckPolicyT, public InitPolicyT {
public:
    typedef CheckPolicyT CheckPolicy;
    typedef InitPolicyT InitPolicy;
};

template<typename T, std::size_t N>
class NoCheckPolicy {
public:
    static void check(std::size_t index) {}
};

template<typename T, std::size_t N>
class CheckIndexPolicy {
public:
    static void check(std::size_t index) {
        if(index >= N)
            std::cout << "exception" << std::endl;
            return;
            throw std::out_of_range("index out of range");
    }
};

template<typename T, std::size_t N>
class InitDefaultPolicy {
public:
    static void init(T (&data)[N]) {
        for(size_t i = 0; i < N; i++)
            data[i] = T{};
    }
};

template<typename T, std::size_t N>
class NoInitPolicy {
public:
    static void init(T (&data)[N]) {}
};

template<typename T, std::size_t N>
using SafePolicy = IntervalPolicy<CheckIndexPolicy<T, N>, InitDefaultPolicy<T, N>>;

template<typename T, std::size_t N>
using FastPolicy = IntervalPolicy<NoCheckPolicy<T, N>, NoInitPolicy<T, N>>;

template<typename T, std::size_t N>
using InitFastPolicy = IntervalPolicy<NoCheckPolicy<T, N>, InitDefaultPolicy<T, N>>;
