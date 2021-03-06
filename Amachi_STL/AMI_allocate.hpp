
/**
 * This file is the user oriented part of amachi STL
 * Open source by MIT by amachi Inori
 * 
 * Main header file of allocator
**/

# pragma once
# include "AMI_base/AMI_alloc.h"
# include "AMI_base/AMI_uninit.h"
# include "AMI_base/AMI_construct.h"

__ASTL_NAMESPACE_START

template <class __value_type, class allocator = __secondary_allocator> 
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