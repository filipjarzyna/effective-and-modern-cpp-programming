#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

template <typename... Types>
class MultiVector {
private:
    using tuple_type = tuple<vector<Types> ...>;

    tuple_type container;

    template <typename T, size_t I = 0>
    static constexpr size_t tuple_index() {
        static_assert(I != tuple_size_v<tuple_type>, "Type not found");
        if constexpr (is_same_v<tuple_element_t<I, tuple_type>, vector<T>>) {
            return I;
        } else {
            return tuple_index<T, I + 1>();
        }
    }

    template<typename T>
    void print_vector(const vector<T>& c) {
        cout << "[ ";
        for(auto a : c)
            cout << a << " ";
        cout << "]";
    }

public:
    MultiVector() = default;

    constexpr size_t size() {
        return sizeof...(Types);
    }

    template<typename T>
    void push_back(T arg) {
        auto& vec = get<tuple_index<T>()>(container);
        vec.push_back(std::move(arg));
    }

    template<std::size_t I = 0>
    void print() {
        if constexpr (I < std::tuple_size_v<tuple_type>)
        {
            print_vector(get<I>(container));
            print<I + 1>();
        } else {
            cout << endl;
        }
    }
};

int main(){

  MultiVector<int, string, double> m;
  m.push_back(5);
  m.push_back(string("text"));
  m.push_back(7);
  m.push_back(1.2);
  m.print();   // [ 5 7 ] [ text ] [ 1.2 ]
  auto v = std::move(m);
  for(auto x: { 1, 2, 3}){
	v.push_back(x+10);
	v.push_back(std::to_string(x));
	v.push_back(x/10.0);
  }
  m.print(); // [ ] [ ] [ ]   but can be undefined
  v.print(); // [ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
  MultiVector<int, int, double, int> w;
  w.push_back(1);
  w.push_back(2.0);
  w.print(); // [ 1 ] [ ] [ 2 ] [ ]
}
/*
[ 5 7 ] [ text ] [ 1.2 ]
[ ] [ ] [ ]
[ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
[ 1 ] [ ] [ 2 ] [ ]  
 */
