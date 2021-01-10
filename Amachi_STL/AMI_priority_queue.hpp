
/**
 * This is a Standard C++ Library header.
 * This file is the user oriented part of amachi STL
 * Open source by MIT by amachi Inori
 * Copyright (C) 2020-2020 Amachi Inori.
 * 
 * Main header file of string
 * 
**/

# pragma once
# include <initializer_list>
# include "AMI_base/AMI_heap.h"
# include "AMI_deque.hpp"
# include "AMI_functional.hpp"

__ASTL_NAMESPACE_START

template <class T, 
          class container = AMI_std::deque<T>, 
          class cmp = AMI_std::less<T>>
class priority_queue {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T&              reference;
    typedef _AMI_size_t     size_type;
    typedef _AMI_ptrdiff_t  difference_type;
protected:
    container __ctn;
public:
    priority_queue() noexcept = default;

    priority_queue(const std::initializer_list<value_type>& __init_list) : __ctn(__init_list) {
        AMI_std::build_heap<typename container::iterator, cmp>(__ctn.begin(), __ctn.end());
    }

    priority_queue(const priority_queue<value_type>& _copy_orin) : __ctn(_copy_orin.__ctn) {  }

# ifndef AMI_STL_STRICT_MODE
    template <class other_type>
    priority_queue(const other_type &other) noexcept :
        __ctn(other.begin(), other.end()) {
        AMI_std::build_heap<typename container::iterator, cmp>(__ctn.begin(), __ctn.end());
    }
# endif

    priority_queue(priority_queue<value_type>&& _move_orin) : __ctn(std::move(_move_orin.__ctn)) {  }

    ~priority_queue() = default;

    value_type& top() const {
        return *__ctn.begin();
    }

    void push(const value_type& _value) {
        __ctn.push_back(_value);
        push_heap<typename container::iterator, cmp>(__ctn.begin(), __ctn.end());
    }

    void pop() {
        pop_heap<typename container::iterator, cmp>(__ctn.begin(), __ctn.end());
        __ctn.pop_back();
    }

    unsigned int size() const;
    bool empty() const;
};

__ASTL_NAMESPACE_END 