# pragma once
# include "AMI_allocate.hpp"
# include "initializer_list"
# include <iostream>

__ASTL_NAMESPACE_START

template <class T, class alloc, _AMI_size_t _bufsize>
class __deque_iterator : 
public __base_iterator <__ittag_random_iterator, T> {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T&              reference;
    typedef _AMI_size_t     size_type;
    typedef _AMI_ptrdiff_t  difference_type;
    typedef T**             map_pointer;

    typedef __deque_iterator<T, alloc, _bufsize> self;

    pointer current_element;
    pointer node_begin;
    pointer node_end;
    map_pointer current_node;

    void set_node(map_pointer node) {
        current_node = node;
        node_begin = *node;
        node_end = node_begin + buf_size();
    }

    static size_type buf_size() {
        return _bufsize != 0 ? _bufsize : (sizeof(T) < 512 ? _AMI_size_t(512 / sizeof(T)) : 1);
    }
    reference& operator*() const {
        return *current_element;
    }
    pointer operator->() const {
        return current_element;
    }
    self& operator+=(difference_type _length) {
        difference_type len_frm_sta = (current_element - node_begin) +  _length;
        if (len_frm_sta >= 0 && len_frm_sta < buf_size()) {
            current_element += _length;
        } else {
            difference_type node_len = len_frm_sta / (difference_type)buf_size();
            difference_type element_len = len_frm_sta % (difference_type)buf_size();
            set_node(current_node + node_len);
            current_element = node_begin + element_len;
        }
        return *this;
    }
    self& operator-=(difference_type _length) {
        return this->operator+=(-_length);
    }
    self operator+(difference_type _length) const {
        self temp = *this;
        temp += _length;
        return temp;
    }
    self operator-(difference_type _length) const {
        self temp = *this;
        temp -= _length;
        return temp;
    }
    difference_type operator-(const self& _other) const {
        if (this->current_node == _other.current_node) {
            return difference_type(this->current_element - _other.current_element);
        } else {
            if (this->current_node > _other.current_node) {
                return difference_type(((this->current_node - _other.current_node) - 1) * buf_size() + 
                                        (this->current_element - this->node_begin) + 
                                        (_other.node_end - _other.current_element));
            } else {
                return -difference_type(((_other.current_node - this->current_node) - 1) * buf_size() + 
                                         (_other.current_element - _other.node_begin) + 
                                         (this->node_end - this->current_element));
            }
        }
    }
    self& operator++() {
        current_element++;
        if (current_element == node_end) {
            set_node(current_node + 1);
            current_element = node_begin;
        }
        return *this;
    }
    self operator++(int) {
        self old = *this;
        ++(*this);
        return old;
    }
    self& operator--() {
        if (current_element == node_begin) {
            set_node(current_node - 1);
            current_element = node_end;
        }
        current_element--;
        return *this;
    }
    self operator--(int) {
        self old = *this;
        --(*this);
        return old;
    }
    reference operator[](size_type _length) {
        return *(*this + _length);
    }
    bool operator==(const self &_other) const {
        return _other.current_element == this->current_element;
    }
    bool operator!=(const self &_other) const {
        return _other.current_element != this->current_element;
    }
    bool operator<(const self &_other) const {
        return (this->current_node == _other.current_node ? 
                this->current_element < _other.current_element :
                this->current_node < _other.current_node);
    }
};

template <class T, class alloc = __secondary_allocator, int _bufsize = 0>
class deque {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T&              reference;
    typedef _AMI_size_t     size_type;
    typedef _AMI_ptrdiff_t  difference_type;
    typedef T**             map_pointer;

    typedef __deque_iterator<T, alloc, _bufsize> iterator;

protected:
    map_pointer __map = 0;
    iterator __begin;
    iterator __end;

    size_type __map_size = 0;

    typedef base_allocator<value_type, alloc> node_alloc;
    typedef base_allocator<pointer, alloc> map_alloc;

