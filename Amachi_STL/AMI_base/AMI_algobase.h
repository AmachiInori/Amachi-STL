# include "AMI_iterator.h"

__ASTL_NAMESPACE_START

template <class input_iterator, class type>
inline void fill(input_iterator begin, input_iterator end, const type &value) { //only POD types
    for (; begin != end; begin++) {
        *begin = value;
    }
}

template <class input_iterator, class type, class size_type = _AMI_ptrdiff_t>
inline input_iterator fill_n(input_iterator begin, size_type length, const type &value) {  //only POD types
    for (; length > 0; length--, begin++) {
        *begin = value;
    }
    return begin;
}

template <class input_iterator, class forward_iterator>
inline forward_iterator copy(input_iterator begin, input_iterator end, forward_iterator target) {  //only POD types
    for (; begin != end; begin++, target++) {
        *target = *begin;
    }
    return target;
}

__ASTL_NAMESPACE_END