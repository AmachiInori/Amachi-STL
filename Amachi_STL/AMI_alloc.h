# pragma once
# include <stdlib.h>
# include "AMI_type_traits.h"
# include "AMI_iterator.h"
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
    __destroy_single(&*target, trival());
}

template <class __input_iterator>
inline void _destroy(__input_iterator begin, __input_iterator end) {
    for (; begin != end; begin++) 
        __destroy(&*begin);
}

inline void _destroy(char*, char*) {}
inline void _destroy(wchar_t*, wchar_t*) {}



class __primary_allocator {
    static void * out_of_memory_malloc(_AMI_size_t __size) {
        void (*handler)() = out_of_memory_handler;
        void *tempPtV;
        for (;;) {
            if (0 == handler) __THROW_BAD_ALLOC;
            handler();
            tempPtV = malloc(__size);
            if (tempPtV != nullptr) return tempPtV;
        }
    }
    static void * out_of_memory_realloc(void* __pointer, _AMI_size_t __size) {
        void (*handler)() = out_of_memory_handler;
        void *tempPtV;
        for (;;) {
            if (0 == handler) __THROW_BAD_ALLOC;
            handler();
            tempPtV = realloc(__pointer, __size);
            if (tempPtV != nullptr) return tempPtV;
        }
    }
    static void (*out_of_memory_handler)();

public:
    static void * allocate(_AMI_size_t __size) {
        void *tempPtV = malloc(__size);
        if (tempPtV == 0) {
            tempPtV = out_of_memory_malloc(__size);
        }
        return tempPtV;
    }
    static void deallocate(void *__pointer, _AMI_size_t) {
        free(__pointer);
    }
    static void * reallocate(void *__pointer, _AMI_size_t, _AMI_size_t __new_size) {
        void *tempPtV = realloc(__pointer, __new_size);
        if (tempPtV == 0) {
            tempPtV = out_of_memory_realloc(__pointer, __new_size);
        }
        return tempPtV;
    }
    static void (*set_OOM_handler(void (*new_oom_handler)()))() {
        void (*oldOOM)() = out_of_memory_handler;
        out_of_memory_handler = new_oom_handler;
        return oldOOM;
    }
};
void (*__primary_allocator::out_of_memory_handler)() = 0;



class __secondary_allocator {
    union list_node {
        union list_node *next;
        char memory_data[1];
    };
    
    static const _AMI_size_t unit = 8;
    static const _AMI_size_t max_bytes = 128;
    static const _AMI_size_t chain_number = max_bytes / unit;

    static _AMI_size_t __round (_AMI_size_t n) { return (n + unit - 1) & ~(unit - 1); }
    static _AMI_size_t __find_list_loca (_AMI_size_t __size) {
        return __size / unit; //.
    } 
    static union list_node* volatile __main_table[chain_number];

    static char *__memory_pool_start;
    static char *__memory_pool_end;
    static char *__pool_alloc(_AMI_size_t __size, _AMI_size_t &__got_node_number) {
        
    }
    static void *__refill(_AMI_size_t __size) {

    }
public:
    static void * allocate(_AMI_size_t __size) {
        if (__size > max_bytes) return __primary_allocator::allocate(__size);
        union list_node* volatile *target = __main_table + __find_list_loca(__size);
        union list_node* tempPtC = *target;
        if (tempPtC == 0) {
            void *res = __refill(__round(__size));
            return res;
        }
        *target = tempPtC->next;
    }
    static void deallocate(void *__pointer, _AMI_size_t __size) {
        if (__size > max_bytes) {
            return __primary_allocator::deallocate(__pointer, __size);
        }
        union list_node* volatile *target = __main_table + __find_list_loca(__size);
        union list_node* tempPtN = (union list_node*)__pointer;
        tempPtN->next = *target;
        *target = tempPtN;
    }
};
char *__secondary_allocator::__memory_pool_start = 0;
char *__secondary_allocator::__memory_pool_end = 0;
typename __secondary_allocator::list_node * volatile
__secondary_allocator::__main_table[chain_number] = 
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


template<class __value_type, class allocator = __primary_allocator> 
class base_allocator {
public:
    typedef __value_type            value_type;
    typedef __value_type*           pointer;
    typedef const __value_type*     const_pointer;
    typedef __value_type&           reference;
    typedef const __value_type&     const_reference;
    typedef _AMI_size_t             size_type;
    typedef _AMI_ptrdiff_t          difference_type;

    size_type max_size() const { return UINT_MAX / size_type(sizeof(value_type)); }
    pointer address(reference n) const { return &n; };
    const_pointer address(const_reference n) const { return &n; };
    static void construct(pointer target, const_reference val) {
        _construct<value_type, value_type>(target, val);
    }
    static void destroy(pointer __pointer) {
        _destroy(__pointer);
    }
    static pointer allocate(size_type length) {
        return length == 0 ? 0 : (__value_type*)allocator::allocate(sizeof(value_type) * length);
    }
    static pointer allocate() {
        return (__value_type*)allocator::allocate(sizeof(value_type));
    }
    static void deallocate(pointer __pointer, size_type length) {
        if (length != 0) {
            allocator::deallocate(__pointer, length);
        }
    }
    static void deallocate(pointer pointer) {
        allocator::deallocate(pointer, sizeof(value_type));
    }
};

__ASTL_NAMESPACE_END 