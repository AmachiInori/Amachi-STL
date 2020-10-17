# include "AMI_iterator.h"

__ASTL_NAMESPACE_START

template <class input_iterator, class type>
inline void fill(input_iterator begin, input_iterator end, const type &target) { //only POD types
    for (; begin != end; begin++) {
        *begin = target;
    }
}

template <class input_iterator, class type, class size_type = _AMI_ptrdiff_t>
inline input_iterator fill_n(input_iterator begin, input_iterator end, size_type length, const type &target) {
    for (; length > 0; length--, begin++) {
        *begin = target;
    }
}

__ASTL_NAMESPACE_END