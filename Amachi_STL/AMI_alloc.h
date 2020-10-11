#pragma once
#include <stdlib.h>

namespace AMI_std {

template <class __targetType, class __valueType>
inline void construct(__targetType* &target, const __valueType &val) {
    target = new(__targetType(val));
}

template <class __targetType>
inline void destroy(__targetType *target) {
    target->~__targetType();
} //未提供缺省类型支持

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

} /* end of namespace AMI_std */