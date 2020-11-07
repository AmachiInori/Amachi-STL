# pragma once
# include "AMI_allocate.hpp"
# include "initializer_list"

# ifndef AMI_STL_STRICT_MODE
#   include <iostream>
# endif


/**
 * This file is the user oriented part of amachi STL
 * Open source by MIT by amachi Inori
 * 
 * Main header file of array
 * The array is declared and defined in this file with namespace AMI_std
**/

__ASTL_NAMESPACE_START

template <class T, _AMI_size_t length, class alloc = __secondary_allocator> 
class array {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef T*              iterator;
    typedef const T*        const_iterator;
    typedef T&              reference;
    typedef _AMI_size_t     size_type;
    typedef _AMI_ptrdiff_t  difference_type;

protected:
    typedef base_allocator<T, alloc>  __array_alloc;

    iterator __map_begin = 0;
    iterator __map_end = 0;
    
    iterator __alloc_and_init(const value_type &value) {
        iterator res = __array_alloc::allocate(length);
        AMI_std::uninitialized_fill_n(res, length, value);
        return res;
    }

    void __destroy_element() {
        destroy(__map_begin, __map_end);
        __map_end = __map_begin;
    }
    void __dealloc() {
        if (__map_begin) {
            __array_alloc::deallocate(__map_begin, this->size());
        }
        __map_begin = 0;
        __map_end = 0;
    }
public:
    /** 
     * Constructor of array with length, element uses its default constructor 
     * no return 
     * 
    **/
    explicit array() noexcept {
        __map_begin = __alloc_and_init(length, size_type());
        __map_end = __map_begin + length;
    }

    /** 
     * Constructor of array with length, element uses its copy constructor 
     * no return 
     * value  - const value_type &  - the copied element
    **/
    array(const value_type &value) noexcept {
        __map_begin = __alloc_and_init(value);
        __map_end = __map_begin + length;
    }

    /** 
     * Copy constructor of array
     * no return 
     * other_v - const array<value_type> & - the copied array
    **/
    array(const array<value_type, length> &other_v) noexcept {
        __map_begin = __alloc_and_copy(other_v.__map_begin, other_v.__map_end);
        __map_end = __map_begin + (other_v.__map_end - other_v.__map_begin);
    }

    /**
     * Destructor of array
    **/
    ~array() noexcept {
        __destroy_element();
        __dealloc();
    }

    array<value_type, length>& operator=(const array<value_type, length> &other_v) {
        array<value_type, length> temp(other_v);
        this->__destroy_element();
        this->__dealloc();
        __map_begin = __alloc_and_copy(temp.__map_begin, temp.__map_end);
        __map_end = __map_begin + (temp.__map_end - temp.__map_begin);
        return *this;
    }

    /**
     * Gets the reference of the element according to the subscript
     * returns: value_type & - the element according to the subscript
     * loca - unsigned int - the subscript 
    **/
    value_type& at(size_type loca) {
        return (*this)[loca];
    }

    void fill(const value_type& value) {
        for (iterator i = __map_begin; i != __map_end; i++) {
            *i = value;
        }
    }

    /**
     * Gets the begin itreator of array
     * returns: iterator - the begin itreator of array
     * 
    **/
    iterator begin() const noexcept { return __map_begin; }

    /**
     * Gets the end itreator of array
     * returns: iterator - the end itreator of array
     * 
    **/
    iterator end() const noexcept { return __map_end; }

    /**
     * Gets the occupied size of array
     * returns: unsigned int - occupied size of array
     * 
    **/
    size_type size() const noexcept { return size_type(__map_end - __map_begin); }

    /**
     * Judge whether array is empty
     * returns: bool
     * 
    **/
    bool empty() const noexcept { return __map_begin == __map_end; }

    /**
     * Gets the first element of array
     * returns: value_type& - the last element of array
     * 
    **/
    reference front() { return *begin(); }

    /**
     * Gets the last element of array
     * returns: value_type& - the last element of array
     * 
    **/
    reference back() { return *(end() - 1); }

    /**
     * Gets the reference of the element according to the subscript
     * returns: value_type & - the element according to the subscript
     * loca - unsigned int - the subscript 
    **/
    reference operator[](size_type loca) {
        return *(__map_begin + loca);
    }

    /**
     * Find the first element that is not equal to value
     * returns: iterator - required iterator
     * _target - const value_type & - the target
    **/
    iterator find_first_not_of(const value_type &_target) {
        return ::AMI_std::find_first_not_of(begin(), end(), _target);
    }

    /**
     * Find the first element that is equal to value
     * returns: iterator - required iterator
     * _target - const value_type & - the target
    **/
    iterator find_first_of(const value_type &_target) {
        return ::AMI_std::find_first_of(begin(), end(), _target);
    }

    /**
     * Find the last element that is equal to value
     * returns: iterator - required iterator
     * _target - const value_type & - the target
    **/
    iterator find_last_of(const value_type &_target) {
        return ::AMI_std::find_last_of(begin(), end(), _target);
    }

    /**
     * Find the last element that is not equal to value
     * returns: iterator - required iterator
     * _target - const value_type & - the target
    **/
    iterator find_last_not_of(const value_type &_target) {
        return ::AMI_std::find_last_not_of(begin(), end(), _target);
    }

    /**
     * Output array elements with fixed separator, Stream operation operators that overload elements are required.
     * @return no returns
     * @param _div - const char* (default: ", ") - the separator
    **/
    void print(const char* _div = ", ") {
        for (iterator i = begin(); i < end() - 1; i++) {
            std::cout << *i << _div;
        }
        if (size() > 0) std::cout << back();
        std::cout << "\n";
    }
# ifndef AMI_STL_STRICT_MODE
    operator bool() { return this->empty(); }
# endif
};

# ifndef AMI_STL_STRICT_MODE
    template <class T, _AMI_size_t len> 
    std::ostream &operator<<(std::ostream& os, array<T, len> &_v) {
        for (typename array<T, len>::iterator i = _v.begin(); i < _v.end() - 1; i++) {
            std::cout << *i << ", ";
        }
        if (_v.size() > 0) std::cout << _v.back();
        return os;
    }
# endif


__ASTL_NAMESPACE_END 