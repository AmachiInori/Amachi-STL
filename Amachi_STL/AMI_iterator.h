#pragma once
#include "AMI_stddef.h"

namespace AMI_std {

class _ittag_input_iterator {};
class _ittag_output_iterator {};
class _ittag_forward_iterator : public _ittag_input_iterator {};
class _ittag_bidirection_iterator : public _ittag_forward_iterator {};
class _ittag_random_iterator : public _ittag_bidirection_iterator {};

class __false {};
class __true {};

template <class __it_category, class __type, 
          class __dis_type  = ptrdiff_t, 
          class __pointer   = __type*, 
          class __reference = __type&>
class __base_iterator {
    typedef __it_category   iterator_category;
    typedef __type          value_type;
    typedef __dis_type      difference_type;
    typedef __pointer       pointer;
    typedef __reference     reference;
};

template <class __iterator>
class __iterator_traits {
public:
    typedef __iterator::value_type          value_type;
    typedef __iterator::iterator_category   iterator_category;
    typedef __iterator::difference_type     difference_type;
    typedef __iterator::pointer             pointer;
    typedef __iterator::reference           reference;
};

template <class pointer_type>
class __iterator_traits<pointer_type*> {
public:
    typedef pointer_type                    value_type;
    typedef _ittag_random_iterator          iterator_category;
    typedef ptrdiff_t                       difference_type;
    typedef pointer_type*                   pointer;
    typedef pointer_type&                   reference;
};

template <class pointer_type>
class __iterator_traits<const pointer_type*> {
public:
    typedef pointer_type                    value_type;
    typedef _ittag_random_iterator          iterator_category;
    typedef ptrdiff_t                       difference_type;
    typedef const pointer_type*             pointer;
    typedef const pointer_type&             reference;
};

template <class __iterator>
inline typename __iterator_traits<__iterator>::iterator_category
__iterator_category() {
    return typename __iterator_traits<__iterator>::iterator_category();
}

template <class __iterator>
inline typename __iterator_traits<__iterator>::iterator_category
__iterator_category(const __iterator&) {
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

}// end of namespace 