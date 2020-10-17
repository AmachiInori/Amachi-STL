# pragma once
# include "AMI_stddef.h"

__ASTL_NAMESPACE_START

class __ittag_input_iterator {};
class __ittag_output_iterator {};
class __ittag_forward_iterator : public __ittag_input_iterator {};
class __ittag_bidirection_iterator : public __ittag_forward_iterator {};
class __ittag_random_iterator : public __ittag_bidirection_iterator {};

template <class __iterator>
class __iterator_traits {
public:
    typedef typename __iterator::value_type          value_type;
    typedef typename __iterator::iterator_category   iterator_category;
    typedef typename __iterator::difference_type     difference_type;
    typedef typename __iterator::pointer             pointer;
    typedef typename __iterator::reference           reference;
};

template <class pointer_type>
class __iterator_traits<pointer_type*> {
public:
    typedef pointer_type                    value_type;
    typedef __ittag_random_iterator         iterator_category;
    typedef _AMI_ptrdiff_t                  difference_type;
    typedef pointer_type*                   pointer;
    typedef pointer_type&                   reference;
};

template <class pointer_type>
class __iterator_traits<const pointer_type*> {
public:
    typedef pointer_type                    value_type;
    typedef __ittag_random_iterator         iterator_category;
    typedef _AMI_ptrdiff_t                  difference_type;
    typedef const pointer_type*             pointer;
    typedef const pointer_type&             reference;
};

/* 类型提取函数 */
template <class __iterator>
inline typename __iterator_traits<__iterator>::iterator_category
iterator_category() {
    return typename __iterator_traits<__iterator>::iterator_category();
}

template <class __iterator>
inline typename __iterator_traits<__iterator>::iterator_category
iterator_category(const __iterator&) {
    return typename __iterator_traits<__iterator>::iterator_category();
}

template <class __iterator>
inline typename __iterator_traits<__iterator>::difference_type
difference_type() {
    return typename __iterator_traits<__iterator>::difference_type(0);
}

template <class __iterator>
inline typename __iterator_traits<__iterator>::difference_type
difference_type(const __iterator&) {
    return typename __iterator_traits<__iterator>::difference_type(0);
}

template <class __iterator>
inline typename __iterator_traits<__iterator>::value_type
value_type() {
    return typename __iterator_traits<__iterator>::value_type(0);
}

template <class __iterator>
inline typename __iterator_traits<__iterator>::value_type
value_type(const __iterator&) {
    typedef typename __iterator_traits<__iterator>::value_type value;
    return value(0);
}

__ASTL_NAMESPACE_END