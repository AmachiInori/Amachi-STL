# pragma once
# include "AMI_deque.hpp"

__ASTL_NAMESPACE_START

template <class T, class __container = AMI_std::deque<T>>
class stack {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T&              reference;
    typedef _AMI_size_t     size_type;
protected:
    __container __main_cont;
public:
    stack() noexcept : __main_cont() { }
    stack(size_type length, const value_type& value) noexcept : 
        __main_cont(length, value) { }
    stack(const std::initializer_list<value_type> &i_list) noexcept :
        __main_cont(i_list) { }

# ifndef AMI_STL_STRICT_MODE
    __container& container() { return __main_cont; }
# endif

    size_type size() const { return __main_cont.size(); }
    size_type empty() const { return __main_cont.empty(); }
    size_type capacity() const { return __main_cont.capacity(); }
    size_type max_size() const { return __main_cont.max_size(); }
    value_type& top() { return __main_cont.back(); }
    void push(const value_type& value) { return __main_cont.push_back(value); }
    void pop() { return __main_cont.pop_back(); }
};

__ASTL_NAMESPACE_END