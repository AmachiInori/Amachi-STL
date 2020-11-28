# pragma once
# include "AMI_stlconfig.h"
# include "AMI_stddef.h"
# include "../AMI_functional.hpp"
# include "AMI_iterator.h"

__ASTL_NAMESPACE_START

template <class random_iterator, class _cmp = less<typename __iterator_traits<random_iterator>::value_type>>
inline void push_heap(random_iterator begin, random_iterator end, _cmp) {
    return __push_heap(begin, end, end - begin, *begin, _cmp());
}

template <class random_iterator, class _cmp, class distance, class value_type> 
inline void __push_heap(random_iterator begin, random_iterator end, distance, value_type, _cmp) {
    return __percolate_up(begin, distance((end - begin) - 1), *(end - 1), _cmp());
}

template <class random_iterator, class _cmp, class distance, class value_type> 
inline void __percolate_up(random_iterator begin, distance insert_loca, value_type insert_value, _cmp) {
    auto father_index = [](distance loca) { return (loca - 1) / 2; };
    distance current = insert_loca;
    for (current = insert_loca; current > 0; current = father_index(current)) {
        if (_cmp()(*(begin + father_index(current)), insert_value)) break;
        *(begin + current) = *(begin + father_index(current));
    }
    *(begin + current) = insert_value;
}

template <class random_iterator, class _cmp = less<typename __iterator_traits<random_iterator>::value_type>>
inline void pop_heap(random_iterator begin, random_iterator end, _cmp) {
    return __pop_heap(begin, end, end - begin, *begin, _cmp());
}

template <class random_iterator, class _cmp, class distance, class value_type> 
inline void __pop_heap(random_iterator begin, random_iterator end, distance, value_type, _cmp) {
    return __percolate_down(begin, distance((end - begin) - 1), *(begin), _cmp());
}

template <class random_iterator, class _cmp, class distance, class value_type> 
inline void __percolate_down(random_iterator begin, distance end_loca, value_type root_value, _cmp) {
    auto left_child = [](distance root) { return (root + 1) * 2 - 1; };
    auto right_child = [](distance root) { return (root + 1) * 2; };
    distance current = 0;
    while (1) {
        if (left_child(current) >= end_loca) break;
        if (right_child(current) >= end_loca) {
            *(begin + current) = *(begin + left_child(current));
            current = right_child(current);
        } else {
            if (_cmp()(*(begin + left_child(current)), *(begin + right_child(current)))) {
                *(begin + current) = *(begin + left_child(current));
                current = left_child(current);
            } else {
                *(begin + current) = *(begin + right_child(current));
                current = right_child(current);
            }
        }
    }
    *(begin + current) = *(begin + end_loca);
    *(begin + end_loca) = root_value;
}

template <class random_iterator, class _cmp>
inline void build_heap(random_iterator begin, random_iterator end, _cmp) {
    random_iterator current = begin + 1;
    for (current; current != end; current++) {
        push_heap(begin, current, _cmp());
    }
} 

__ASTL_NAMESPACE_END