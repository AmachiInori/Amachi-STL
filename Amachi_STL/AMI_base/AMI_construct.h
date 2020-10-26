# pragma once
# include "AMI_type_traits.h"
# include "AMI_stlconfig.h"

__ASTL_NAMESPACE_START

template <class targetType, class valueType>
inline void _construct(targetType* target, const valueType &val) {
    new (target) targetType(val);
}

template <class __targetType>
inline void __destroy_single(__targetType *target, __true) {}

template <class __targetType>
inline void __destroy_single(__targetType *target, __false) {
    target->~__targetType();
}

template <class __targetType>
inline void _destroy(__targetType *target) {
    typedef typename __type_traits<__targetType>::has_trival_default_dtor trival;
    __destroy_single(target, trival());
}

template <class __input_iterator>
inline void _destroy(__input_iterator begin, __input_iterator end) {
    for (; begin != end; begin++) 
        _destroy(&*begin);
}

inline void _destroy(char*, char*) {}
inline void _destroy(wchar_t*, wchar_t*) {}

template <class targetType, class valueType>
inline void construct(targetType* target, const valueType &val) {
    _construct(target, val);
}

template <class __input_iterator>
inline void destroy(__input_iterator pointer) {
    _destroy(pointer);
}

template <class __input_iterator>
inline void destroy(__input_iterator begin, __input_iterator end) {
    _destroy(begin, end);
}

__ASTL_NAMESPACE_END