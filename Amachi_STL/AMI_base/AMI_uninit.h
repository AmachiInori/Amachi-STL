# pragma once
# include "AMI_type_traits.h"
# include "AMI_iterator.h"
# include "AMI_algobase.h"
# include "AMI_construct.h"

__ASTL_NAMESPACE_START

template <class forward_iterator, class value_type>
class __unint_fill {
private:
    static inline void
    __uninitialized_fill(forward_iterator start, forward_iterator end, 
                         const value_type &value, __true) {
        return fill(start, end, value);
    }

    static inline void
    __uninitialized_fill(forward_iterator start, forward_iterator end, 
                         const value_type &value, __false) {
        forward_iterator __start = start;
        try {
            for (; start != end; start++) {
                construct(&*start, value);
            }
        }catch (...) { // commit or rollback
            AMI_std::destroy(&*__start, &*start);
            throw;
        }
    }
public:
    template <class _forward_iterator, class _value_type>
    friend void uninitialized_fill(_forward_iterator start, 
        _forward_iterator end, const _value_type &value);
};

template <class _forward_iterator, class _value_type>
inline void
uninitialized_fill(_forward_iterator start, _forward_iterator end, 
                   const _value_type &value) {
    typedef typename __type_traits<_value_type>::is_POD_type is_POD_type;
    return __unint_fill<_forward_iterator, _value_type>::
        __uninitialized_fill(start, end, value, is_POD_type());
}

template <class forward_iterator, class value_type, class size_type>
class __unint_fill_n {
private:
    static inline forward_iterator 
    __uninitialized_fill_n(forward_iterator start, size_type length, 
                           const value_type &value, __true) {
        return fill_n(start, length, value);
    }

    static inline forward_iterator 
    __uninitialized_fill_n(forward_iterator start, size_type length, 
                           const value_type &value, __false) {
        forward_iterator __start = start;
        try {
            for (; length > 0; start++, length--) {
                construct(&*start, value);
            }
            return start;
        }catch (...) {
            AMI_std::destroy(&*__start, &*start);
            throw;
        }
    }
public:
    template <class _forward_iterator, class _value_type, class _size_type>
    friend _forward_iterator uninitialized_fill_n(_forward_iterator start, _size_type length, 
        const _value_type &value);
};

template <class _forward_iterator, class _value_type, class _size_type>
inline _forward_iterator 
uninitialized_fill_n(_forward_iterator start, _size_type length, 
                     const _value_type &value) {
    typedef typename __type_traits<_value_type>::is_POD_type is_POD_type;
    return __unint_fill_n<_forward_iterator, _value_type, _size_type>::
        __uninitialized_fill_n(start, length, value, is_POD_type());
}

template <class input_iterator, class forward_iterator>
class __unint_copy {
private:
    static inline forward_iterator
    __uninitialized_copy(input_iterator begin, input_iterator end, forward_iterator target, __true) {
        return AMI_std::copy(begin, end, target);
    }

    static  inline forward_iterator
    __uninitialized_copy(input_iterator begin, input_iterator end, forward_iterator target, __false) {
        forward_iterator start = target;
        try {
            for (; begin != end; begin++, target++) {
                AMI_std::construct(&*target, *begin);
            }
        }catch (...) {
            AMI_std::destroy(start, target);
            throw;
        }
        return start;
    }
public:
    template <class _input_iterator, class _forward_iterator>
    friend _forward_iterator uninitialized_copy(_input_iterator begin, 
        _input_iterator end, _forward_iterator target);
};

template <class _input_iterator, class _forward_iterator>
inline _forward_iterator
uninitialized_copy(_input_iterator begin, _input_iterator end, _forward_iterator target) {
    typedef typename __iterator_traits<_input_iterator>::value_type value_type;
    typedef typename __type_traits<value_type>::is_POD_type is_POD_type;
    return AMI_std::__unint_copy<_input_iterator, _forward_iterator>::
        __uninitialized_copy(begin, end, target, is_POD_type());
}

__ASTL_NAMESPACE_END 