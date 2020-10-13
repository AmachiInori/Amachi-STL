#pragma once
#include "AMI_stddef.h"
#include "AMI_stlconfig.h"

__ASTL_NAMESPACE_START

class __ittag_input_iterator {};
class __ittag_output_iterator {};
class __ittag_forward_iterator : public __ittag_input_iterator {};
class __ittag_bidirection_iterator : public __ittag_forward_iterator {};
class __ittag_random_iterator : public __ittag_bidirection_iterator {};

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
public:
    __base_iterator() = default;
    virtual ~__base_iterator() = default;
    virtual bool operator==(const __base_iterator&) = 0;
    virtual bool operator!=(const __base_iterator&) = 0;
};

/****************************************/

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
    typedef __ittag_random_iterator         iterator_category;
    typedef ptrdiff_t                       difference_type;
    typedef pointer_type*                   pointer;
    typedef pointer_type&                   reference;
};

template <class pointer_type>
class __iterator_traits<const pointer_type*> {
public:
    typedef pointer_type                    value_type;
    typedef __ittag_random_iterator         iterator_category;
    typedef ptrdiff_t                       difference_type;
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
    typedef __iterator_traits<__iterator>::value_type value;
    return value(0);
}

/***************************************
- 通用迭代器函数 
distance函数描述两个迭代器的距离
 ***************************************/
template <class __input_iterator>
inline typename __iterator_traits<__input_iterator>::difference_type
__distance(__input_iterator begin, __input_iterator end, 
           __ittag_input_iterator) {
    typedef __iterator_traits<__input_iterator>::difference_type distance;
    distance res = 0;
    while (begin != end) res++, begin++;
    return res;
}

template <class __random_iterator>
inline typename __iterator_traits<__random_iterator>::difference_type
__distance(__random_iterator begin, __random_iterator end, 
           __ittag_random_iterator) {
    return end - begin;
}

template <class __iterator>
inline typename __iterator_traits<__iterator>::difference_type
distance(__iterator begin, __iterator end) {
    typedef __iterator_traits<__iterator>::iterator_category category;
    return __distance(begin, end, category());
}

/***************************************
- 通用迭代器函数 
advance函数将引用的迭代器向前迭代
****************************************/
template <class __input_iterator, class __distance_type>
inline void __advance(__input_iterator& it, __distance_type move_length, 
                      __ittag_input_iterator) { //内部实现调用之方法，因此不必追究move_length的正负问题
    while(move_length--) it++;
}

template <class __random_iterator, class __distance_type>
inline void __advance(__random_iterator& it, __distance_type move_length, 
                      __ittag_random_iterator) {
    it += move_length;
}

template <class __double_iterator, class __distance_type>
inline void __advance(__double_iterator& it, __distance_type move_length, 
                      __ittag_bidirection_iterator) { //内部实现调用之方法，因此不必追究move_length的正负问题
    if (move_length > 0) {
        while (move_length--) it++;
    } else {
        while (move_length++) it--;
    }
}

template <class __iterator, class __distance_type>
inline void advance(__iterator& it, __distance_type move_length) {
    return __advance(it, distance, iterator_category<__iterator>(it));
}

__ASTL_NAMESPACE_END