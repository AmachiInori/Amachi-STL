# pragma once
# include "AMI_base/AMI_stlconfig.h"
# include "AMI_base/AMI_stddef.h"

__ASTL_NAMESPACE_START

template <class type>
class less {
public:
    constexpr bool operator()(const type &a, const type& b) { return a < b; }
};

template <class type>
class greater {
public:
    constexpr bool operator()(const type &a, const type& b) { return a > b; }
};

__ASTL_NAMESPACE_END