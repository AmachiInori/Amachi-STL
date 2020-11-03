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

template <class T, class alloc = __secondary_allocator> 
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
    
    iterator __alloc_and_init(size_type length, const value_type &value) {
        iterator res = __array_alloc::allocate(length);
        AMI_std::uninitialized_fill_n(res, length, value);
        return res;
    }

    template <class inpt_iter>
    iterator __alloc_and_copy(inpt_iter begin, inpt_iter end) {
        iterator res = __array_alloc::allocate(end - begin);
        AMI_std::uninitialized_copy(begin, end, res);
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
     * Default constructor of array
     * no return 
     * 
    **/
    array() noexcept = default;

    /** 
     * Constructor of array with a uint length, element uses its default constructor 
     * no return 
     * length - unsigned int - the length of the array
    **/
    explicit array(size_type length) noexcept {
        __map_begin = __alloc_and_init(length, size_type());
        __map_end = __map_begin + length;
    }

    /** 
     * Constructor of array with two iterator to copy all the elements between __begin and __end 
     * no return 
     * __begin - iterator - the start point of the copied array
     * __end   - iterator - the end point of the copied array
    **/
    template <class inpt_iter>
    array(inpt_iter __begin, inpt_iter __end) noexcept {
        size_type __length = __end - __begin;
        __map_begin = __alloc_and_copy(__begin, __end);
        __map_end = __map_begin + __length;
    }

    /** 
     * Constructor of array with a uint length, element uses its copy constructor 
     * no return 
     * length - unsigned int        - the length of the array
     * value  - const value_type &  - the copied element
    **/
    array(size_type length, const value_type &value) noexcept {
        __map_begin = __alloc_and_init(length, value);
        __map_end = __map_begin + length;
    }

    /** 
     * Constructor of array with a int length, element uses its copy constructor 
     * no return 
     * length - int                 - the length of the array
     * value  - const value_type &  - the copied element
    **/
    array(int length, const value_type &value) noexcept {
        __map_begin = __alloc_and_init(size_type(length), value);
        __map_end = __map_begin + length;
    }

    /** 
     * Constructor of array with a long int length, element uses its copy constructor 
     * no return 
     * length - long int            - the length of the array
     * value  - const value_type &  - the copied element
    **/
    array(long length, const value_type &value) noexcept {
        __map_begin = __alloc_and_init(size_type(length), value);
        __map_end = __map_begin + length;
    }

    /** 
     * Copy constructor of array
     * no return 
     * other_v - const array<value_type> & - the copied array
    **/
    array(const array<value_type> &other_v) noexcept {
        __map_begin = __alloc_and_copy(other_v.__map_begin, other_v.__map_end);
        __map_end = __map_begin + (other_v.__map_end - other_v.__map_begin);
    }
# ifndef AMI_STL_STRICT_MODE
    template <class other>
    array(const other& _other) noexcept :
        array(_other.begin(), _other.end()) {}
# endif

    array(const std::initializer_list<value_type> &i_list) noexcept : 
        array((iterator)i_list.begin(), (iterator)i_list.end()) {}

    /**
     * Destructor of array
    **/
    ~array() noexcept {
        __destroy_element();
        __dealloc();
    }

# ifndef AMI_STL_STRICT_MODE
    /**
     * Standard assignment operator
     * returns: array<value_type> & - lvalue of assignment
     * other_v - const other & - the right value of assignment  
    **/
    template <class other>
    array<value_type>& operator=(const other &other_v) {
        array<value_type> temp(other_v);
        this->__destroy_element();
        this->__dealloc();
        __map_begin = __alloc_and_copy(temp.__map_begin, temp.__map_end);
        __map_end = __map_begin + (temp.__map_end - temp.__map_begin);
        return *this;
    }
# endif

    array<value_type>& operator=(const array<value_type> &other_v) {
        array<value_type> temp(other_v);
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
};

__ASTL_NAMESPACE_END 