    size_type buf_size() { return iterator::buf_size(); }
    void __destroy_all() { return AMI_std::destroy(__begin, __end); }
    void __dealloc_all() {
        map_pointer it;
        for (it = __begin.current_node; it <= __end.current_node; it++) {
            node_alloc::deallocate(*it);
        }
        map_alloc::deallocate(__map);
    }
    void _fill_init(size_type length, const value_type &value) {
        __init_node_and_map(length);
        map_pointer it;
        try {
            for (it = __begin.current_node; it < __end.current_node; it++) {
                uninitialized_fill(*it, *it + buf_size(), value);
            }
            uninitialized_fill(__end.node_begin, __end.current_element, value);
        }catch (...) {
            map_pointer _de_it;
            for (_de_it = __begin.current_node; _de_it < it; _de_it++) {
                AMI_std::destroy(_de_it, _de_it + buf_size());
            }
            throw;
        }
    }

    template <class inpt_iter>
    void _copy_init(inpt_iter _cpy_start, inpt_iter _cpy_end) {
        __init_node_and_map(_cpy_end - _cpy_start);
        map_pointer it;
        try {
            for (it = __begin.current_node; it < __end.current_node; it++, _cpy_start += buf_size()) {
                AMI_std::uninitialized_copy(_cpy_start, _cpy_start + buf_size(), *it);
            }
            AMI_std::uninitialized_copy(_cpy_start, _cpy_end, __begin.node_begin);
        }catch (...) {
            map_pointer _de_it;
            for (_de_it = __begin.current_node; _de_it < it; _de_it++) {
                AMI_std::destroy(_de_it, _de_it + buf_size());
            }
            throw;
        }
    }
    void __enlarge_map_at_begin(size_type new_node_number = 1) {
        size_type _new_map_l = new_node_number + __map_size;
        size_type _old_node_num = __end.current_node - __begin.current_node + 1;
        map_pointer new_start_node;
        if (__map_size > 2 * _new_map_l) {
            new_start_node = __map + new_node_number + (__map_size - _new_map_l) / 2;
            if (__begin.current_node > new_start_node) {
                copy(__begin.current_node, __end.current_node + 1, new_start_node);
            } else {
                copy_backward(__begin.current_node, __end.current_node + 1, __begin.current_node + _old_node_num);
            }
        }else {
            map_pointer new_map = map_alloc::allocate(_new_map_l);
            new_start_node = new_map + new_node_number + (_new_map_l - __map_size) / 2;
            copy(__begin.current_node, __end.current_node + 1, new_start_node);
            map_alloc::deallocate(__map, __map_size);
            __map = new_map;
            __map_size = _new_map_l;
        }
        __begin.set_node(new_start_node);
        __end.set_node(new_start_node + _old_node_num - 1);
    }
    void __enlarge_map_at_end(size_type new_node_number = 1) {
        size_type _new_map_l = new_node_number + __map_size;
        size_type _old_node_num = __end.current_node - __begin.current_node + 1;
        map_pointer new_start_node;
        if (__map_size > 2 * _new_map_l) {
            new_start_node = __map + (_new_map_l - __map_size) / 2;
            if (__begin.current_node > new_start_node) {
                copy(__begin.current_node, __end.current_node + 1, new_start_node);
            } else {
                copy_backward(__begin.current_node, __end.current_node + 1, __begin.current_node + _old_node_num);
            }
        } else {
            map_pointer new_map = map_alloc::allocate(_new_map_l);
            new_start_node = new_map + (_new_map_l - __map_size) / 2;
            copy(__begin.current_node, __end.current_node + 1, new_start_node);
            map_alloc::deallocate(__map, __map_size);
            __map = new_map;
            __map_size = _new_map_l;
        }
        __begin.set_node(new_start_node);
        __end.set_node(new_start_node + _old_node_num - 1);
    }
    pointer __allocate_node() {
        return (pointer)node_alloc::allocate(buf_size());
    }
    void __init_node_and_map(size_type element_num) {
        size_type node_number = element_num / buf_size() + 1;
        __map_size = node_number + 2;
        
        __map = map_alloc::allocate(__map_size);
        map_pointer node_start = __map + (__map_size - node_number) / 2;
        map_pointer node_end = node_start + node_number - 1;
        map_pointer it;
        try {
            for (it = node_start; it <= node_end; it++) {
                *it = __allocate_node();
            }
        } catch(...) {
            for (; node_start <= it; node_start++) {
                node_alloc::deallocate(*node_start);
            }
            throw;
        }

        __begin.set_node(node_start);
        __begin.current_element = __begin.node_begin;
        __end.set_node(node_end);
        __end.current_element = __end.node_begin + (element_num % buf_size());
    }
public:
    deque() noexcept : deque(0, value_type()) {}
    deque(size_type length, const value_type& value) noexcept :
        __begin(), __end() {
        _fill_init(length, value);
    }
    template <class inpt_iter>
    deque(const inpt_iter& start, const inpt_iter& end) noexcept :
        __begin(), __end() {
            _copy_init(start, end);
    }
    template <class other_type>
    deque(const other_type &other) noexcept :
        __begin(), __end() {
        _copy_init(other.begin(), other.end());
    }
    deque(const std::initializer_list<value_type> &i_list) noexcept :
        __begin(), __end() {
        _copy_init((pointer)i_list.begin(), (pointer)i_list.end());
    }
    deque(const AMI_std::deque<value_type> &other) noexcept :
        deque(other.begin(), other.end()) {}
    ~deque() noexcept {
        this->__destroy_all();
        this->__dealloc_all();
    }
    deque<T>& operator=(const deque<T>& other) noexcept {
        deque<T> temp(other);
        this->__destroy_all();
        this->__dealloc_all();
        _copy_init(temp.begin(), temp.end());
    }
    iterator begin() { return __begin; }
    iterator end() { return __end; }
    reference operator[](size_type __n) {
        return __begin[difference_type(__n)];
    }
    size_type capacity() const { return -1; }
    size_type size() const { return (__end - __begin); }
    size_type max_size() const { return -1; }
    bool empty() const { return __end == __begin; }
    reference front() { return *__begin; }
    reference back() { 
        iterator _temp = end();
        _temp--;
        return *_temp;
    }

