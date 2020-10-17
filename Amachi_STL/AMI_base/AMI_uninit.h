# pragma once
# include "AMI_type_traits.h"
# include "AMI_iterator.h"
# include "AMI_algobase.h"
# include "AMI_construct.h"

__ASTL_NAMESPACE_START

template <class forward_iterator, class value_type>
inline forward_iterator 
uninitialized_fill(forward_iterator start, forward_iterator end, 
                   const value_type &value) {

}

template <class forward_iterator, class value_type>
inline forward_iterator 
__uninitialized_fill(forward_iterator start, forward_iterator end, 
                     const value_type &value, __true) {
    return fill(start, end, value);
}

template <class forward_iterator, class value_type>
inline forward_iterator 
__uninitialized_fill(forward_iterator start, forward_iterator end, 
                     const value_type &value, __false) {
    for (; start != end; start++) {
        construct(start, value);
    }
}

__ASTL_NAMESPACE_END 