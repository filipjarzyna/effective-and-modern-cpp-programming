#include <string>

template<typename T>
class vector_traits {
public:
    using param_type = const T&;
    using scalar_type = T;

    static T multiply(scalar_type t, param_type v) {
        return t * v;
    }

    static T zero() {
        return 0;
    }

};

template<>
class vector_traits<std::string> {
public:
    using param_type = const std::string&;
    using scalar_type = int;

    static std::string multiply(scalar_type t, param_type v) {
        if (t == 0) return 0;

        std::string res;
        res.reserve(v.size() * t);

        for(int i = 0; i < t; i++)
            res += v;

        return res;
    }

    static std::string zero() {
        return "0";
    }
};

template<>
class vector_traits<int> {
public:
    using param_type = int;
    using scalar_type = int;

    static int multiply(scalar_type t, param_type v) {
        return t * v;
    }

    static int zero() {
        return 0;
    }
};

template<>
class vector_traits<double> {
public:
    using param_type = double;
    using scalar_type = double;

    static double multiply(scalar_type t, param_type v) {
        return t * v;
    }

    static double zero() {
        return 0.;
    }
};

