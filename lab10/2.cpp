#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <forward_list>
#include <vector>
#include <deque>

template <typename Container>
double median(Container c);

template <typename Container>
double median_impl(Container& c, std::random_access_iterator_tag) {
    using std::begin;
    using std::end;

    const size_t n = c.size();
    auto mid = c.begin() + n / 2;

    std::nth_element(c.begin(), mid, c.end());
    double upper = *mid;

    if (n % 2 == 1) {
        return upper;
    }

    auto left_max = std::max_element(c.begin(), mid);
    double lower = *left_max;

    return (lower + upper) / 2.0;
}

template <typename Container>
double median_impl(Container& c, std::forward_iterator_tag) {
    using std::begin;
    using std::end;

    c.sort();

    const size_t n = std::distance(c.begin(), c.end());
    auto mid = c.begin();
    std::advance(mid, n / 2);

    if (n % 2 == 1) {
        return static_cast<double>(*mid);
    }

    auto prev = mid;
    --prev;

    return (*prev + *mid) / 2.0;
}

template <typename Container>
double median(Container c) {
    using category = typename std::iterator_traits<
        typename Container::iterator
    >::iterator_category;

    return median_impl(c, category{});
}

int main() {
    std::list<int> a{3, 2, 5, 1, 4};
    std::cout << median(a) << std::endl; // 3
    std::vector<int> v{3, 1, 4, 2};
    std::cout << median(v) << std::endl; // 2.5
}
