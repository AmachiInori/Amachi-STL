# pragma once
# include "AMI_deque.hpp"

# ifndef AMI_STL_STRICT_MODE
#   include <iostream>
# endif

__ASTL_NAMESPACE_START

template <class T, class __container = AMI_std::deque<T>>
class queue {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T&              reference;
    typedef _AMI_size_t     size_type;
protected:
    __container __main_cont;
public:
    queue() noexcept : __main_cont() { }
    queue(size_type length, const value_type& value) noexcept : 
        __main_cont(length, value) { }
    queue(const std::initializer_list<value_type> &i_list) noexcept :
        __main_cont(i_list) { }
    queue<T>& operator=(const queue<T> &other) {
        __main_cont = other.__main_cont;
        return *this;
    }

# ifndef AMI_STL_STRICT_MODE 
    template <class inner_cont>
    queue<T>& operator=(const inner_cont &other) {
        __main_cont = other;
        return *this;
    }
    template <class inpt_iter>
    queue(const inpt_iter& begin, const inpt_iter& end) noexcept :
        __main_cont(begin, end) { }
    template <class other_cont>
    queue(const other_cont& other) noexcept :
        __main_cont(other) { };

    __container& container() { return __main_cont; }
# endif 

    size_type size() const { return __main_cont.size(); }
    size_type empty() const { return __main_cont.empty(); }
    size_type capacity() const { return __main_cont.capacity(); }
    size_type max_size() const { return __main_cont.max_size(); }
    value_type& front() { 
    # ifdef AMI_STL_STRICT_MODE
        if (empty()) __THROW_OUT_OF_BOUNDS;
    # endif
        return __main_cont.front(); 
    }
    void push(const value_type& value) { return __main_cont.push_back(value); }
    void pop() { 
    # ifdef AMI_STL_STRICT_MODE
        if (empty()) __THROW_OUT_OF_BOUNDS;
    # endif
        return __main_cont.pop_front();
    }
    
# ifndef AMI_STL_STRICT_MODE 
    void print(const char* _div = ", ") {
        for (typename __container::iterator i = __main_cont.begin(); i < __main_cont.end() - 1; i++) {
            std::cout << *i << _div;
        }
        if (size() > 0) std::cout << __main_cont.back();
        std::cout << "\n";
    }
# endif 
# ifndef AMI_STL_STRICT_MODE
    operator bool() { return this->empty(); }
# endif
};

__ASTL_NAMESPACE_END