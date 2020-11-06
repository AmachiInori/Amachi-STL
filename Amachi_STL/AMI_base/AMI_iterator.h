# pragma once
# include "AMI_itera_traits.h"

__ASTL_NAMESPACE_START

template <class __it_category, class __type
        , class __dis_type  = _AMI_ptrdiff_t
        , class __pointer   = __type*
        , class __reference = __type&>
class __base_iterator {
public:
    typedef __it_category   iterator_category;
    typedef __type          value_type;
    typedef __dis_type      difference_type;
    typedef __pointer       pointer;
    typedef __reference     reference;

    __base_iterator() = default;
    virtual ~__base_iterator() = default;
};

/***************************************
- ͨ�õ��������� 
distance�������������������ľ���
 ***************************************/
template <class __iterator>
class __dist {
private:
    static inline typename __iterator_traits<__iterator>::difference_type
    __distance(__iterator begin, __iterator end 
            ,  __ittag_input_iterator) {
        typedef typename __iterator_traits<__iterator>::difference_type distance;
        distance res = 0;
        while (begin != end) res++, begin++;
        return res;
    }

    static inline typename __iterator_traits<__iterator>::difference_type
    __distance(__iterator begin, __iterator end
            ,  __ittag_random_iterator) {
        return end - begin;
    }
public:
    template <class iterator>
    friend typename __iterator_traits<iterator>::difference_type
        distance(iterator begin, iterator end);
};

template <class iterator>
inline typename __iterator_traits<iterator>::difference_type
distance(iterator begin, iterator end) {
    typedef typename __iterator_traits<iterator>::iterator_category category;
    return __dist<iterator>::__distance(begin, end, category());
}

/***************************************
- ͨ�õ��������� 
advance���������õĵ�������ǰ����
****************************************/
template <class __input_iterator, class __distance_type>
inline void __advance(__input_iterator& it, __distance_type move_length, 
                      __ittag_input_iterator) { //�ڲ�ʵ�ֵ���֮��������˲���׷��move_length����������
    while(move_length--) it++;
}

template <class __random_iterator, class __distance_type>
inline void __advance(__random_iterator& it, __distance_type move_length
                    , __ittag_random_iterator) {
    it += move_length;
}

template <class __double_iterator, class __distance_type>
inline void __advance(__double_iterator& it, __distance_type move_length
                    , __ittag_bidirection_iterator) { //�ڲ�ʵ�ֵ���֮��������˲���׷��move_length����������
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