    void push_back(const value_type& value) {
        construct(&*__end.current_element, value);
        __end.current_element++;

        if (__end.current_element == __end.node_end && __end.current_node == __map + __map_size - 1) {
            __enlarge_map_at_end();
        }
        if (__end.current_element == __end.node_end) {
            *(__end.current_node + 1) = node_alloc::allocate(buf_size());
            __end.set_node(__end.current_node + 1);
            __end.current_element = __end.node_begin;
        }
    }
    void pop_back() {
        if (__end.current_element == __end.node_begin) {
            node_alloc::deallocate(__end.node_begin);
            __end.set_node(__end.current_node - 1);
            __end.current_element = __end.node_end - 1;
        } else {
            __end.current_element--;
        }
        destroy(__end.current_element);
    }
    void push_front(const value_type& value) {
        if (__begin.current_element == __begin.node_begin && __begin.current_node == __map) {
            __enlarge_map_at_begin();
        }
        if (__begin.current_element == __begin.node_begin) {
            *(__begin.current_node - 1) = node_alloc::allocate(buf_size());
            __begin.set_node(__begin.current_node - 1);
            __begin.current_element = __begin.node_end;
        }
        __begin.current_element--;
        construct(__begin.current_element, value);
    }
    void pop_front() {
        destroy(__begin.current_element);
        __begin.current_element++;
        if (__begin.current_element == __begin.node_end) {
            node_alloc::deallocate(__begin.node_begin);
            __begin.set_node(__begin.current_node + 1);
            __begin.current_element = __begin.node_begin;
        }
    }
    void clear() {
        for (map_pointer it = __begin.current_node + 1; it <= __begin.current_node - 1; it++) {
            AMI_std::destroy(*it, *it + buf_size());
            node_alloc::deallocate(*it, buf_size());
        }
        if (__begin.current_node == __end.current_node) {
            AMI_std::destroy(__begin.current_element, __end.current_element);
        } else {
            AMI_std::destroy(__end.node_begin, __end.current_element);
            node_alloc::deallocate(__end.node_begin, buf_size());
        }
        __end = __begin;
    }
    void insert(size_type loca, const value_type& value) {
        return insert(__begin + loca, value);
    }
    void insert(const iterator &pos, const value_type& value) {
        if (pos - __begin < size() / 2) {
            this->push_front(front());
            copy(__begin + 2, pos, __begin + 1);
            *(pos - 1) = value;
        } else {
            this->push_back(back());
            copy_backward(pos, __end - 2, __end - 1);
            *pos = value;
        }
    }
    void erase(size_type loca) {
        return erase(__begin + loca);
    }
    void erase(const iterator &pos) {
        if (pos - __begin < size() / 2) {
            copy_backward(__begin, pos, pos + 1);
            this->pop_front();
        } else {
            copy(pos + 1, __end, pos);
            this->pop_back();
        }
    }
};

__ASTL_NAMESPACE_END 