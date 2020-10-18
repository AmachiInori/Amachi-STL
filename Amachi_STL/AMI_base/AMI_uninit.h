# pragma once
# include "AMI_type_traits.h"
# include "AMI_iterator.h"
# include "AMI_algobase.h"
# include "AMI_construct.h"

__ASTL_NAMESPACE_START

template <class forward_iterator, class value_type>
inline void
uninitialized_fill(forward_iterator start, forward_iterator end, 
                   const value_type &value) {
    typedef typename __type_traits<value_type>::is_POD_type is_POD_type;
    return __uninitialized_fill(start, end, value, is_POD_type());
}

template <class forward_iterator, class value_type>
inline void
__uninitialized_fill(forward_iterator start, forward_iterator end, 
                     const value_type &value, __true) {
    return fill(start, end, value);
}

template <class forward_iterator, class value_type>
inline void
__uninitialized_fill(forward_iterator start, forward_iterator end, 
                     const value_type &value, __false) {
    for (; start != end; start++) {
        construct(start, value);
    }
}

template <class forward_iterator, class value_type, class size_type>
inline forward_iterator 
uninitialized_fill_n(forward_iterator start, size_type length, 
                     const value_type &value) {
    typedef typename __type_traits<value_type>::is_POD_type is_POD_type;
    return __uninitialized_fill_n(start, length, value, is_POD_type());
}

template <class forward_iterator, class value_type, class size_type>
inline forward_iterator 
__uninitialized_fill_n(forward_iterator start, size_type length, 
                       const value_type &value, __true) {
    return fill_n(start, length, value);
}

template <class forward_iterator, class value_type, class size_type>
inline forward_iterator 
__uninitialized_fill_n(forward_iterator start, size_type length, 
                       const value_type &value, __false) {
    for (; length > 0; start++, length--) {
        construct(&*start, value);
    }
    return start;
}

template <class input_iterator, class forward_iterator>
inline forward_iterator
uninitialized_copy(input_iterator begin, input_iterator end, forward_iterator target) {
    typedef typename __iterator_traits<input_iterator>::value_type value_type;
    typedef typename __type_traits<value_type>::is_POD_type is_POD_type;
    return __uninitialized_copy(begin, end, target, is_POD_type());
}

template <class input_iterator, class forward_iterator>
inline forward_iterator
__uninitialized_copy(input_iterator begin, input_iterator end, forward_iterator target, __true) {
    return copy(begin, end, target);
}

template <class input_iterator, class forward_iterator>
inline forward_iterator
__uninitialized_copy(input_iterator begin, input_iterator end, forward_iterator target, __false) {
    for (; begin != end; begin++, target++) {
        construct(&*target, *begin);
    }
    return target;
}

__ASTL_NAMESPACE_END 