
#ifndef LAB8_FILTER_H
#define LAB8_FILTER_H
#include <iostream>

template<typename Container, typename Predicate>
class Filter {
private:
    Container container;
    Predicate predicate;
    using container_iter = decltype(std::declval<std::remove_reference_t<Container>&>().begin());

 public:
    Filter(Container c, Predicate p) : container(c), predicate(p) {}

    class iterator{
    private:
        container_iter cur;
        container_iter end;
        const Predicate& predicate;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = typename container_iter::value_type;
        using difference_type = typename container_iter::difference_type;
        using pointer = typename container_iter::pointer;
        using reference = typename container_iter::reference;
    private:
        void skip_invalid() {
            while(cur != end) {
                if(predicate(*cur))
                    break;
                cur++;
            }
        }

    public:
        iterator(container_iter cur, container_iter end, const Predicate& p)
            : cur(cur), end(end), predicate(p)  {
                skip_invalid();
            }

        reference operator*() const {
            return *cur;
        }

        pointer operator->() const {
            return &(*cur);
        }

        iterator& operator++() {
            cur++;
            skip_invalid();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(iterator other) {
            return cur == other.cur;
        }

        bool operator!=(iterator other) {
            return cur != other.cur;
        } 
    };

public:
    iterator begin() {
        return iterator(container.begin(), container.end(), predicate);
    }

    iterator end() {
        return iterator(container.end(), container.end(), predicate);
    }

};

template<typename Container, typename Predicate>
Filter<Container, Predicate> make_filter(Container&& c, Predicate&& p) {
    return Filter<Container, Predicate>(std::forward<Container>(c), std::forward<Predicate>(p));
}
#endif //LAB8_FILTER_H
