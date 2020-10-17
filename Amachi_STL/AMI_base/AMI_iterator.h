# pragma once
# include "AMI_itera_traits.h"

__ASTL_NAMESPACE_START

template <class __it_category, class __type
        , class __dis_type  = _AMI_ptrdiff_t
        , class __pointer   = __type*
        , class __reference = __type&>
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

/***************************************
- 通用迭代器函数 
distance函数描述两个迭代器的距离
 ***************************************/
template <class __input_iterator>
inline typename __iterator_traits<__input_iterator>::difference_type
__distance(__input_iterator begin, __input_iterator end 
        ,  __ittag_input_iterator) {
    typedef typename __iterator_traits<__input_iterator>::difference_type distance;
    distance res = 0;
    while (begin != end) res++, begin++;
    return res;
}

template <class __random_iterator>
inline typename __iterator_traits<__random_iterator>::difference_type
__distance(__random_iterator begin, __random_iterator end
        ,  __ittag_random_iterator) {
    return end - begin;
}

template <class iterator>
inline typename __iterator_traits<iterator>::difference_type
distance(iterator begin, iterator end) {
    typedef typename __iterator_traits<iterator>::iterator_category category;
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
inline void __advance(__random_iterator& it, __distance_type move_length
                    , __ittag_random_iterator) {
    it += move_length;
}

template <class __double_iterator, class __distance_type>
inline void __advance(__double_iterator& it, __distance_type move_length
                    , __ittag_bidirection_iterator) { //内部实现调用之方法，因此不必追究move_length的正负问题
    if (move_length > 0) {
        while (move_length--) it++;
    } else {
        while (move_length++) it--;
    }
}

template <class iterator, class distance_type>
inline void advance(iterator& it, distance_type move_length) {
    return __advance(it, distance, iterator_category<iterator>(it));
}

__ASTL_NAMESPACE_END