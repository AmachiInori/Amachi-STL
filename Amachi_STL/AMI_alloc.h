#pragma once
#include <stdlib.h>
#include "AMI_type_traits.h"
#include "AMI_iterator.h"
#include "AMI_stlconfig.h"

__ASTL_NAMESPACE_START

template <class __targetType, class __valueType>
inline void construct(__targetType* target, const __valueType &val) {
    new (target) __targetType(val);
}

template <class __targetType>
inline void __destroy_single(__targetType *target, __true) {}

template <class __targetType>
inline void __destroy_single(__targetType *target, __false) {
    target->~__targetType();
}

template <class __input_iterator>
inline void destroy(__input_iterator begin, __input_iterator end) {
    typedef typename __type_traits<__iterator_traits<__input_iterator>::value_type>::has_trival_default_dtor 
        trival;
    for (; begin != end; begin++) 
        __destroy_single(&*begin, trival());
}

inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}

template <class __value_type>
class __primary_allocator {
    static void * out_of_memory_malloc(size_t);
    static void * out_of_memory_realloc(size_t);
    static void (*out_of_memory_handler)();

public:
    static void * allocate(size_t __size) {
        void * tempPtV = malloc(__size);
        if (tempPtV == 0) {
            tempPtV = out_of_memory_malloc(__size);
        }
        return tempPtV;
    }
    
};

__ASTL_NAMESPACE_END 