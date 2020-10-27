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

template <class input_iterator, class forward_iterator>
inline forward_iterator copy_backward(input_iterator begin, input_iterator end, forward_iterator target) {  //only POD types
    for (; begin != end; end--, target--) {
        *target = *begin;
    }
    return target;
}

template <class type>
inline void swap(type &a, type &b) {
    type temp = a;
    a = b;
    b = temp;
}

template <class input_iterator, class value_type>
inline input_iterator find_first_of(input_iterator begin, input_iterator end, const value_type &value) {
    for (; begin != end; begin++) {
        if (*begin == value) return begin;
    }
    return end;
}

template <class input_iterator, class value_type>
inline input_iterator find_first_not_of(input_iterator begin, input_iterator end, const value_type &value) {
    for (; begin != end; begin++) {
        if (*begin != value) return begin;
    }
    return end;
}

template <class input_iterator, class value_type>
inline input_iterator find_last_not_of(input_iterator begin, input_iterator end, const value_type &value) {
    input_iterator old = end;
    end--;
    for (; begin != end; end--) {
        if (*end != value) return end;
    }
    return old;
}

template <class input_iterator, class value_type>
inline input_iterator find_last_of(input_iterator begin, input_iterator end, const value_type &value) {
    input_iterator old = end;
    end--;
    for (; begin != end; end--) {
        if (*end == value) return end;
    }
    return old;
}

template <class value_type>
inline value_type min(value_type a, value_type b) {
    return a >= b ? b : a;
}

template <class value_type>
inline value_type& max(const value_type& a, const value_type& b) {
    return a > b ? a : b;
}

_AMI_size_t strlen(const char* _str) {
    int _i = 0;
    for (_i = 0; _str[_i] != '\0'; _i++);
    return _i;
}

__ASTL_NAMESPACE_END